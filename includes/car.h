#include <string>

class Car {
    public:
        int length = 5;
        float v[2]; // Velocity
        float a[2]; // acceleration
        int x; // Position
        int y;
        Car* nextCar;
        Car() {
           ;  
        }
};
