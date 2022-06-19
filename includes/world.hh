#include <string>
#include <fstream>
#include <iostream>
#include <array>
/* #include "../includes/road.h" */
/* #include "../includes/car.h" */
#include "../includes/common.hh"
#include <vector>
#include <map>


class World {

    public:
        int width;
        int height;
        std::vector<Road *> pRoads;
        std::vector<Car *> pCars;
        // Map of source coords to road uniqueID
        // Each road is uniquely defined by it's source coordinates because
        // for our model, two pRoads cannot have the same source coordinates.
        std::map<std::array<int, 2>, int> roadSourceMap;

        World(int width,
                int height, 
                std::vector<Road *> pRoads)
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
        }

        void updateWorld(float t) {
           for (Car* pCar : pCars) {
               pCar->update(pRoads, roadSourceMap);
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
        void deleteObjects() {
            std::cout << "Deleting Objects..." << std::endl;
            for (Car* pCar : pCars) {
                delete pCar;
            }
            for (Road* pRoad : pRoads) {
                delete pRoad;
            }
        }
};
