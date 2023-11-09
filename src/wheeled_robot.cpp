#include "wheeled_robot.h"
#include <chrono>
#include <thread>
#include <math.h>

void RWA2::WheeledRobot::accelerate(double amount)
{
    // While wheeled robot is less than desired speed
    while (speed_ <= desired_speed_)
    {
        std::chrono::milliseconds duration(500);
        // Sleep the thread and increment speed
        std::this_thread::sleep_for(duration);
        speed_ += amount;
    }
    std::cout << model_ << " has reached the desired speed of " << desired_speed_ << " m/s \n";
}

void RWA2::WheeledRobot::deceletate(double amount)
{
    // While wheeled robot is greater than 0 speed
    while (speed_ >= 0.0)
    {
        std::chrono::milliseconds duration(500);
        // Sleep the thread and decrement speed
        std::this_thread::sleep_for(duration);
        speed_ -= amount;
    }
    // Ensure speed does not reach zero
    if (speed_ < 0.0)
    {
        speed_ = 0;
    }
}

void RWA2::WheeledRobot::brake()
{
    // Set speed directly to 0
    speed_ = 0;
}

void RWA2::WheeledRobot::rotate(double angle)
{
    // Rotate robot by desired angle
    orientation_ += angle;
    std::cout << "WheeledRobot::" << model_ << " rotated " << angle << " degrees \n";
}

void RWA2::WheeledRobot::print_status()
{
    std::cout << "================\n";
    std::cout << "WheeledRobot::" << model_ << "\n";
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
    // Check if move command is not greater than maximum distance (100m)
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

    // Read sensor data
    WheeledRobot::get_sensor_reading(5);
    // Rotate wheeled robot by angle
    WheeledRobot::rotate(angle);
    // Accelerate to desired speed
    WheeledRobot::accelerate(2);
    // Sleep thread for distance-2 seconds
    int wait_time_milli = static_cast<int>(distance * 1000 - 2000);
    std::chrono::milliseconds duration(wait_time_milli);
    std::this_thread::sleep_for(duration);
    // Decelerate to zero
    WheeledRobot::deceletate(2);
    // Brake
    WheeledRobot::brake();
    // Update new position
    position_.first += distance * cos(orientation_ * 3.14 / 180);
    position_.second += distance * sin(orientation_ * 3.14 / 180);
    // Discharge battery by proper amount
    battery_.discharge(distance);
    std::cout << model_ << " drove " << distance << " m\n";
    // Print status of wheeled robot.
    WheeledRobot::print_status();
}
