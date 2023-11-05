#include "legged_robot.h"
#include <chrono>
#include <thread>

void RWA2::LeggedRobot::kick()
{
    std::cout << model_ << "kicks with a leg strength of " << leg_strength_ << '\n';
}

void RWA2::LeggedRobot::jump(double amount)
{
    height_ = amount*leg_strength_;
}

void RWA2::LeggedRobot::rotate(double angle)
{
    orientation_ += angle;
    std::cout << "LeggedRobot::" << model_ << " rotated" << angle << " degrees \n";
}

void RWA2::LeggedRobot::print_status()
{
    std::cout << "================\n";
    std::cout << "LEGGED ROBOT\n";
    std::cout
        << "Position: (" << position_.first << ", "
        << position_.second << "), Orientation: " << orientation_
        << ", Speed: " << speed_ << "\n"
        << ", Current Battery Charge: " << battery_.get_current_charge();
    std::cout << "Height: " << height_ << " Leg Strength: " << leg_strength_ << " Number of Legs: " << number_of_legs_ << '\n';
}

void RWA2::LeggedRobot::move(double distance, double angle)
{
    if (distance > 10)
    {
        std::cout << "Legged Robot unable to move more than 10 m." << '\n';
    }

    if (battery_.get_current_charge() < 100 * height_)
    {
        std::cout << "Battery level is too low to jump " << height_ << " cm\n";
        battery_.start_charging();
    }

    if (battery_.get_current_charge() < 1 * leg_strength_)
    {
        std::cout << "Battery level is too low to kick. \n";
        battery_.start_charging();
    }
    LeggedRobot::get_sensor_reading(5);
    LeggedRobot::rotate(angle);
    LeggedRobot::jump(distance);
    battery_.discharge(100 * distance);
    LeggedRobot::kick();
    battery_.discharge(1 * leg_strength_);
    LeggedRobot::print_status();
}