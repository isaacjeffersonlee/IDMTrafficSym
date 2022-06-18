#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "../includes/road.hh"
#include "../includes/car.hh"
#include "../includes/world.hh"
#include "../includes/common.hh"
#include "../includes/exporter.hh"

float fps = 50.0;                   // Frames per second
float dt = 1 / fps;                 // Time between frames
bool export_data = true;            // Set false to prevent writing to files
float simTime = 60;                 // Simulation time in seconds
int totalFrameNum = simTime / dt;   // Total number of frames


// For lane change MOBIL model
// https://traffic-simulation.de/info/info_MOBIL.html

// Note: We are assuming 10px == 1m irl


int main() {
    // Circular road layout
    /* Road* pRoad0 = new Road(0, {{120, 860}}, {{140, 880}}, {100, 860}, {140, 900}); */
    /* Road* pRoad1 = new Road(1, {{140, 880}}, {{860, 880}}, {140, 860}, {860, 900}); */
    /* Road* pRoad2 = new Road(2, {{860, 880}}, {{880, 860}}, {860, 860}, {900, 900}); */
    /* Road* pRoad3 = new Road(3, {{880, 860}}, {{880, 140}}, {860, 140}, {900, 860}); */
    /* Road* pRoad4 = new Road(4, {{880, 140}}, {{860, 120}}, {860, 100}, {900, 140}); */
    /* Road* pRoad5 = new Road(5, {{860, 120}}, {{140, 120}}, {140, 100}, {860, 140}); */
    /* Road* pRoad6 = new Road(6, {{140, 120}}, {{120, 140}}, {100, 100}, {140, 140}); */
    /* Road* pRoad7 = new Road(7, {{120, 140}}, {{120, 860}}, {100, 140}, {140, 860}); */
    /* std::vector<Road *> pRoads = {pRoad0, pRoad1, pRoad2, pRoad3, pRoad4, pRoad5, pRoad6, pRoad7}; */
    
    // Simple Interseciton road layout
    Road* pRoad0 = new Road(0, {{100, 420}}, {{500, 420}}, {100, 400}, {500, 440}, 0);
    Road* pRoad1 = new Road(1, {{500, 420}}, {{520, 440}, {520, 400}}, {500, 400}, {540, 440}, 0);
    Road* pRoad2 = new Road(2, {{520, 400}}, {{520, 100}}, {500, 100}, {540, 400}, 0);
    Road* pRoad3 = new Road(3, {{520, 440}}, {{520, 740}}, {500, 440}, {540, 740}, 0);
    Road* pRoad4 = new Road(4, {{520, 740}}, {{520, 780}}, {500, 740}, {540, 780}, -1);
    Road* pRoad5 = new Road(5, {{520, 100}}, {{520, 60}}, {500, 60}, {540, 100}, -1);
    std::vector<Road *> pRoads = {pRoad0, pRoad1, pRoad2, pRoad3, pRoad4, pRoad5};

    World world(1000, 1000, pRoads);

    // Initialize our exporter object
    Exporter e = Exporter(true);
    // Export pRoad data to a csv file so that we can read it in in Python
    e.writeRoadsToCSV("../visual/data/road_data.csv", pRoads);

    // Setup Car Objects
    Car* pCar0 = new Car(nullptr);  // nullptr for first car
    /* Car car3(&pCar2); */
    pCar0->x = 400;  // Initial position
    pCar0->y = 420;
    pCar0->v = pCar0->kmhtoms(180);
    pCar0->pCurrentRoad = pRoad0;

    /* Car* pCar1 = new Car(pCar0); */
    /* pCar1->x = 200;  // Initial position */
    /* pCar1->y = 420; */
    /* pCar1->v = pCar1->kmhtoms(40); */
    /* pCar1->pCurrentRoad = pRoad0; */

    /* Car* pCar2 = new Car(pCar1); */
    /* pCar2->x = 100;  // Initial position */
    /* pCar2->y = 420; */
    /* pCar2->v = pCar2->kmhtoms(20); */
    /* pCar2->pCurrentRoad = pRoad0; */


    world.pCars.push_back(pCar0);
    /* world.pCars.push_back(pCar1); */
    /* world.pCars.push_back(pCar2); */

    float t = 0.0;
    for (int i = 0; i < totalFrameNum; i++) {
        t += dt;  // Keep track of overall time elapsed
        world.updateWorld(t);
    }

    e.writeCarsToCSV("../visual/data/car_data.csv", world.pCars);
    e.writeTrafficLightsToCSV("../visual/data/light_data.csv", world.pRoads);
    world.deleteObjects();

    return 0;
}

// For testing
/* int main() { */
/*     std::cout << bearing({0.0f, 0.0f}, {-0.70107f, 0.707107f}) << std::endl; */
/*     return 0; */
/* } */
