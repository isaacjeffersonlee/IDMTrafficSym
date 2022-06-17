#include <fstream>
#include <array>
#include <vector>
#include "../includes/common.h"

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
        void writeRoadsToCSV(std::string fileName, std::vector<Road> roads) {
            if (exportData) {
                std::ofstream mapFile(fileName);
                // Road class attributes for column names
                mapFile << "uniqueID;flowDir;topLeft;bottomRight\n";
                for(Road r : roads) {
                    mapFile << r.uniqueID << ';' << _arrToPyListString(r.flowDir) <<
                        ';' << _arrToPyListString(r.topLeft) << ';' <<
                        _arrToPyListString(r.bottomRight) << '\n';
                }
                std::cout << "Successfully wrote map to " << fileName << std::endl;
                mapFile.close();
            }
        }

        // Save the cars position and angle information for each time frame
        // for each car to a csv file.
        void writeCarsToCSV(std::string fileName, std::vector<Car> cars) {
            if (exportData) {
                std::ofstream carFile(fileName);
                for (int i = 0; i < totalFrameNum; i++) {
                    for (Car c : cars) {
                        carFile << c.carPos[i][0] << ',' << c.carPos[i][1] <<
                            /* ',' << c.carDir[i][0] << ',' << c.carDir[i][1] << */ 
                            ',' << c.carAngle[i] << ';';
                    }
                    carFile << '\n';
                }
                std::cout << "Successfully wrote cars to " << fileName << std::endl;
                carFile.close();
            }
        }
};
