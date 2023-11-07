#include "battery.h"

#include <chrono>
#include <thread>

void RWA2::Battery::start_charging()
{
    // Check if battery is not already charging
    if (is_charging_ == false)
    {
        // Update charging status
        is_charging_ = true;
        std::cout << "Battery " << model_ << " is charging. \n";

        if (model_ == "Li-ion")
        {
            // Calculate charge time for a Li-ion battery
            int charge_left = 100 - current_charge_;
            int charge_time = 0.5 * 1000 * charge_left;
            std::chrono::milliseconds duration(charge_time);
            // Sleep the thread for charge time
            std::this_thread::sleep_for(duration);
        }

        else if (model_ == "LiFePO4")
        {
            // Calculate charge time for a LiFePO4 battery
            int charge_left = 100 - current_charge_;
            int charge_time = 0.25 * 1000 * charge_left;
            std::chrono::milliseconds duration(charge_time);
            // Sleep the thread for charge time
            std::this_thread::sleep_for(duration);
        }
        // Update current charge
        current_charge_ = 100;
        // Stop charging battery
        stop_charging();
    }
    else
    {
        std::cout << "Battery is already charging. \n";
    }
}

void RWA2::Battery::stop_charging()
{
    // Update charging status
    is_charging_ = false;
    std::cout << "Battery " << model_ << " is fully charged. \n";
}

void RWA2::Battery::discharge(double amount)
{
    // Decrement current charge by given amount
    current_charge_ -= amount;
}