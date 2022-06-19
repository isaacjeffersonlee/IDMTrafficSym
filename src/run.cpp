#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "../includes/road.hh"
#include "../includes/car.hh"
#include "../includes/world.hh"
#include "../includes/common.hh"
#include "../includes/exporter.hh"

float fps = 50.0;                   // Frames per second
float dt = 1 / fps;                 // Time between frames
bool export_data = true;            // Set false to prevent writing to files
float simTime = 60;                 // Simulation time in seconds
int totalFrameNum = simTime / dt;   // Total number of frames


// Note: We are assuming 10px == 1m irl


int main() {
    // Circular road layout
    /* Road* pRoad0 = new Road(0, {{120, 860}}, {{140, 880}}, {100, 860}, {140, 900}); */
    /* Road* pRoad1 = new Road(1, {{140, 880}}, {{860, 880}}, {140, 860}, {860, 900}); */
    /* Road* pRoad2 = new Road(2, {{860, 880}}, {{880, 860}}, {860, 860}, {900, 900}); */
    /* Road* pRoad3 = new Road(3, {{880, 860}}, {{880, 140}}, {860, 140}, {900, 860}); */
    /* Road* pRoad4 = new Road(4, {{880, 140}}, {{860, 120}}, {860, 100}, {900, 140}); */
    /* Road* pRoad5 = new Road(5, {{860, 120}}, {{140, 120}}, {140, 100}, {860, 140}); */
    /* Road* pRoad6 = new Road(6, {{140, 120}}, {{120, 140}}, {100, 100}, {140, 140}); */
    /* Road* pRoad7 = new Road(7, {{120, 140}}, {{120, 860}}, {100, 140}, {140, 860}); */
    /* std::vector<Road *> pRoads = {pRoad0, pRoad1, pRoad2, pRoad3, pRoad4, pRoad5, pRoad6, pRoad7}; */
    
    // Simple Interseciton road layout
    /* Road* pRoad0 = new Road(0, {{100, 420}}, {{500, 420}}, {100, 400}, {500, 440}, 0); */
    /* Road* pRoad1 = new Road(1, {{500, 420}, {520, 400}}, {{540, 420}, {520, 440}}, {500, 400}, {540, 440}, 0); */
    /* Road* pRoad2 = new Road(2, {{520, 100}}, {{520, 400}}, {500, 100}, {540, 400}, 0); */
    /* Road* pRoad3 = new Road(3, {{520, 440}}, {{520, 740}}, {500, 440}, {540, 740}, 0); */
    /* Road* pRoad4 = new Road(4, {{520, 740}}, {{520, 780}}, {500, 740}, {540, 780}, -1); */
    /* Road* pRoad5 = new Road(5, {{520, 100}}, {{520, 60}}, {500, 60}, {540, 100}, -1); */
    /* Road* pRoad6 = new Road(6, {{540, 420}}, {{800, 420}}, {540, 400}, {800, 440}, 0); */
    /* Road* pRoad7 = new Road(7, {{800, 420}}, {{840, 420}}, {800, 400}, {840, 440}, -1); */
    /* std::vector<Road *> pRoads = {pRoad0, pRoad1, pRoad2, pRoad3, pRoad4, pRoad5, pRoad6, pRoad7}; */

    Road* pRoad0 = new Road(0, {{200, 80}}, {{200, 40}}, {180, 40}, {220}, -1);
    Road* pRoad1 = new Road(1, {{240, 40}}, {{240, 80}}, {220, 40}, {260, 80}, 0);
    Road* pRoad2 = new Road(2, {{200, 180}}, {{200, 80}}, {180, 80}, {220, 180}, 0);
    Road* pRoad3 = new Road(3, {{240, 80}}, {{240, 180}}, {220, 80}, {260, 180}, 0);
    Road* pRoad4 = new Road(4, {{200, 220}}, {{200, 180}}, {180, 180}, {220, 220}, 0);
    Road* pRoad5 = new Road(5, {{240, 180}}, {{260, 200}}, {220, 180}, {260, 220}, 0);
    Road* pRoad6 = new Road(6, {{220, 240}}, {{200, 220}}, {180, 220}, {220, 260}, 0);
    Road* pRoad7 = new Road(7, {{260, 240}}, {{220, 240}}, {220, 220}, {260, 260}, 0);
    Road* pRoad8 = new Road(8, {{260, 200}}, {{480, 200}}, {260, 180}, {480, 220}, 0);
    Road* pRoad9 = new Road(9, {{480, 240}}, {{260, 240}}, {260, 220}, {480, 260}, 0);
    Road* pRoad10 = new Road(10, {{480, 200}}, {{520, 200}}, {480, 180}, {520, 220}, 0);
    Road* pRoad11 = new Road(11, {{520, 200}}, {{540, 220}}, {520, 180}, {560, 220}, 0);
    Road* pRoad12 = new Road(12, {{500, 260}}, {{480, 240}}, {480, 220}, {520, 260}, 0);
    Road* pRoad13 = new Road(13, {{540, 220}}, {{540, 260}}, {520, 220}, {560, 260}, 0);
    Road* pRoad14 = new Road(14, {{500, 440}}, {{500, 260}}, {480, 260}, {520, 440}, 0);
    Road* pRoad15 = new Road(15, {{540, 260}}, {{540, 440}}, {520, 260}, {560, 440}, 0);
    Road* pRoad16 = new Road(16, {{500, 480}, {480, 460}}, {{500, 440}, {520, 460}}, {480, 440}, {520, 480}, 0);
    Road* pRoad17 = new Road(17, {{540, 440}, {520, 460}}, {{540, 480}, {560, 460}}, {520, 440}, {560, 440}, 0);
    Road* pRoad18 = new Road(18, {{500, 520}, {520, 500}}, {{500, 480}, {480, 500}}, {480, 480}, {520, 520}, 0);
    Road* pRoad19 = new Road(19, {{540, 480}, {560, 500}}, {{540, 520}, {520, 500}}, {520, 480}, {560, 520}, 0);
    Road* pRoad20 = new Road(20, {{260, 460}}, {{480, 460}}, {260, 440}, {480, 480}, 0);
    Road* pRoad21 = new Road(21, {{480, 500}}, {{260, 500}}, {260, 480}, {480, 520}, 0);
    Road* pRoad22 = new Road(22, {{200, 480}}, {{220, 460}}, {180, 440}, {220, 480}, 0);
    Road* pRoad23 = new Road(23, {{220, 460}}, {{260, 460}}, {220, 440}, {260, 480}, 0);
    Road* pRoad24 = new Road(24, {{200, 520}}, {{200, 480}}, {180, 480}, {220, 520}, 0);
    Road* pRoad25 = new Road(25, {{260, 500}}, {{240, 520}}, {220, 480}, {260, 520}, 0);
    Road* pRoad26 = new Road(26, {{200, 740}}, {{200, 520}}, {180, 520}, {220, 740}, 0);
    Road* pRoad27 = new Road(27, {{240, 520}}, {{240, 740}}, {220, 520}, {260, 740}, 0);
    Road* pRoad28 = new Road(28, {{200, 780}, {180, 760}}, {{200, 740}, {220, 760}}, {180, 740}, {220, 780}, 0);
    Road* pRoad29 = new Road(29, {{240,740}, {220, 760}}, {{240, 780}, {260, 760}}, {220, 740}, {260, 780}, 0);
    Road* pRoad30 = new Road(30, {{200, 820}, {220, 800}}, {{200, 780}, {180, 800}}, {180, 780}, {220, 820}, 0);
    Road* pRoad31 = new Road(31, {{240, 780}, {260, 800}}, {{240, 820}, {220, 800}}, {220, 780}, {260, 820}, 0);
    Road* pRoad32 = new Road(32, {{260, 760}}, {{480, 760}}, {260, 740}, {480, 780}, 0);
    Road* pRoad33 = new Road(33, {{480, 800}}, {{260, 800}}, {260, 780}, {480, 820}, 0);
    Road* pRoad34 = new Road(34, {{500, 740}}, {{500, 520}}, {480, 520}, {520, 740}, 0);
    Road* pRoad35 = new Road(35, {{540, 520}}, {{540, 740}}, {520, 520}, {560, 740}, 0);
    Road* pRoad36 = new Road(36, {{480, 760}}, {{500, 740}}, {480, 740}, {520, 780}, 0);
    Road* pRoad37 = new Road(37, {{540, 740}}, {{540, 780}}, {520, 740}, {560, 780}, 0);
    Road* pRoad38 = new Road(38, {{520, 800}}, {{480, 800}}, {480, 780}, {520, 820}, 0);
    Road* pRoad39 = new Road(39, {{540, 780}}, {{520, 800}}, {520, 780}, {560, 820}, 0);
    Road* pRoad40 = new Road(40, {{560, 460}}, {{740, 460}}, {560, 440}, {740, 480}, 0);
    Road* pRoad41 = new Road(41, {{740, 500}}, {{560, 500}}, {560, 480}, {740, 520}, 0);
    Road* pRoad42 = new Road(42, {{740, 460}}, {{780, 460}}, {740, 440}, {780, 480}, 0);
    Road* pRoad43 = new Road(43, {{780, 460}}, {{800, 480}}, {780, 440}, {820, 480}, 0);
    Road* pRoad44 = new Road(44, {{760, 520}}, {{740, 500}}, {740, 480}, {780, 520}, 0);
    Road* pRoad45 = new Road(45, {{800, 480}}, {{800, 520}}, {780, 480}, {820, 520}, 0);
    Road* pRoad46 = new Road(46, {{800, 740}}, {{760, 520}}, {740, 520}, {780, 740}, 0);
    Road* pRoad47 = new Road(47, {{800, 520}}, {{800, 740}}, {780, 520}, {820, 740}, 0);
    Road* pRoad48 = new Road(48, {{760, 780}}, {{760, 740}}, {740, 740}, {780, 780}, 0);
    Road* pRoad49 = new Road(49, {{800, 740}}, {{820, 760}}, {780, 740}, {820, 780}, 0);
    Road* pRoad50 = new Road(50, {{780, 800}}, {{760, 780}}, {740, 780}, {780, 820}, 0);
    Road* pRoad51 = new Road(51, {{820, 800}}, {{780, 800}}, {780, 780}, {820, 820}, 0);
    Road* pRoad52 = new Road(52, {{820, 760}}, {{920, 760}}, {820, 740}, {920, 780}, 0);
    Road* pRoad53 = new Road(53, {{920, 800}}, {{820, 800}}, {820, 780}, {920, 820}, 0);
    Road* pRoad54 = new Road(54, {{920, 760}}, {{960, 760}}, {920, 740}, {960, 780}, -1);
    Road* pRoad55 = new Road(55, {{960, 800}}, {{920, 800}}, {920, 780}, {960, 820}, 0);
    Road* pRoad56 = new Road(56, {{100, 760}}, {{180, 760}}, {100, 740}, {180, 780}, 0);
    Road* pRoad57 = new Road(57, {{180, 800}}, {{100, 800}}, {100, 780}, {180, 820}, 0);
    Road* pRoad58 = new Road(58, {{60, 760}}, {{100, 760}}, {60, 740}, {100, 780}, 0);
    Road* pRoad59 = new Road(59, {{100, 800}}, {{60, 800}}, {60, 780}, {100, 820}, -1);
    Road* pRoad60 = new Road(60, {{200, 900}}, {{200, 820}}, {180, 820}, {220, 900}, 0);
    Road* pRoad61 = new Road(61, {{240, 820}}, {{240, 900}}, {220, 820}, {260, 900}, 0);
    Road* pRoad62 = new Road(62, {{200, 940}}, {{200, 900}}, {180, 900}, {220, 940}, 0);
    Road* pRoad63 = new Road(63, {{240, 900}}, {{240, 940}}, {220, 900}, {260, 940}, -1);


    std::vector<Road*> pRoads = {pRoad0, pRoad1, pRoad2, pRoad3, pRoad4,
        pRoad5, pRoad6, pRoad7, pRoad8, pRoad9, pRoad10, pRoad11, pRoad12,
        pRoad13, pRoad14, pRoad15, pRoad16, pRoad17, pRoad18, pRoad19, pRoad20,
        pRoad21, pRoad22, pRoad23, pRoad24, pRoad25, pRoad26, pRoad27, pRoad28,
        pRoad29, pRoad30, pRoad31, pRoad32, pRoad33, pRoad34, pRoad35, pRoad36,
        pRoad37, pRoad38, pRoad39, pRoad40, pRoad41, pRoad42, pRoad43, pRoad44,
        pRoad45, pRoad46, pRoad47, pRoad48, pRoad49, pRoad50, pRoad51, pRoad52,
        pRoad53, pRoad54, pRoad55, pRoad56, pRoad57, pRoad58, pRoad59, pRoad60,
        pRoad61, pRoad62, pRoad63};

    World world(1000, 1000, pRoads);

    // Initialize our exporter object
    Exporter e = Exporter(true);
    // Export pRoad data to a csv file so that we can read it in in Python
    e.writeRoadsToCSV("../visual/data/road_data.csv", pRoads);

    // Setup Car Objects
    Car* pCar0 = new Car(nullptr, 240, 100, 120, pRoad3);  // nullptr for first car

    Car* pCar1 = new Car(pCar0, 240, 60, 140, pRoad1);

    Car* pCar2 = new Car(nullptr, 200, 900, 120, pRoad60);

    Car* pCar3 = new Car(pCar2, 200, 920, 140, pRoad62);


    world.pCars.push_back(pCar0);
    world.pCars.push_back(pCar1);
    world.pCars.push_back(pCar2);
    world.pCars.push_back(pCar3);

    float t = 0.0;
    for (int i = 0; i < totalFrameNum; i++) {
        t += dt;  // Keep track of overall time elapsed
        world.updateWorld(t);
    }

    e.writeCarsToCSV("../visual/data/car_data.csv", world.pCars);
    e.writeTrafficLightsToCSV("../visual/data/light_data.csv", world.pRoads);
    world.deleteObjects();

    return 0;
}

// For testing
/* int main() { */
/*     std::cout << bearing({0.0f, 0.0f}, {-0.70107f, 0.707107f}) << std::endl; */
/*     return 0; */
/* } */
