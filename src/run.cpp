#include <iostream>
#include <string>
#include <vector>
#include "../includes/road.h"
#include "../includes/car.h"
#include "../includes/map.h"


// Still to Implement
// TODO: IDM equations for 1D model
// TODO: Expand to 2D - Implement turning
// TODO: Intersections with Traffic Lights
// TODO: Collision detection

// Improvements:
// - Better python export method
// - MOBIL Lane changing
// - More layouts

// For lane change MOBIL model
// https://traffic-simulation.de/info/info_MOBIL.html

int main() {
    Road road1(0, "left", {150, 475}, {900, 525});
    Road road2(1, "left", {100, 475}, {150, 525});
    Road road3(2, "up", {100, 100}, {150, 475});
    std::vector<Road> roads = {road1, road2, road3};
    /* std::vector<Road> roads = {road1}; */
    Map worldMap(1000, 1000, roads);
    worldMap.writeMaptoFile("../visual/test_map.py");
    return 0;
}
