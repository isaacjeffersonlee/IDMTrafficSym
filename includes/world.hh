#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include <set>
/* #include "../includes/road.hh" */
/* #include "../includes/car.hh" */
#include "../includes/common.hh"
#include "../includes/exporter.hh"

float getRandomSpeed() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(20.0f, 160.0f);
    return distr(eng);
}

class World {

    public:
        float t = 0.0f; // Current time in seconds.
        int width;
        int height;
        std::vector<Road *> pRoads;
        std::vector<std::vector<Car *>> pActiveCars;
        std::vector<Car *> pDespawnedCars;
        // Map of source coords to road uniqueID
        // Each road is uniquely defined by it's source coordinates because
        // for our model, two pRoads cannot have the same source coordinates.
        std::map<std::array<int, 2>, int> roadSourceMap;
        // (x, y) px coords for starting spawn points
        std::vector<std::array<int, 2>> spawnCoords;  
        // Travel times for each car, where the ith index -> travel time in seconds
        // for the ith car.
        std::vector<float> travelTimes;

        World(int width,
                int height, 
                std::vector<Road *> pRoads,
                std::vector<int> spawnRoadNums)
            : width(width)
            , height(height)
            , pRoads(pRoads)
        {
            // Populate the source map, which maps source coordinates
            // to their road number. We can do this since 2 roads cannot
            // share the same source.
            for (Road* pRoad : pRoads) {
                for (std::array<int, 2> source : pRoad->sources) {
                    roadSourceMap[source] = pRoad->uniqueID;
                }
            }
            for (int spawnRoadNum : spawnRoadNums) {
                spawnCoords.push_back(pRoads[spawnRoadNum]->source);
                pActiveCars.push_back({});  // Initialize empty nested vector
            }
        }
        
        // Spawn a car at the spawn coordinate, adding it to the correct pCars
        // vector. Note: spawnFrameIdx is the frame number that the car will
        // spawn at.
        Car* spawnCar(int spawnNum, int spawnFrameIdx,
                float desiredSpeedKmh, float T, float a, float b, int delta, float s0) {
            /* float spawnTime = spawnFrameIdx * dt;  // Keep track of this for metrics */
            std::array<int, 2> spawnCoord =  spawnCoords[spawnNum];
            Road* pStartRoad = pRoads[roadSourceMap[spawnCoord]];
            // Check whether the pCars vector for the corresponding spawn point
            // has any cars in it, i.e isFirst?
            Car* pCar;
            if (pActiveCars[spawnNum].empty()) {  // First Car
                pCar = new Car(nullptr, pStartRoad,  // nullptr for first car
                        spawnNum, spawnFrameIdx,
                        desiredSpeedKmh, T, a, b, delta, s0);
            }
            else {  // Not first car
                // Get the current last car for the spawn
                int n = pActiveCars[spawnNum].size();
                Car* pNextCar = pActiveCars[spawnNum][n-1];
                pCar = new Car(pNextCar, pStartRoad,
                        spawnNum, spawnFrameIdx,
                        desiredSpeedKmh, T, a, b, delta, s0);
            }
            pActiveCars[spawnNum].push_back(pCar);
            return pCar;
        }

        // Remove car from pActiveCars vector
        void despawnCar(Car* pCar) {
            // Remove the first item from the corresponding car vector.
            // This assumes we will be deleting cars sequentially, in order
            // of when they were spawned.
            pActiveCars[pCar->spawnIdx].erase(pActiveCars[pCar->spawnIdx].begin());
            // Make the next in line the front car
            pActiveCars[pCar->spawnIdx][0]->isFirst = true;
            pDespawnedCars.push_back(pCar);
        }

        void updateWorld(float t) {
            for (std::vector<Car *> pCars : pActiveCars) {
               for (Car* pCar : pCars) {
                   if (pCar->despawn) {
                       despawnCar(pCar);
                       // Time that passes before car is spawned.
                       float spawnTime = pCar->spawnFrameIdx * dt;
                       float travelTime = t - spawnTime;
                       travelTimes.push_back(travelTime);
                   }
                   else {
                       pCar->updateCar(pRoads, roadSourceMap);
                   }
               } 
            } 
            for (Car* pCar : pDespawnedCars) {
                // Yeet the car off the screen.
                // This is kinda dodgy and if I had more time I'd 
                // find a better solution.
                // TODO: Better despawning method.
                pCar->x = 1500;
                pCar->y = 1500;
                pCar->updateExportInfo();
            }
            for (Road* pRoad : pRoads) {
               if (pRoad->isIntersection) {  // TODO: Better Traffic Light Switching
                   if (fmod(t, pRoad->trafficLightDelay) < 0.001f) {
                       pRoad->updateLight();
                   } 
                   pRoad->lightCoords.push_back(
                           {pRoad->source[0],
                           pRoad->source[1],
                           pRoad->sink[0],
                           pRoad->sink[1]});
               } 
               else {
                   pRoad->lightCoords.push_back({0, 0, 0, 0});
               }
            }
        }

        // Free up dynamically allocated memory
        void deleteRemainingObjects() {
            std::cout << "Cleaning up..." << std::endl;
            // Use sets, because in some weird edge cases we get car
            // pointers added to both despawnedCars and activeCars,
            // and then we would get a double free error.
            // Probably a better way to do this.
            std::set<Road *> remainingRoads;
            std::set<Car *> remainingCars;
            for (Road* pRoad : pRoads) {
                remainingRoads.insert(pRoad);
            }
            for (Road* pRemainingRoad : remainingRoads) {
                delete pRemainingRoad;
            }
            for (std::vector<Car *> pCars : pActiveCars) {
                for (Car* pCar : pCars) {
                    remainingCars.insert(pCar);
                }
            }
            for (Car* pCar : pDespawnedCars) {
                remainingCars.insert(pCar);
            }
            for (Car* pRemainingCar : remainingCars) {
                delete pRemainingCar;
            }
        }

        // Run a simulation
        std::vector<float> runSim(bool exportData, float T, float a, float b, int delta, float s0) {
            float t = 0.0;
            for (int i = 0; i < totalFrameNum; i++) {
                t += dt;  // Keep track of overall time elapsed
                updateWorld(t);
                // TODO: Put this in a loop
                if (i % 200 == 0) {
                    Car* pCar = spawnCar(0, i, getRandomSpeed(), T, a, b, delta, s0);
                }
                if (i % 200 == 0) {
                    Car* pCar = spawnCar(1, i, getRandomSpeed(), T, a, b, delta, s0);
                }
                if (i % 200 == 0) {
                    Car* pCar = spawnCar(2, i, getRandomSpeed(), T, a, b, delta, s0);
                }
                if (i % 200 == 0) {
                    Car* pCar = spawnCar(3, i, getRandomSpeed(), T, a, b, delta, s0);
                }
            }
            
            Exporter e = Exporter(exportData);
            if (exportData) {
                e.writeTravelTimesToCSV("../visual/data/travel_times.csv", travelTimes);
                std::vector<Car *> pCars;
                for (std::vector<Car *> activeCars : pActiveCars) {
                    for (Car* pCar : activeCars) {
                        pCars.push_back(pCar);
                    }
                }
                for (Car* pDespawnedCar : pDespawnedCars) {
                    pCars.push_back(pDespawnedCar);
                }
                e.writeCarsToCSV("../visual/data/car_data.csv", pCars);
                e.writeTrafficLightsToCSV("../visual/data/light_data.csv", pRoads);
            }
            deleteRemainingObjects();
            std::cout << "*Sigh* Simulation complete." << std::endl;
            return travelTimes;
        }
};
