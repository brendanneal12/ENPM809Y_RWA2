#include "mobile_robot.h"
#include "aquatic_robot.h"
#include "aerial_robot.h"
#include "wheeled_robot.h"
#include "legged_robot.h"
#include "sensor.h"
#include "battery.h"

// Group 12: Brendan Neal, Sarang Shibu, and Prathinav Karnala Venkata.
// ENPM809Y RWA2
// Due: 10 November 2023

void move_robot(const std::vector<std::unique_ptr<RWA2::MobileRobot>> &robots)
{
    //For all robots in vector
    for (const auto &robot : robots)
        //Move 8 meters and rotate 5 degrees
        robot->move(8, 5);
}

int main()
{
    // Create a vector of derived mobile robots
    std::vector<std::unique_ptr<RWA2::MobileRobot>> mobile_robots;

    // Instatiate two instances of each derived classes with different properties
    // Add sensors to each robot
    std::unique_ptr<RWA2::MobileRobot> aquatic_ptr1 =
        std::make_unique<RWA2::AquaticRobot>(4.5, 7.5, 0.0, "HoloOcean", "LiFePO4", 5, false, false);

    aquatic_ptr1->add_sensor(std::make_unique<RWA2::Sensor>("multiScan100"));

    std::unique_ptr<RWA2::MobileRobot> aerial_ptr1 =
        std::make_unique<RWA2::AerialRobot>(2.5, 5.5, 45.0, "Erle-Plane", "Li-ion", 15, false, true);

    aerial_ptr1->add_sensor(std::make_unique<RWA2::Sensor>("OS2"));

    std::unique_ptr<RWA2::MobileRobot> legged_ptr1 =
        std::make_unique<RWA2::LeggedRobot>(3.5, 6.5, 45.0, "Spot", "LiFePO4", 50, false, 0.0, 2, 4);

    legged_ptr1->add_sensor(std::make_unique<RWA2::Sensor>("LMS5xx"));

    std::unique_ptr<RWA2::MobileRobot> wheeled_ptr1 =
        std::make_unique<RWA2::WheeledRobot>(4.5, 7.5, 0.0, "Dagu", "Li-ion", 100, false, 6, 0.126, 5);

    wheeled_ptr1->add_sensor(std::make_unique<RWA2::Sensor>("OSDome"));

    std::unique_ptr<RWA2::MobileRobot> aquatic_ptr2 =
        std::make_unique<RWA2::AquaticRobot>(10.5, 6.9, 0.0, "SoFi", "Li-ion", 64, false, true);

    aquatic_ptr2->add_sensor(std::make_unique<RWA2::Sensor>("LD-MRS"));

    std::unique_ptr<RWA2::MobileRobot> aerial_ptr2 =
        std::make_unique<RWA2::AerialRobot>(9.5, 10.5, 55.0, "Crazyflie", "LiFePO4", 15, false, false);

    aerial_ptr2->add_sensor(std::make_unique<RWA2::Sensor>("OS1"));

    std::unique_ptr<RWA2::MobileRobot> legged_ptr2 =
        std::make_unique<RWA2::LeggedRobot>(33.5, 63.5, 145.0, "Mx-Phoenix", "Li-ion", 50, false, 0.0, 2, 6);

    legged_ptr2->add_sensor(std::make_unique<RWA2::Sensor>("OS0"));

    std::unique_ptr<RWA2::MobileRobot> wheeled_ptr2 =
        std::make_unique<RWA2::WheeledRobot>(21.5, 9.5, 0.0, "TurtleBot", "LiFePO4", 7, false, 2, 0.66, 4);

    wheeled_ptr2->add_sensor(std::make_unique<RWA2::Sensor>("OSDome"));

    // Push classes to vector
    mobile_robots.push_back(std::move(aquatic_ptr1));
    mobile_robots.push_back(std::move(aerial_ptr1));
    mobile_robots.push_back(std::move(legged_ptr1));
    mobile_robots.push_back(std::move(wheeled_ptr1));
    mobile_robots.push_back(std::move(aquatic_ptr2));
    mobile_robots.push_back(std::move(aerial_ptr2));
    mobile_robots.push_back(std::move(legged_ptr2));
    mobile_robots.push_back(std::move(wheeled_ptr2));

    //Call move_robot function on all instatiated robots
    move_robot(mobile_robots);
}