#include "aerial_robot.h"
#include <chrono>
#include <thread>

void RWA2::AerialRobot::takeoff(double altitude)
{
    // Check if not already flying
    if (is_flying_ == false)
    {
        // Set flying to true
        is_flying_ = true;
        if (has_wings_ == true)
        {
            // Calculate time to climb for a winged aerial robot
            double climb_time = altitude / 3;
            int climb_time_milli = static_cast<int>(1000 * climb_time);
            std::chrono::milliseconds duration(climb_time_milli);
            // Sleep the thread for calculated climb time
            std::this_thread::sleep_for(duration);
            // Update Altitude
            altitude_ = altitude;
        }

        else if (has_wings_ == false)
        {
            // Calculate time to climb for a non-winged aerial robot
            double climb_time = altitude / 1.5;
            int climb_time_milli = static_cast<int>(1000 * climb_time);
            std::chrono::milliseconds duration(climb_time_milli);
            // Sleep the thread for calculated climb time
            std::this_thread::sleep_for(duration);
            // Update Altitude
            altitude_ = altitude;
        }
    }
}

void RWA2::AerialRobot::land()
{
    // Check if already flying
    if (is_flying_ == true)
    {
        if (has_wings_ == true)
        {
            // Calculate time to descend for a winged aerial robot
            double descend_time = altitude_ / 4;
            int descend_time_milli = static_cast<int>(1000 * descend_time);
            std::chrono::milliseconds duration(descend_time_milli);
            // Sleep the thread for calculated descend time
            std::this_thread::sleep_for(duration);
            // Update Altitude
            altitude_ = 0.0;
            // Update flight status
            is_flying_ = false;
        }

        else if (has_wings_ == false)
        {
            // Calculate time to descend for a non-winged aerial robot
            double descend_time = altitude_ / 2;
            int descend_time_milli = static_cast<int>(1000 * descend_time);
            std::chrono::milliseconds duration(descend_time_milli);
            // Sleep the thread for calculated descend time
            std::this_thread::sleep_for(duration);
            // Update Altitude
            altitude_ = 0.0;
            // Update flight status
            is_flying_ = false;
        }
    }
}

void RWA2::AerialRobot::move(double distance, double angle)
{
    // Check if distance is greater than the max fly and land range. Max range is 50m total.
    if (distance > 25)
    {
        std::cout << "Aerial robot unable to fly and land more than 50 m" << '\n';
    }

    // each meter consumes 2% of the battery
    // check if the battery has enough charge to move the robot take off AND land by the
    // given distance
    if (battery_.get_current_charge() < 2 * 2 * distance)
    {
        std::cout << "Battery level is too low to take off and land by " << distance << " m\n";
        // Charge Battery
        battery_.start_charging();
    }

    // Read Sensor Data for 5 seconds
    AerialRobot::get_sensor_reading(5);
    // Take Off
    AerialRobot::takeoff(distance);
    // Rotate by desired angle
    AerialRobot::rotate(angle);
    // Land
    AerialRobot::land();
    // Discharge battery by proper amount
    battery_.discharge(2 * 2 * distance);
    std::cout << model_ << " reached an altitude of " << distance << " meters and then landed\n";
    // Print the new status of AerialRobot
    AerialRobot::print_status();
}

void RWA2::AerialRobot::rotate(double angle)
{
    // Rotate the aerial robot by desired amount
    orientation_ += angle;
    std::cout << "AerialRobot::" << model_ << " rotated " << angle << " degrees \n";
}

void RWA2::AerialRobot::print_status()
{
    std::cout << "================\n";
    std::cout << "AerialRobot:: " << model_ << "\n";
    std::cout
        << "Position: (" << position_.first << ", "
        << position_.second << "), Orientation: " << orientation_
        << ", Speed: " << speed_ << "\n"
        << "Current Battery Charge: " << battery_.get_current_charge() << "\n";
    std::cout << "Has Wings:" << std::boolalpha << has_wings_ << ", Altitude: " << altitude_ << "m, Is Flying:" << std::boolalpha << is_flying_ << '\n';
    std::cout << "================\n";
}