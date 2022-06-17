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
            for (Road* pRoad: pRoads) {
                roadSourceMap[pRoad->source] = pRoad->uniqueID;
            }
        }

        void updateWorld() {
           for (Car* pCar : pCars) {
               pCar->update(pRoads, roadSourceMap);
           } 
           for (Road* pRoad : pRoads)
               pRoad->updateLights();
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
