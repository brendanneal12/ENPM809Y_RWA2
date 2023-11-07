#include "legged_robot.h"
#include <chrono>
#include <thread>

void RWA2::LeggedRobot::kick()
{
    // Print kick move
    std::cout << model_ << " kicks with a leg strength of " << leg_strength_ << '\n';
}

void RWA2::LeggedRobot::jump(double amount)
{
    // Update robot height by jump amount
    height_ = (0.01 * amount) * leg_strength_;
}

void RWA2::LeggedRobot::rotate(double angle)
{
    // Rotate robot by given angle
    orientation_ += angle;
    std::cout << "LeggedRobot::" << model_ << " rotated " << angle << " degrees \n";
}

void RWA2::LeggedRobot::print_status()
{
    std::cout << "================\n";
    std::cout << "LeggedRobot::" << model_ << "\n";
    std::cout
        << "Position: (" << position_.first << ", "
        << position_.second << "), Orientation: " << orientation_
        << ", Speed: " << speed_ << "\n"
        << "Current Battery Charge: " << battery_.get_current_charge() << "\n";
    std::cout << "Height: " << height_ << ", Leg Strength: " << leg_strength_ << ", Number of Legs: " << number_of_legs_ << '\n';
    std::cout << "================\n";
}

void RWA2::LeggedRobot::move(double distance, double angle)
{
    // Check if robot is moving less than max distance
    if (distance > 10)
    {
        std::cout << "Legged Robot unable to move more than 10 m." << '\n';
    }

    // Check if able to complete one jump
    LeggedRobot::jump(distance);
    if (battery_.get_current_charge() < 100 * height_)
    {
        std::cout << "Battery level is too low to jump " << height_ << " cm\n";
        // Charge battery
        battery_.start_charging();
        height_ = 0.0;
    }

    height_ = 0.0;

    // Check if able to complete one kick
    if (battery_.get_current_charge() < 1 * leg_strength_)
    {
        std::cout << "Battery level is too low to kick. \n";
        // Charge battery
        battery_.start_charging();
    }
    // Read sensor data
    LeggedRobot::get_sensor_reading(5);
    // Rotate by set amount
    LeggedRobot::rotate(angle);
    // Jump given distance
    LeggedRobot::jump(distance);
    // Discharge battery by proper amount
    battery_.discharge(100 * height_);
    // Kick once
    LeggedRobot::kick();
    // Discharge battery by proper amount
    battery_.discharge(1 * leg_strength_);
    // Print status of legged robot
    LeggedRobot::print_status();
}