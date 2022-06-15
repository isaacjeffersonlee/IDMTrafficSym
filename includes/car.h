#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <map>
#include "../includes/common.h"


typedef std::array<int, 2> intCoord;
typedef std::array<float, 2> floatCoord;

float dynamicCeil(float x) {
    if (x < 0.0f) {
        return std::floor(x);
    } 
    else {
        return std::ceil(x);
    }
}

class Car {
    public:
        // Model params
        float v0 = (120.0 * 1000) / 3600; // Desired speed in m/s
        float T = 1.6;    // Reaction time in s
        float a = 0.73;   // Max acceleration in m/s^2
        float b = 1.67;   // Desired deceleration in m/s^2
        int delta = 4;    // Acceleration exponent
        float s0 = 1;     // Jam Distance
        int l = 5;        // Vehicle length
        Road* currentRoad; // Road the car is currently driving along

        // Positional attributes 
        float v = 0.0;    // Speed at time t, in m/s
        floatCoord d;       // Direction/orientation at time t, scaled s.t |d| == 1
        floatCoord dvdt;    // Acceleration at time t
        int x;            // x intCoordinate at time t
        int y;            // y intCoordinate at time t
        std::vector<intCoord> carPos; // ith entry is the (x, y) of the car for frame i
        std::vector<floatCoord> carDir; // ith entry is the (d1, d2),
        // the direction of the car at frame i
        Car* nextCar;     // Car ahead
        bool isFirst = false;     // Is this car the first car?

        // Helper function to convert speed from km/h to m/s
        float kmhtoms(float speedKmh) {return (speedKmh * 1000) / 3600;}

        Car(Car* firstCar) {
            nextCar = firstCar;
            if (!firstCar) {
                isFirst = true;
                v = v0;
            }
        }
        // Return the difference in speeds for the car and the nextCar
        float getApproachRate() {
            float delta_t;
            if (isFirst) {
                delta_t = v0;
            }
            else {
                delta_t = v - (nextCar->v);
            }
            return delta_t;
        }
        // Return the bumper to bumper distance in px
        // Assumes cars have same orientation
        float getBumperDistance() {
            if (!isFirst) {  // There exists a car in front
                float center_diff = sqrt(pow((nextCar->y - y), 2) + pow((nextCar->x - x), 2));
                return center_diff - (l * 10);  // Account for length of car
            }
            else {  // First car
                return 5000.0;
            }
        }
        // Update position and direction of the car
        void update(std::vector<Road> roads, std::map<intCoord, int> roadSourceMap) {
            float eps = v * 10 * dt;
            // If sufficiently close to the sink coordinate
            if (sqrt(pow(currentRoad->sink[0]-x, 2) + pow(currentRoad->sink[1]-y, 2)) < eps) {
                currentRoad = &roads[roadSourceMap[currentRoad->sink]];
                x = currentRoad->source[0];
                y = currentRoad->source[1];
            }
            d = currentRoad->flowDir;  // Set the direction of the car to the
            // flow direction of the current road.
            float distToNext = getBumperDistance();
            if (distToNext > s0*10) {
                x += dynamicCeil(v*d[0] * 10 * dt); // Multiply by 10 since we have 10px == 1m
                y -= dynamicCeil(v*d[1] * 10 * dt); // Multiply by 10 since we have 10px == 1m
                // Negative y increment since (0,0) is at the top left
                // Also we use the ceil function because we cannot have fractions of pixels
            }   
            carPos.push_back({x, y});
            carDir.push_back(d);
        }
};
