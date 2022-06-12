#include <string>
#include <fstream>
#include <iostream>
/* #include "../includes/road.h" */
#include <vector>
class Map {
    public:
        int width;
        int height;
        std::vector<Road> roads;
        Map(int mapWidth, int mapHeight, std::vector<Road> roadVec) {
            width = mapWidth;
            height = mapHeight;
            roads = roadVec;  // Vector containing all road objects for the map
        }
        // Write the map data to a csv file with given name
        void writeMaptoFile(std::string fileName) {
            std::ofstream mapFile(fileName);
            mapFile << "map_width = " << width << '\n';
            mapFile << "map_height = " << height << '\n';
            mapFile << "road_number = " << roads.size() << '\n';
            for(Road r : roads) {
                mapFile << "# ---------------------------------------------\n";
                mapFile << "length" << r.uniqueID << " = " << r.length << '\n';
                mapFile << "orient" << r.uniqueID << " = " << '"' << r.orient <<
                    '"'<< '\n';
                mapFile << "source" << r.uniqueID << " = " <<
                    '[' << r.source[0] << ", " << r.source[1] << ']' << '\n';
                mapFile << "sink" << r.uniqueID << " = " <<
                    '[' << r.sink[0] << ", " << r.source[1] << ']' << '\n';
                mapFile << "flow_dir" << r.uniqueID << " = " << '"' <<
                    r.flowDir << '"'<< '\n';
                mapFile << "top_left" << r.uniqueID << " = " <<
                    '[' << r.topLeft[0] << ", " << r.topLeft[1] << ']' << '\n';
                mapFile << "bottom_right" << r.uniqueID << " = " <<
                    '[' << r.bottomRight[0] << ", " << r.bottomRight[1] <<
                    ']' << '\n';
            }
            std::cout << "Successfully wrote map to " << fileName << std::endl;
            mapFile.close();
        }

};
