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
    Car* pCar0 = new Car(nullptr);  // nullptr for first car
    /* Car car3(&pCar2); */
    pCar0->x = 600;  // Initial position
    pCar0->y = 880;
    pCar0->v = pCar0->kmhtoms(40);
    pCar0->pCurrentRoad = &road1;

    Car* pCar1 = new Car(pCar0);
    pCar1->x = 140;  // Initial position
    pCar1->y = 120;
    pCar1->v = pCar1->kmhtoms(120);
    pCar1->pCurrentRoad = &road5;

    Car* pCar2 = new Car(pCar1);
    pCar2->x = 500;  // Initial position
    pCar2->y = 120;
    pCar2->v = pCar2->kmhtoms(150);
    pCar2->pCurrentRoad = &road5;


    world.pCars.push_back(pCar0);
    world.pCars.push_back(pCar1);
    world.pCars.push_back(pCar2);

    float t = 0.0;
    for (int i = 0; i < totalFrameNum; i++) {
        t += dt;  // Keep track of overall time elapsed
        world.updateWorld();
    }

    e.writeCarsToCSV("../visual/data/car_data.csv", world.pCars);
    world.deleteObjects();

    return 0;
}

// For testing
/* int main() { */
/*     std::cout << bearing({0.0f, 0.0f}, {-0.70107f, 0.707107f}) << std::endl; */
/*     return 0; */
/* } */
