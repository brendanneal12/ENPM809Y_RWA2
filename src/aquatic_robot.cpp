#include "aquatic_robot.h"
#include <chrono>
#include <thread>

void RWA2::AquaticRobot::dive(double depth)
{
    // Check if robot is not currently diving
    if (is_diving_ == false)
    {
        // Set dive status to true
        is_diving_ = true;
        if (has_fins_ == true)
        {
            // Calculate dive time for a finned aquatic robot
            double dive_time = depth / 2;
            int dive_time_milli = static_cast<int>(1000 * dive_time);
            std::chrono::milliseconds duration(dive_time_milli);
            // Sleep the thread for dive time
            std::this_thread::sleep_for(duration);
            // Update depth
            depth_ = depth;
        }

        else if (has_fins_ == false)
        {
            // Calculate dive time for a non-finned aquatic robot
            double dive_time = depth / 1;
            int dive_time_milli = static_cast<int>(1000 * dive_time);
            std::chrono::milliseconds duration(dive_time_milli);
            // Sleep the thread for dive time
            std::this_thread::sleep_for(duration);
            // Update depth
            depth_ = depth;
        }
    }
}

void RWA2::AquaticRobot::surface()
{
    // Check if robot is currently diving
    if (is_diving_ == true)
    {
        if (has_fins_ == true)
        {
            // Calculate ascend time for a finned aquatic robot
            double ascend_time = depth_ / 4;
            int ascend_time_milli = static_cast<int>(1000 * ascend_time);
            std::chrono::milliseconds duration(ascend_time_milli);
            // Sleep the thread for ascend time
            std::this_thread::sleep_for(duration);
            // Update depth
            depth_ = 0.0;
            // Update dive status
            is_diving_ = false;
        }

        else if (has_fins_ == false)
        {
            // Calculate the ascend time for a non-finned aquatic robot
            double ascend_time = depth_ / 2;
            int ascend_time_milli = static_cast<int>(1000 * ascend_time);
            std::chrono::milliseconds duration(ascend_time_milli);
            // Sleep the thread for ascend time
            std::this_thread::sleep_for(duration);
            // Update depth
            depth_ = 0.0;
            // Update dive status
            is_diving_ = false;
        }
    }
}

void RWA2::AquaticRobot::rotate(double angle)
{
    // Rotate the aquatic robot by desired amount
    RWA2::MobileRobot::rotate(angle);
    std::cout << "AquaticRobot::" << model_ << " rotated " << angle << " degrees \n";
}

void RWA2::AquaticRobot::print_status()
{
    std::cout << "================\n";
    std::cout << "AquaticRobot::" << model_ << "\n";
    RWA2::MobileRobot::print_status();
    std::cout << "Current Battery Charge: " << battery_.get_current_charge() << "\n";
    std::cout << "Has Fins: " << std::boolalpha << has_fins_ << ", Depth: " << depth_ << "m, Is Diving: " << std::boolalpha << is_diving_ << '\n';
    std::cout << "================\n";
}

void RWA2::AquaticRobot::move(double distance, double angle)
{
    // Check if distance is greater than the max dive AND surface range. Max range is 100m.
    if (distance <= 100)
    {

        // each meter consumes 1% of the battery
        // check if the battery has enough charge to move the robot by the
        // given distance (dive and surface)
        if (battery_.get_current_charge() < distance)
        {
            std::cout << "Battery level is too low to dive and surface " << distance << " m\n";
            // Charge the battery
            battery_.start_charging();
        }

        // Read sensor data
        AquaticRobot::get_sensor_reading(5);
        // Rotate by given amount
        AquaticRobot::rotate(angle);
        // Dive
        AquaticRobot::dive(distance / 2);
        // Surface
        AquaticRobot::surface();
        // Discharge battery proper amount
        battery_.discharge(distance);
        std::cout << model_ << " reached a depth of " << distance / 2 << " meters and then surfaced\n";
        // Print aquatic robot status
        AquaticRobot::print_status();
    }
    else
    {
        std::cout << "Aquatic robot unable to dive and surface more than 50 m." << '\n';
    }
}