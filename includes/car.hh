#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <map>
#include "../includes/common.hh"

#define PI 3.14159265f

// Helper functions
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
        int uniqueID = 0;
        // Model params
        float v0 = kmhtoms(120.0f); // Desired speed in m/s
        float T = 1.6;    // Reaction time in s
        float a = 0.73;   // Max acceleration in m/s^2
        float b = 1.67;   // Desired deceleration in m/s^2
        int delta = 4;    // Acceleration exponent
        float s0 = 1;     // Jam Distance
        int l = 5;        // Vehicle length
        Road* pCurrentRoad; // Road the car is currently driving along
        Road* pStartRoad; // Road the car starts on
        // Positional attributes 
        float v;    // Speed at time t, in m/s
        float dvdt = 0.0;    // Acceleration at time t, in m/s^2
        std::array<float, 2> d;       // Direction/orientation at time t, scaled s.t |d| == 1
        float angle;      // Car bearing, measured anticlockwise from N in degrees
        int x;            // x coordinate at time t
        int y;            // y coordinate at time t
        std::vector<std::array<int, 2>> carPos; // ith entry is the (x, y) of the car for frame i
        std::vector<std::array<float, 2>> carDir; // ith entry is the (d1, d2),
        // the direction of the car at frame i
        std::vector<float> carAngle; // ith entry is the 
        // compass bearing in degrees of the car at time i
        Car *pNextCar;     // Car ahead
        bool isFirst = false;     // Is this car the first car?
        bool despawn = false;
        int spawnIdx;    // Index of the spawn point coord for world.spawnCoords
        int spawnFrameIdx;   // Time at which the car is spawned, in seconds

        // Helper function to convert speed from km/h to m/s
        float kmhtoms(float speedKmh) {return (speedKmh * 1000) / 3600;}

        Car(Car* pNextCar, Road* pStartRoad,
                int spawnIdx, int spawnFrameIdx,
                float desiredSpeedKmh,
                float T,
                float a,
                float b,
                int delta,
                float s0)
            : pNextCar(pNextCar)
            , pStartRoad(pStartRoad)
            , spawnIdx(spawnIdx)
            , spawnFrameIdx(spawnFrameIdx)
            , T(T)
            , a(a)
            , b(b)
            , delta(delta)
            , s0(s0)
        {
            pCurrentRoad = pStartRoad;
            v0 = kmhtoms(desiredSpeedKmh);
            v = v0;
            x = pStartRoad->source[0];
            y = pStartRoad->source[1];
            if (!pNextCar) {
                isFirst = true;
            }
        }
        // Return the difference in speeds for the car and the pNextCar
        float getApproachRate() {
            float delta_v;
            if (isFirst) {
                delta_v = v0;
            }
            else {
                delta_v = v - (pNextCar->v);
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
                float center_diff = std::hypot(pNextCar->x - x, pNextCar->y - y);
                return std::max(center_diff - (l * 10), 0.01f);  // Avoid zero division errors
            }

        }

        // Return the distance to the current sink coordinate
        float getCenterDistToSink() {
            float s = std::hypot(pCurrentRoad->sink[0] - x, pCurrentRoad->sink[1] - y);
            return s;
        }

        // Return the dvdt, i.e the acceleration for the current frame.
        float getAcceleration(bool nextRoadisIntersection) {
            if (!nextRoadisIntersection) {
                if (isFirst) {
                    if (v < v0) {
                        return 20.0f;
                    }
                    else {
                        return 0.0f;  // Don't accelerate if at desired speed
                    }
                }
                else {
                    float delta_v = getApproachRate();
                    float s = s0 + T*v + ((v * delta_v)/(2*sqrt(a*b)));
                    float bumpDist = getBumperDistance();  // Distance to next car
                    return a * (1 - pow((v/v0), delta) - (s/bumpDist)*(s/bumpDist));
                }
            }
            else {  // Next road is a traffic light
                float delta_v = v;
                float s = s0 + T*v + ((v * delta_v)/(2*sqrt(a*b)));
                float center_diff = getCenterDistToSink();
                float bumpDist = std::max(center_diff - (0.5f*l*10), 1.0f);  // Account for length of car
                return a * (1 - pow((v/v0), delta) - (s/bumpDist)*(s/bumpDist));
            }
        }

        // Append the car position information vectors (used for exporting)
        // with the cars current x,y direction, d and angle.
        void updateExportInfo() {
            carPos.push_back({x, y});
            carDir.push_back(d);
            carAngle.push_back(angle);
        }

        // Update position and direction of the car
        void updateCar(std::vector<Road *> pRoads, std::map<std::array<int, 2>, int> roadSourceMap) {
            if (pCurrentRoad->spawnMode == -1) {
                despawn = true;
            }
            else {
                Road* pNextRoad = pRoads[roadSourceMap[pCurrentRoad->sink]];
                float eps = v * 10 * dt;
                bool nextRoadisIntersection = false;
                if (pNextRoad->source != pCurrentRoad->sink) {  // Red Light
                    nextRoadisIntersection = true;
                    float center_diff = getCenterDistToSink();
                    float bumpDist = std::max(center_diff - (0.5f*l*10), 0.0f);  // Account for length of car
                    if (bumpDist < eps) {
                        v = 0.0f;
                    }
                }
                else { // Green Light
                    // If sufficiently close to the sink coordinate
                    if (getCenterDistToSink() < eps) {
                        pCurrentRoad->carNumber -= 1;
                        pCurrentRoad = pNextRoad;
                        pCurrentRoad->carNumber += 1;
                        // Reset x and y to avoid weird behaviour when turning
                        x = pCurrentRoad->source[0];
                        y = pCurrentRoad->source[1];
                    }
                }
                // Flow direction of the current road.
                d = pCurrentRoad->flowDir;  // Set the direction of the car to the
                angle = std::ceil(bearing({0.0f, 0.0f}, d));
                dvdt = getAcceleration(nextRoadisIntersection);
                // Update speed using acceleration
                if (getBumperDistance() > s0*10) {
                    // Negative y increment since (0,0) is at the top left
                    // Also we use the ceil function because we cannot have fractions of pixels
                    v += dvdt * dt;
                    x += absCeil(v*d[0] * 10 * dt); // Multiply by 10 since we have 10px == 1m
                    y -= absCeil(v*d[1] * 10 * dt); // Multiply by 10 since we have 10px == 1m
                }   
            }
            updateExportInfo();
        }
};
