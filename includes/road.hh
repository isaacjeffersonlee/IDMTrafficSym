#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include "../includes/common.h"


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
        std::vector<std::array<int, 2>> sinks; // (x, y) std::array<int, 2> for road exit/sink
        // Note: for intersections we can have multiple sinks, so we store them
        // in a vector and loop over the possible sinks each time step.
        int currentSinkIdx = 0; // Idx of the currently active sink

        Road(int uniqueID,
                std::array<int, 2> source,
                std::vector<std::array<int, 2>> sinks,
                std::array<int, 2> topLeft,
                std::array<int, 2> bottomRight)
            : uniqueID(uniqueID)
            , source(source)
            , sinks(sinks)
            , topLeft(topLeft)
            , bottomRight(bottomRight)
        {

            sink = sinks[currentSinkIdx];
            // Note: negative y because coordinates upside down.
            std::array<int, 2> unscaledFlowDir = {sink[0]-source[0], -(sink[1]-source[1])};
            flowDir = {(1/norm(unscaledFlowDir))*unscaledFlowDir[0],
            (1/norm(unscaledFlowDir))*unscaledFlowDir[1]};
            /* topLeft[0] = pTopLeft[0]; */
            /* topLeft[1] = pTopLeft[1]; */
            /* bottomRight[0] = pBottomRight[0]; */
            /* bottomRight[1] = pBottomRight[1]; */
        }

        void updateSink() {
            sink = sinks[currentSinkIdx];
        }
};
