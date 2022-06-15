#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include "../includes/common.h"

typedef std::array<int, 2> intCoord;
typedef std::array<float, 2> floatCoord;


float norm(std::array<int, 2> v) {
    return sqrt(pow(v[0], 2) + pow(v[1], 2));
}

class Road {
    public:
        int uniqueID;
        floatCoord flowDir;  // Scaled to have length 1
        intCoord topLeft;
        intCoord bottomRight;
        intCoord source;  // (x, y) intCoord for road entrance/source
        intCoord sink;
        std::vector<intCoord> sinks; // (x, y) intCoord for road exit/sink
        // Note: for intersections we can have multiple sinks, so we store them
        // in a vector and loop over the possible sinks each time step.
        int currentSinkIdx = 0; // Idx of the currently active sink
        Road(int roadUniqueID, intCoord roadSource, std::vector<intCoord> roadSinks,
                intCoord roadTopLeft, intCoord roadBottomRight) {
            uniqueID = roadUniqueID;
            source = roadSource;
            sinks = roadSinks;
            sink = sinks[currentSinkIdx];
            // Note: negative y because coordinates upside down.
            intCoord unscaledFlowDir = {sink[0]-source[0], -(sink[1]-source[1])};
            flowDir = {(1/norm(unscaledFlowDir))*unscaledFlowDir[0],
            (1/norm(unscaledFlowDir))*unscaledFlowDir[1]};
            topLeft[0] = roadTopLeft[0];
            topLeft[1] = roadTopLeft[1];
            bottomRight[0] = roadBottomRight[0];
            bottomRight[1] = roadBottomRight[1];
        }
        void updateSink() {
            sink = sinks[currentSinkIdx];
        }
};
