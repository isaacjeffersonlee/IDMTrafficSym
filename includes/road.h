#include <string>
#include <iostream>
#include <vector>
#include <array>
#include "../includes/common.h"

typedef std::array<int, 2> coord;

class Road {
    public:
        int uniqueID;
        int length;
        std::string orient;  // Either "horiz" for horizontal or "vert" for vertical
        coord source;  // (x, y) coord for road entrance/source
        coord sink;  // (x, y) coord for road exit/sink
        std::string flowDir;  // "up", "down", "left", or "right"
        coord topLeft;
        coord bottomRight;
        // source road 
        // sink road
        Road(int roadUniqueID, std::string roadFlowDir,
                coord roadTopLeft, coord roadBottomRight) {
            uniqueID = roadUniqueID;
            flowDir = roadFlowDir;
            topLeft[0] = roadTopLeft[0];
            topLeft[1] = roadTopLeft[1];
            bottomRight[0] = roadBottomRight[0];
            bottomRight[1] = roadBottomRight[1];
            int roadWidth = roadBottomRight[0] - roadTopLeft[0];
            int roadHeight = roadBottomRight[1] - roadTopLeft[1];
            length = std::max(roadWidth, roadHeight);
            if (roadWidth < roadHeight) {
                orient = "vert";
                if (roadFlowDir == "up") {
                    source[0] = roadBottomRight[0] - (roadWidth/2);
                    source[1] = roadBottomRight[1];
                    sink[0] = roadTopLeft[0] + (roadWidth/2);
                    sink[1] = roadTopLeft[1];
                }
                else if (roadFlowDir == "down") {
                    source[0] = roadTopLeft[0] + (roadWidth/2);
                    source[1] = roadTopLeft[1];
                    sink[0] = roadBottomRight[0] - (roadWidth/2);
                    sink[1] = roadBottomRight[1];
                }
                else {
                    std::cout << roadFlowDir << " is not a valid flow direction!" << std::endl;
                }
            }
            else {
                orient = "horiz";
                if (roadFlowDir == "left") {
                    source[0] = roadBottomRight[0];
                    source[1] = roadTopLeft[1] - (roadHeight/2);
                    sink[0] = roadTopLeft[0];
                    sink[1] = roadTopLeft[1] - (roadHeight/2);
                }
                else if (roadFlowDir == "right") {
                    source[0] = roadTopLeft[0];
                    source[1] = roadTopLeft[1] - (roadHeight/2);
                    sink[0] = roadBottomRight[0];
                    sink[1] = roadTopLeft[1] - (roadHeight/2);
                }
                else {
                    std::cout << roadFlowDir << " is not a valid flow direction!" << std::endl;
                }
            }
        }
};
