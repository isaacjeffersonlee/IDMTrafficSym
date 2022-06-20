#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include "../includes/common.hh"


class World {

    public:
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
        Car* spawnCar(int spawnNum, float desiredSpeedKmh, int spawnFrameIdx) {
            std::array<int, 2> spawnCoord =  spawnCoords[spawnNum];
            Road* pStartRoad = pRoads[roadSourceMap[spawnCoord]];
            // Check whether the pCars vector for the corresponding spawn point
            // has any cars in it, i.e isFirst?
            Car* pCar;
            if (pActiveCars[spawnNum].empty()) {  // First Car
                pCar = new Car(nullptr, desiredSpeedKmh, pStartRoad,
                        spawnNum, spawnFrameIdx);  // nullptr for first car
            }
            else {  // Not first car
                // Get the current last car for the spawn
                int n = pActiveCars[spawnNum].size();
                Car* pNextCar = pActiveCars[spawnNum][n-1];
                pCar = new Car(pNextCar, desiredSpeedKmh, pStartRoad,
                        spawnNum, spawnFrameIdx);
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
            std::cout << "Deleting Objects..." << std::endl;
            for (Road* pRoad : pRoads) {
                delete pRoad;
            }
            for (std::vector<Car *> pCars : pActiveCars) {
                for (Car* pCar : pCars) {
                    delete pCar;
                }
            }
            for (Car* pCar : pDespawnedCars) {
                delete pCar;
            }
        }
};
