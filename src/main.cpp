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
    for (const auto &robot : robots)
        robot->move(8, 5);
}

int main()
{
    std::vector<std::unique_ptr<RWA2::MobileRobot>> mobile_robots;

    std::unique_ptr<RWA2::MobileRobot> aquatic_ptr =
        std::make_unique<RWA2::AquaticRobot>(4.5, 7.5, 0.0, "HoloOcean", "LiFePO4", 5, false, false);

    aquatic_ptr->add_sensor(std::make_unique<RWA2::Sensor>("multiScan100"));

    std::unique_ptr<RWA2::MobileRobot> aerial_ptr =
        std::make_unique<RWA2::AerialRobot>(2.5, 5.5, 45.0, "Erle-Plane", "Li-ion", 5, false, true);

    aerial_ptr->add_sensor(std::make_unique<RWA2::Sensor>("OS2"));

    std::unique_ptr<RWA2::MobileRobot> legged_ptr =
        std::make_unique<RWA2::LeggedRobot>(3.5, 6.5, 45.0, "Spot", "LiFePO4", 50, false, 1.0, 2, 4);

    legged_ptr->add_sensor(std::make_unique<RWA2::Sensor>("LMS5xx"));

    std::unique_ptr<RWA2::MobileRobot> wheeled_ptr =
        std::make_unique<RWA2::WheeledRobot>(4.5, 7.5, 0.0, "Dagu", "Li-ion", 100, false, 6, 0.126, 5);

    wheeled_ptr->add_sensor(std::make_unique<RWA2::Sensor>("OSDome"));

    mobile_robots.push_back(std::move(aquatic_ptr));
    mobile_robots.push_back(std::move(aerial_ptr));
    mobile_robots.push_back(std::move(legged_ptr));
    mobile_robots.push_back(std::move(wheeled_ptr));

    move_robot(mobile_robots);
}