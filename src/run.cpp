#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "../includes/road.hh"
#include "../includes/car.hh"
#include "../includes/world.hh"
#include "../includes/common.hh"
/* #include "../includes/exporter.hh" */

// Note: We are assuming 10px == 1m irl
float fps = 50.0;                   // Frames per second
float dt = 1 / fps;                 // Time between frames
bool exportData = false;            // Set false to prevent writing to files
float simTime = 30;                 // Simulation time in seconds
int totalFrameNum = simTime / dt;   // Total number of frames

int main() {
    World world(1000, 1000, pRoads, {1, 62, 58, 55});
    Exporter e = Exporter(exportData);
    // Export pRoad data to a csv file so that we can read it in in Python
    e.writeRoadsToCSV("../visual/data/road_data.csv", pRoads);

    float T = 1.6;    // Reaction time in s
    float a = 0.73;   // Max acceleration in m/s^2
    float b = 1.67;   // Desired deceleration in m/s^2
    int delta = 4;    // Acceleration exponent
    float s0 = 1;     // Jam Distance
    std::vector<float> carTimes = world.runSim(exportData, T, a, b, delta, s0);
    std::cout << carTimes[0] << std::endl;

    return 0;
}

// For testing
/* int main() { */
/*     std::cout << bearing({0.0f, 0.0f}, {-0.70107f, 0.707107f}) << std::endl; */
/*     return 0; */
/* } */
