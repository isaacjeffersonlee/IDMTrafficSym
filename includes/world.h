#include <string>
#include <fstream>
#include <iostream>
#include <array>
/* #include "../includes/road.h" */
/* #include "../includes/car.h" */
#include "../includes/common.h"
#include <vector>
#include <map>


class World {

    public:
        int width;
        int height;
        std::vector<Road> roads;
        std::vector<Car *> pCars;
        std::map<std::array<int, 2>, int> roadSourceMap;  // Map of source coords to road uniqueID
        // Each road is uniquely defined by it's source coordinates because
        // for our model, two roads cannot have the same source coordinates.

        World(int width,
                int height, 
                std::vector<Road> roads)
            : width(width)
            , height(height)
            , roads(roads)
        {
            for (Road r: roads) {
                roadSourceMap[r.source] = r.uniqueID;
            }
        }

        void updateWorld() {
           for (Car* pCar : pCars) {
               pCar->update(roads, roadSourceMap);
           } 
        }

        // Cleanup
        void deleteObjects() {
            for (Car* pCar : pCars) {
                delete pCar;
            }
            std::cout << "Deleted Objects." << std::endl;
        }
};
