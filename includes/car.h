#include <string>
#include <vector>
#include "../includes/common.h"



class Car {
    public:
        // Model params
        float v0 = 120.0; // Desired speed in km/h
        float T = 1.6;    // Reaction time in s
        float a = 0.73;   // Max acceleration in m/s^2
        float b = 1.67;   // Desired deceleration in m/s^2
        int delta = 4;    // Acceleration exponent
        float s0 = 1;     // Jam Distance
        int l = 5;        // Vehicle length
        // Positional attributes 
        float v = 0.0;    // Speed at time t
        std::vector<float> d;       // Direction/orientation at time t
        std::vector<float> dvdt;    // Acceleration at time t
        int x;            // x coordinate at time t
        int y;            // y coordinate at time t
        std::vector<std::vector<int>> carPos; // ith entry is the (x, y) of the car for frame i
        std::vector<std::vector<float>> carDir; // ith entry is the (d1, d2),
        // the direction of the car at frame i
        Car* m_nextCar;     // Car ahead
        bool isFirst = false;     // Is this car the first car?
        float roadOrientation;

        // Convert speed from km/h to m/s
        float _kmhtoms(float speedKmh) {return (speedKmh * 1000) / 3600;}

        Car(Car* nextCar = nullptr) {
            m_nextCar = nextCar;
            v0 = _kmhtoms(v0);
            v = _kmhtoms(v);
            if (!nextCar) {
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
                delta_t = v - (m_nextCar->v);
            }
            return delta_t;
        }
        // Return the bumper to bumper distance in px
        float getBumperDistance() {
            if (!isFirst) {  // There exists a car in front
                return (m_nextCar->x) - x - (l*10);
            }
            else {  // First car
                return 5000.0;
            }
        }
        // Update position and direction of the car
        void update() {
            // TODO: Implement orientation checking
            float distToNext = getBumperDistance();
            if (distToNext > (s0*10) && x < 870) {
                x += v * 10 * dt; // Multiply by 10 since we have 10px == 1m
            }   
            carPos.push_back({x, y});
            carDir.push_back(d);
        }
};
