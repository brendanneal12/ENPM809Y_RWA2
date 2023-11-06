#include "wheeled_robot.h"
#include <chrono>
#include <thread>

void RWA2::WheeledRobot::accelerate(double amount)
{
    while (speed_ <= desired_speed_)
    {
        std::chrono::milliseconds duration(500);
        std::this_thread::sleep_for(duration);
        speed_ += amount;
    }
    std::cout << model_ << " has reached the desired speed of " << desired_speed_ << " m/s \n";
}

void RWA2::WheeledRobot::deceletate(double amount)
{
    while (speed_ >= 0.0)
    {
        std::chrono::milliseconds duration(500);
        std::this_thread::sleep_for(duration);
        speed_ -= amount;
    }
    if (speed_ < 0.0)
    {
        speed_ = 0;
    }
}

void RWA2::WheeledRobot::brake()
{
    speed_ = 0;
}

void RWA2::WheeledRobot::rotate(double angle)
{
    orientation_ += angle;
    std::cout << "WheeledRobot::" << model_ << " rotated " << angle << " degrees \n";
}

void RWA2::WheeledRobot::print_status()
{
    std::cout << "================\n";
    std::cout << "WHEELED ROBOT\n";
    std::cout
        << "Position: (" << position_.first << ", "
        << position_.second << "), Orientation: " << orientation_
        << ", Speed: " << speed_ << "\n"
        << "Current Battery Charge: " << battery_.get_current_charge() << "\n";
    std::cout << "Number of Wheels: " << number_of_wheels_ << ", Wheel Diameter: " << wheel_diameter_ << "m , Desired Speed: " << desired_speed_ << "m/s \n";
    std::cout << "================\n";
}

void RWA2::WheeledRobot::move(double distance, double angle)
{
    if (distance > 100)
    {
        std::cout << "Wheeled Robot unable to move more than 100 m." << '\n';
    }

    // each meter consumes 1% of the battery
    // check if the battery has enough charge to move the robot forward by the
    // given distance
    if (battery_.get_current_charge() < distance)
    {
        std::cout << "Battery level is too low to move " << distance << " m\n";
        battery_.start_charging();
    }

    WheeledRobot::get_sensor_reading(5);
    WheeledRobot::rotate(angle);
    WheeledRobot::accelerate(2);
    int wait_time_milli = static_cast<int>(distance * 1000 - 2000);
    std::chrono::milliseconds duration(wait_time_milli);
    std::this_thread::sleep_for(duration);
    WheeledRobot::deceletate(2);
    WheeledRobot::brake();
    battery_.discharge(distance);
    std::cout << model_ << " drove " << distance << " m\n";
    WheeledRobot::print_status();
}
