#include "battery.h"

#include <chrono>
#include <thread>

void RWA2::Battery::start_charging()
{
    if (is_charging_ == false)
    {
        is_charging_ = true;
        std::cout << "Battery" << model_ << " is charging. \n";

        if (model_ == "Li-ion")
        {
            int charge_left = 100-current_charge_;
            int charge_time = 0.5*charge_left;
            std::chrono::seconds duration(charge_time);
            std::this_thread::sleep_for(duration);
        }

        else if (model_ == "LiFePO4")
        {
            int charge_left = 100-current_charge_;
            int charge_time = 0.25*charge_left;
            std::chrono::seconds duration(charge_time);
            std::this_thread::sleep_for(duration);
        }

        current_charge_ = 100;
        stop_charging();
    }
    else
    {
        std::cout << "Battery is already charging. \n";
    }
}

void RWA2::Battery::stop_charging()
{
    is_charging_ = false;
    std::cout << "Battery" << model_ << " is fully charged. \n";
}

void RWA2::Battery::discharge(double amount)
{
    current_charge_ -= amount;

}