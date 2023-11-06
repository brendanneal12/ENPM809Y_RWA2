#include "aerial_robot.h"
#include <chrono>
#include <thread>

void RWA2::AerialRobot::takeoff(double altitude) 
{
    if (is_flying_ == false)
    {
        is_flying_ = true;
        if (has_wings_ == true)
        {
            double climb_time = altitude / 3;
            int climb_time_milli = static_cast<int>(1000 * climb_time);
            std::chrono::milliseconds duration(climb_time_milli);
            std::this_thread::sleep_for(duration);
            altitude_ = altitude;
        }

        else if (has_wings_ == false)
        {
            double climb_time = altitude / 1.5;
            int climb_time_milli = static_cast<int>(1000 * climb_time);
            std::chrono::milliseconds duration(climb_time_milli);
            std::this_thread::sleep_for(duration);
            altitude_ = altitude;
        }
    }
}

void RWA2::AerialRobot::land()
{
    if (is_flying_ == true)
    {
        if (has_wings_ == true)
        {
            double descend_time = altitude_ / 4;
            int descend_time_milli = static_cast<int>(1000 * descend_time);
            std::chrono::milliseconds duration(descend_time_milli);
            std::this_thread::sleep_for(duration);
            altitude_ = 0.0;
            is_flying_ = false;
        }

        else if (has_wings_ == false)
        {
            double descend_time = altitude_ / 2;
            int descend_time_milli = static_cast<int>(1000 * descend_time);
            std::chrono::milliseconds duration(descend_time_milli);
            std::this_thread::sleep_for(duration);
            altitude_ = 0.0;
            is_flying_ = false;
        }
    }
}

void RWA2::AerialRobot::move(double distance, double angle)
{
    if(distance > 25){
        std::cout << "Aerial robot unable to fly and land more than 50 m" << '\n';
    }

    // each meter consumes 2% of the battery
    // check if the battery has enough charge to move the robot forward by the
    // given distance
    if (battery_.get_current_charge() < 2*2*distance)
    {
        std::cout << "Battery level is too low to take off and land by " << distance << " m\n";
        battery_.start_charging();
    }

    AerialRobot::get_sensor_reading(5);
    AerialRobot::takeoff(distance);
    AerialRobot::rotate(angle);
    AerialRobot::land();
    battery_.discharge(2*2*distance);
    std::cout << model_ << " reached an altitude of " << distance << " meters and then landed\n";
    AerialRobot::print_status();
}

void RWA2::AerialRobot::rotate(double angle)
{
    orientation_ += angle;
    std::cout << AerialRobot::model_ << " rotated " << angle << " degrees \n";
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