#include <string>
#include <iostream>
#include <vector>

class Road {
    public:
        int uniqueID;
        int length;
        std::string orient;  // Either "horiz" for horizontal or "vert" for vertical
        int source[2];  // (x, y) coord for road entrance/source
        int sink[2];  // (x, y) coord for road exit/sink
        std::string flowDir;  // "up", "down", "left", or "right"
        std::vector<int> topLeft;
        std::vector<int> bottomRight;
        // source road 
        // sink road
        Road(int roadUniqueID, std::string roadFlowDir,
                std::vector<int> roadTopLeft, std::vector<int> roadBottomRight) {
            uniqueID = roadUniqueID;
            flowDir = roadFlowDir;
            topLeft = roadTopLeft;
            bottomRight = roadBottomRight;
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
