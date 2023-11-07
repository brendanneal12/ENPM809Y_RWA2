#include "sensor.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <random>

void RWA2::Sensor::read_data(unsigned int duration)
{

    std::cout << "Sensor " << model_ << " gathering data for " << duration << " seconds. \n";
    //Sleep thread for proper time
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    // Fill sensor data with random data values
    for (int i = 0; i < 50; ++i) 
    {
        // generate random double between 1 and 30
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 30.0);
        //Update associated data slot
        data_[i] = dis(gen);
    }
}
