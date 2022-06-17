#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "../includes/road.h"
#include "../includes/car.h"
#include "../includes/world.h"
#include "../includes/common.h"
#include "../includes/exporter.h"

float fps = 50.0;                   // Frames per second
float dt = 1 / fps;                 // Time between frames
bool export_data = true;            // Set false to prevent writing to files
float simTime = 60;                 // Simulation time in seconds
int totalFrameNum = simTime / dt;   // Total number of frames

// Still to Implement
// TODO: Intersections with Traffic Lights
// TODO: Random car spawning
// TODO: Better README

// Improvements:
// - Color changing depending on speed
// - Printing parameter values
// - More dynamic method for spawing road layouts
// - Read parameters from json/YAML
// - MOBIL Lane changing
// - More layouts

// For lane change MOBIL model
// https://traffic-simulation.de/info/info_MOBIL.html

// Note: We are assuming 10px == 1m irl


int main() {
    // Setup our road layout
    Road road0(0, {120, 860}, {{140, 880}}, {100, 860}, {140, 900});
    Road road1(1, {140, 880}, {{860, 880}}, {140, 860}, {860, 900});
    Road road2(2, {860, 880}, {{880, 860}}, {860, 860}, {900, 900});
    Road road3(3, {880, 860}, {{880, 140}}, {860, 140}, {900, 860});
    Road road4(4, {880, 140}, {{860, 120}}, {860, 100}, {900, 140});
    Road road5(5, {860, 120}, {{140, 120}}, {140, 100}, {860, 140});
    Road road6(6, {140, 120}, {{120, 140}}, {100, 100}, {140, 140});
    Road road7(7, {120, 140}, {{120, 860}}, {100, 140}, {140, 860});
    std::vector<Road> roads = {road0, road1, road2, road3, road4, road5, road6, road7};
    World world(1000, 1000, roads);

    // Initialize our exporter object
    Exporter e = Exporter(true);
    // Export road data to a csv file so that we can read it in in Python
    e.writeRoadsToCSV("../visual/data/road_data.csv", roads);

    // Setup Car Objects
    Car car0(nullptr);  // nullptr for first car
    /* Car car3(&car2); */
    car0.x = 600;  // Initial position
    car0.y = 880;
    car0.v = car0.kmhtoms(40);
    car0.pCurrentRoad = &road1;

    Car car1(&car0);
    car1.x = 140;  // Initial position
    car1.y = 120;
    car1.v = car1.kmhtoms(120);
    car1.pCurrentRoad = &road5;

    Car car2(&car1);
    car2.x = 500;  // Initial position
    car2.y = 120;
    car2.v = car2.kmhtoms(150);
    car2.pCurrentRoad = &road5;

    float t = 0.0;
    for (int i = 0; i < totalFrameNum; i++) {
        t += dt;  // Keep track of overall time elapsed
        car0.update(world.roads, world.roadSourceMap);
        car1.update(world.roads, world.roadSourceMap);
        car2.update(world.roads, world.roadSourceMap);
    }

    world.cars.push_back(car0);
    world.cars.push_back(car1);
    world.cars.push_back(car2);

    e.writeCarsToCSV("../visual/data/car_data.csv", world.cars);
    return 0;
}

// For testing
/* int main() { */
/*     std::cout << bearing({0.0f, 0.0f}, {-0.70107f, 0.707107f}) << std::endl; */
/*     return 0; */
/* } */
