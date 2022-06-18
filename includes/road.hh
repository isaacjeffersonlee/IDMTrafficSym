#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include "../includes/common.hh"


float norm(std::array<int, 2> v) {
    return sqrt(pow(v[0], 2) + pow(v[1], 2));
}

class Road {

    public:
        int uniqueID;
        std::array<float, 2> flowDir;  // Scaled to have length 1
        std::array<int, 2> topLeft;
        std::array<int, 2> bottomRight;
        std::array<int, 2> source;  // (x, y) std::array<int, 2> for road entrance/source
        std::array<int, 2> sink;
        std::vector<std::array<int, 2>> sources; // (x, y) std::array<int, 2> for road entry/source
        std::vector<std::array<int, 2>> sinks; // (x, y) std::array<int, 2> for road exit/sink
        // Note: for intersections we can have multiple sinks, so we store them
        // in a vector and loop over the possible sinks each time step.
        int currentSourceIdx = 0; // Idx of the currently active sink
        int currentSinkIdx = 0; // Idx of the currently active sink
        // Traffic Light Attributes
        bool isIntersection;
        float trafficLightDelay = 10.0f;  // Time interval between green and red lights, in seconds
        std::vector<std::array<int, 4>> lightCoords;  // {x_source, y_source, x_sink, y_sink} for ith frame
        // Spawning Attributes
        int spawnMode = 0; // 0 : Normal road, 1 : spawn point, -1 : despawn point
        // Number of cars currently on the road
        int carNumber = 0;

        void updateFlowDir() {
            // Note: negative y because coordinates upside down.
            std::array<int, 2> unscaledFlowDir = {sink[0]-source[0], -(sink[1]-source[1])};
            flowDir = {(1/norm(unscaledFlowDir))*unscaledFlowDir[0],
            (1/norm(unscaledFlowDir))*unscaledFlowDir[1]};
        }

        Road(int uniqueID,
                std::vector<std::array<int, 2>> sources,
                std::vector<std::array<int, 2>> sinks,
                std::array<int, 2> topLeft,
                std::array<int, 2> bottomRight,
                int spawnMode)
            : uniqueID(uniqueID)
            , sources(sources)
            , sinks(sinks)
            , topLeft(topLeft)
            , bottomRight(bottomRight)
            , spawnMode(spawnMode)
        {
            source = sources[currentSourceIdx];
            sink = sinks[currentSinkIdx];
            if (sources.size() > 1 || sinks.size() > 1) {
                isIntersection = true;
            }
            else {
                isIntersection = false;
            }
            updateFlowDir();
        }

        // Update the state of the traffic light for the given road.
        void updateLight() {
            // Need to check no cars on the road when we switch or else
            // we get weird behaviour.
            if (isIntersection && carNumber == 0) {
                currentSourceIdx = (currentSourceIdx + 1) % sources.size();
                currentSinkIdx = (currentSinkIdx + 1) % sinks.size();
                source = sources[currentSourceIdx];
                sink = sinks[currentSinkIdx];
                updateFlowDir();
            }
        }
};
