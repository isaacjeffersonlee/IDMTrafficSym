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
bool visualizeData = false;            // Set false to prevent writing to files
float simTime = 30;                 // Simulation time in seconds
int totalFrameNum = simTime / dt;   // Total number of frames
int numParamSweeps = 100;           // We'll do 20 sweeps per param

void printSimInfo(int simNum, float T, float a, float b, int delta, float s0) {
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Simulation number: " << simNum << " complete!" << std::endl;
    std::cout << "Parameters used: " << T << " | " << a << " | " << b <<
        " | " << delta << " | " << s0 << std::endl;
}

int main() {
    World world(1000, 1000, pRoads, {1, 62, 58, 55}, visualizeData);
    // Parameters
    float T = 1.6;    // Reaction time in s
    float a = 0.73;   // Max acceleration in m/s^2
    float b = 1.67;   // Desired deceleration in m/s^2
    int delta = 4;    // Acceleration exponent
    float s0 = 1.0f;     // Jam Distance
    std::vector<std::vector<float>> allTravelTimes;
    std::vector<float> TVals;
    std::vector<float> aVals;
    std::vector<float> bVals;
    std::vector<int> deltaVals;
    std::vector<float> s0Vals;
    int simNum = 0;  // For idx


    float TMin = 0.5f;
    float TMax = 5.0f;
    float dT = (TMax-TMin) / (numParamSweeps/5);
    for (int i = 0; i < (numParamSweeps/5); i++) {
        T = TMin + (i*dT);
        std::vector<float> travelTimes = world.runSim(T, a, b, delta, s0);
        allTravelTimes.push_back(travelTimes);
        world.travelTimes = {}; // TODO: Better method for resetting this
        TVals.push_back(T);
        aVals.push_back(a);
        bVals.push_back(b);
        deltaVals.push_back(delta);
        s0Vals.push_back(s0);
        simNum += 1;
        printSimInfo(simNum, T, a, b, delta, s0);
    }
    T = 1.6f;

    float aMin = 0.1;
    float aMax = 2.1f;
    float da = (aMax-aMin) / (numParamSweeps/5);
    for (int i = 0; i < (numParamSweeps/5); i++) {
        a = aMin + (i*da);
        std::vector<float> travelTimes = world.runSim(T, a, b, delta, s0);
        allTravelTimes.push_back(travelTimes);
        world.travelTimes = {}; // TODO: Better method for resetting this
        TVals.push_back(T);
        aVals.push_back(a);
        bVals.push_back(b);
        deltaVals.push_back(delta);
        s0Vals.push_back(s0);
        simNum += 1;
        printSimInfo(simNum, T, a, b, delta, s0);
    }
    a = 0.73f;

    float bMin = 0.1;
    float bMax = 2.1f;
    float db = (bMax-bMin) / (numParamSweeps/5);
    for (int i = 0; i < (numParamSweeps/5); i++) {
        b = bMin + (i*db);
        std::vector<float> travelTimes = world.runSim(T, a, b, delta, s0);
        allTravelTimes.push_back(travelTimes);
        world.travelTimes = {}; // TODO: Better method for resetting this
        TVals.push_back(T);
        aVals.push_back(a);
        bVals.push_back(b);
        deltaVals.push_back(delta);
        s0Vals.push_back(s0);
        simNum += 1;
        printSimInfo(simNum, T, a, b, delta, s0);
    }
    b = 1.67f;

    int deltaMin = 1;
    int deltaMax = 21;
    float dDelta = (deltaMax-deltaMin) / (numParamSweeps/5);
    for (int i = 0; i < (numParamSweeps/5); i++) {
        delta = deltaMin + (i*dDelta);
        std::vector<float> travelTimes = world.runSim(T, a, b, delta, s0);
        allTravelTimes.push_back(travelTimes);
        world.travelTimes = {}; // TODO: Better method for resetting this
        TVals.push_back(T);
        aVals.push_back(a);
        bVals.push_back(b);
        deltaVals.push_back(delta);
        s0Vals.push_back(s0);
        simNum += 1;
        printSimInfo(simNum, T, a, b, delta, s0);
    }
    delta = 4;

    float s0Min = 0.5f;
    float s0Max = 4.5f;
    float ds0 = (s0Max-s0Min) / (numParamSweeps/5);
    for (int i = 0; i < (numParamSweeps/5); i++) {
        s0 = s0 + (i*ds0);
        std::vector<float> travelTimes = world.runSim(T, a, b, delta, s0);
        allTravelTimes.push_back(travelTimes);
        world.travelTimes = {}; // TODO: Better method for resetting this
        TVals.push_back(T);
        aVals.push_back(a);
        bVals.push_back(b);
        deltaVals.push_back(delta);
        s0Vals.push_back(s0);
        simNum += 1;
        printSimInfo(simNum, T, a, b, delta, s0);
    }
    s0 = 1.0f;

    Exporter paramSweepExporter = Exporter(true);
    paramSweepExporter.writeTravelTimesAndParamsToCSV("../visual/data/param_sweep.csv",
            numParamSweeps,
            allTravelTimes, TVals, aVals, bVals, deltaVals, s0Vals);
    std::cout << "Exported to csv!" << std::endl;
    world.deleteCars();
    world.deleteRoads();
    std::cout << "Finished!" << std::endl;
    return 0;
}

// For testing
/* int main() { */
/*     std::cout << bearing({0.0f, 0.0f}, {-0.70107f, 0.707107f}) << std::endl; */
/*     return 0; */
/* } */
