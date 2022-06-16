#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <map>
#include "../includes/common.h"

#define PI 3.14159265f

float absCeil(float x) {
    if (x < 0.0f) {
        return std::floor(x);
    } 
    else {
        return std::ceil(x);
    }
}

// Returning the bearing in degrees measured anti-clockwise from North
// of the vector from a to b
float bearing(std::array<float, 2> a, std::array<float, 2> b) {
    float dy = b[1] - a[1];
    float dx = b[0] - a[0];
    return fmod(((std::atan2(dy, dx) * (180.0f/PI)) - 90.0f), 360.0f);
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
        std::array<float, 2> d;       // Direction/orientation at time t, scaled s.t |d| == 1
        float angle;      // Car bearing, measured anticlockwise from N in degrees
        int x;            // x std::array<int, 2>inate at time t
        int y;            // y std::array<int, 2>inate at time t
        std::vector<std::array<int, 2>> carPos; // ith entry is the (x, y) of the car for frame i
        std::vector<std::array<float, 2>> carDir; // ith entry is the (d1, d2),
        // the direction of the car at frame i
        std::vector<float> carAngle; // ith entry is the 
        // compass bearing in degrees of the car at time i
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
            float delta_v;
            if (isFirst) {
                delta_v = v0;
            }
            else {
                delta_v = v - (nextCar->v);
            }
            return delta_v;
        }
        // Return the bumper to bumper distance in px
        // Assumes cars have same orientation
        float getBumperDistance() {
            if (isFirst) {  // There exists a car in front
                return 5000.0f;
            }
            else {  // First car
                float center_diff = std::hypot(nextCar->x - x, nextCar->y - y);
                return std::max(center_diff - (l * 10), 0.0f);  // Account for length of car
            }
        }

        // Return the dvdt, i.e the acceleration for the current frame.
        float getAcceleration() {
            if (isFirst) {
                return 0.0f;
            }
            else {
                float delta_v = getApproachRate();
                float s = s0 + T*v + ((v * delta_v)/(2*sqrt(a*b)));
                float bumpDist = getBumperDistance();  // Distance to next car
                return a * (1 - pow((v/v0), delta) - (s/bumpDist)*(s/bumpDist));
            }
        }

        // Update position and direction of the car
        void update(std::vector<Road> roads, std::map<std::array<int, 2>, int> roadSourceMap) {
            float eps = v * 10 * dt;
            // If sufficiently close to the sink coordinate
            if (std::hypot(currentRoad->sink[0] - x, currentRoad->sink[1] - y) < eps) {
                currentRoad = &roads[roadSourceMap[currentRoad->sink]];
                x = currentRoad->source[0];
                y = currentRoad->source[1];
            }
            d = currentRoad->flowDir;  // Set the direction of the car to the
            angle = std::ceil(bearing({0.0f, 0.0f}, d));
            // flow direction of the current road.
            float distToNext = getBumperDistance();
            if (distToNext > s0*10) {
                x += absCeil(v*d[0] * 10 * dt); // Multiply by 10 since we have 10px == 1m
                y -= absCeil(v*d[1] * 10 * dt); // Multiply by 10 since we have 10px == 1m
                // Negative y increment since (0,0) is at the top left
                // Also we use the ceil function because we cannot have fractions of pixels
            }   
            carPos.push_back({x, y});
            carDir.push_back(d);
            carAngle.push_back(angle);
            float dvdt = getAcceleration();
            // Update speed using acceleration
            v += dvdt * dt;
        }
};
