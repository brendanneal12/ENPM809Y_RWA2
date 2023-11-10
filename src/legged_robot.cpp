#include "legged_robot.h"
#include <chrono>
#include <thread>
#include <math.h>

void RWA2::LeggedRobot::kick()
{
    // Print kick move
    std::cout << model_ << " kicks with a leg strength of " << leg_strength_ << '\n';
}

void RWA2::LeggedRobot::jump(double amount)
{
    // Update robot height by jump amount
    height_ = (0.01 * amount) * leg_strength_;
    std::cout << model_ << " jumps at a height of " << 100 * height_ << " cm above the ground \n";
}

void RWA2::LeggedRobot::rotate(double angle)
{
    // Rotate robot by given angle
    RWA2::MobileRobot::rotate(angle);
    std::cout << "LeggedRobot::" << model_ << " rotated " << angle << " degrees \n";
}

void RWA2::LeggedRobot::print_status()
{
    std::cout << "================\n";
    std::cout << "LeggedRobot::" << model_ << "\n";
    RWA2::MobileRobot::print_status();
    std::cout << "Current Battery Charge: " << battery_.get_current_charge() << "\n";
    std::cout << "Height: " << height_ << ", Leg Strength: " << leg_strength_ << ", Number of Legs: " << number_of_legs_ << '\n';
    std::cout << "================\n";
}

void RWA2::LeggedRobot::move(double distance, double angle)
{
    // Check if robot is moving less than max distance
    if (distance <= 10)
    {

        // Check if able to complete one jump
        if (battery_.get_current_charge() < (0.01 * distance) * leg_strength_)
        {
            std::cout << "Battery level is too low to jump " << height_ << " cm\n";
            // Charge battery
            battery_.start_charging();
        }

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
        // Update new position
        position_.first += distance * cos(orientation_ * 3.14 / 180);
        position_.second += distance * sin(orientation_ * 3.14 / 180);
        // Discharge battery by proper amount
        battery_.discharge(100 * height_);
        // Kick once
        LeggedRobot::kick();
        // Discharge battery by proper amount
        battery_.discharge(1 * leg_strength_);
        // Print status of legged robot
        LeggedRobot::print_status();
    }
    else
    {
        std::cout << "Legged robot unable to move more than 10 m." << '\n';
    }
}