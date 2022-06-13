#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "../includes/road.h"
#include "../includes/car.h"
#include "../includes/map.h"
#include "../includes/common.h"

float fps = 50.0;    // Frames per second
float dt = 1 / fps;  // Time between frames
bool export_data = true;
float simTime = 15; // Simulation time in seconds
int totalFrameNum = simTime / dt;  // Total number of frames

// Still to Implement
// TODO: IDM equations for 1D model
// TODO: Expand to 2D - Implement turning
// TODO: Intersections with Traffic Lights
// TODO: Collision detection

// Improvements:
// - MOBIL Lane changing
// - More layouts

// For lane change MOBIL model
// https://traffic-simulation.de/info/info_MOBIL.html

// Note: We are assuming 10px == 1m irl

typedef std::array<int, 2> coord;

int main() {
    // Setup our road layout
    Road road1(0, "left", {150, 475}, {900, 525});
    Road road2(1, "left", {100, 475}, {150, 525});
    Road road3(2, "up", {100, 100}, {150, 475});
    std::vector<Road> roads = {road1, road2, road3};
    Map worldMap(1000, 1000, roads);
    // Export road data to a csv file so that we can read it in in Python
    if (export_data) {worldMap.writeRoadsToCSV("../visual/road_data.csv");}
    
    // Setup Car Objects
    Car car1(nullptr);  // nullptr for first car
    /* Car car3(&car2); */
    car1.x = 200;  // Initial position
    car1.y = 500;
    car1.v = car1._kmhtoms(150);
    car1.d = {1.0, 0.0};

    Car car2(&car1);
    car2.x = 100;  // Initial position
    car2.y = 500;
    car2.v = car2._kmhtoms(120);
    car2.d = {1.0, 0.0};

    float t = 0.0;
    for (int i = 0; i < totalFrameNum; i++) {
        t += dt;  // Keep track of overall time elapsed
        car1.update();
        car2.update();
    }

    worldMap.cars.push_back(car1);
    worldMap.cars.push_back(car2);

    if (export_data) {worldMap.writeCarsToCSV("../visual/car_data.csv");}
    return 0;
}
