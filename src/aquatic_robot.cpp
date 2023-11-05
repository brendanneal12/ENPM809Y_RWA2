#include "aquatic_robot.h"
#include <chrono>
#include <thread>

void RWA2::AquaticRobot::dive(double depth)
{
    if (is_diving_ == false)
    {
        is_diving_ == true;
        if (has_fins_ == true)
        {
            double dive_time = depth / 2;
            int dive_time_milli = static_cast<int>(1000 * dive_time);
            std::chrono::milliseconds duration(dive_time_milli);
            std::this_thread::sleep_for(duration);
            depth_ = depth;
        }

        else if (has_fins_ == false)
        {
            double dive_time = depth / 1;
            int dive_time_milli = static_cast<int>(1000 * dive_time);
            std::chrono::milliseconds duration(dive_time_milli);
            std::this_thread::sleep_for(duration);
            depth_ = depth;
        }
    }
}

void RWA2::AquaticRobot::surface()
{
    if (is_diving_ == true)
    {
        if (has_fins_ == true)
        {
            double ascend_time = depth_ / 4;
            int ascend_time_milli = static_cast<int>(1000 * ascend_time);
            std::chrono::milliseconds duration(ascend_time_milli);
            std::this_thread::sleep_for(duration);
            depth_ = 0.0;
            is_diving_ == false;
        }

        else if (has_fins_ == false)
        {
            double ascend_time = depth_ / 2;
            int ascend_time_milli = static_cast<int>(1000 * ascend_time);
            std::chrono::milliseconds duration(ascend_time_milli);
            std::this_thread::sleep_for(duration);
            depth_ = 0.0;
            is_diving_ == false;
        }
    }
}

void RWA2::AquaticRobot::rotate(double angle)
{
    orientation_ += angle;
    std::cout << "AquaticRobot::" << model_ << " rotated" << angle << " degrees \n";
}

void RWA2::AquaticRobot::print_status()
{
    std::cout << "================\n";
    std::cout << "AQUATIC ROBOT\n";
    std::cout
        << "Position: (" << position_.first << ", "
        << position_.second << "), Orientation: " << orientation_
        << ", Speed: " << speed_ << "\n"
        << ", Current Battery Charge: " << battery_.get_current_charge();
    std::cout << "Has Fins:" << std::boolalpha << has_fins_ << " Depth:" << depth_ << "Is Diving:" << std::boolalpha << is_diving_ << '\n';
}

void RWA2::AquaticRobot::move(double distance, double angle)
{
    if (distance > 50)
    {
        std::cout << "Aquatic robot unable to move more than 100 m" << '\n';
    }

    // each meter consumes 1% of the battery
    // check if the battery has enough charge to move the robot forward by the
    // given distance
    if (battery_.get_current_charge() < 2 * distance)
    {
        std::cout << "Battery level is too low to dive and surface " << distance << " m\n";
        battery_.start_charging();
    }

    AquaticRobot::get_sensor_reading(5);
    AquaticRobot::rotate(angle);
    AquaticRobot::dive(distance);
    AquaticRobot::surface();
    battery_.discharge(2 * distance);
    std::cout << model_ << "reached a depth of " << distance << " meters and then surfaced\n";
    AquaticRobot::print_status();
}