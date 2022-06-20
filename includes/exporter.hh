#include <fstream>
#include <string>
#include <array>
#include <vector>
#include "../includes/common.hh"


class Exporter {

    public:

        bool exportData = true;

        Exporter(bool exportData) : exportData(exportData) {}
        // Convert a std::array<int, 2> {i, j} to a string of the form "[i, j]"
        std::string _arrToPyListString(std::array<int, 2> intArr) {
            std::string pyListString = '[' + std::to_string(intArr[0]) + ',' + 
                std::to_string(intArr[1]) + ']';
            return pyListString;
        }

        std::string _arrToPyListString(std::array<float, 2> floatArr) {
            std::string pyListString = '[' + std::to_string(floatArr[0]) + ',' + 
                std::to_string(floatArr[1]) + ']';
            return pyListString;
        }

        // Write the map data to a csv file with given fileName
        void writeRoadsToCSV(std::string fileName, std::vector<Road *> pRoads) {
            if (exportData) {
                std::ofstream roadFile(fileName);
                // Road class attributes for column names
                roadFile << "uniqueID;flowDir;topLeft;bottomRight\n";
                for(Road* pRoad : pRoads) {
                    roadFile << pRoad->uniqueID << ';' << _arrToPyListString(pRoad->flowDir) <<
                        ';' << _arrToPyListString(pRoad->topLeft) << ';' <<
                        _arrToPyListString(pRoad->bottomRight) << '\n';
                }
                std::cout << "Successfully wrote road data to " << fileName << std::endl;
                roadFile.close();
            }
        }

        // Write the traffic light coordinate data to a csv file with given fileName
        void writeTrafficLightsToCSV(std::string fileName, std::vector<Road *> pRoads) {
            if (exportData) {
                std::ofstream lightFile(fileName);
                // Road class attributes for column names
                for (int i = 0; i < totalFrameNum; i++) {
                    for (Road* pRoad : pRoads) {
                        lightFile << pRoad->lightCoords[i][0] << ',' << 
                        pRoad->lightCoords[i][1] << ',' << 
                        pRoad->lightCoords[i][2] << ',' << 
                        pRoad->lightCoords[i][3] << ';';
                    }
                    lightFile << '\n';
                }
                std::cout << "Successfully wrote lights to " << fileName << std::endl;
                lightFile.close();
            }
        }
        // Save the pCars position and angle information for each time frame
        // for each car to a csv file.
        void writeCarsToCSV(std::string fileName, std::vector<Car *> pCars) {
            if (exportData) {
                std::ofstream carFile(fileName);
                for (int i = 0; i < totalFrameNum; i++) {
                    int x_i;
                    int y_i;
                    float angle_i;
                    for (Car* pCar : pCars) {
                        int exportOffset = pCar->spawnFrameIdx;
                        if (i >= exportOffset) {
                            x_i = pCar->carPos[i-exportOffset][0];
                            y_i = pCar->carPos[i-exportOffset][1];
                            angle_i = pCar->carAngle[i-exportOffset];
                        }
                        else {
                            x_i = -1500;
                            y_i = -1500;
                            angle_i = -69.0f;
                        }
                        carFile << x_i << ',' << y_i <<
                            ',' << angle_i << ';';
                    }
                    carFile << '\n';
                }
                std::cout << "Successfully wrote car data to " << fileName << std::endl;
                carFile.close();
            }
        }

    void writeTravelTimesToCSV(std::string fileName, std::vector<float> travelTimes) {
        std::ofstream timeFile(fileName);
        for (float t : travelTimes) {
            timeFile << t << '\n';
        }
        timeFile.close();
    }
};
