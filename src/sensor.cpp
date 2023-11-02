#include "sensor.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <random>

void RWA2::Sensor::read_data(unsigned int duration)
{

    std::cout << "Sensor " << model_ << " gathering data for " << duration << ' seconds. \n';
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    // generate random double between 1 and 30
    std::random_device rd;  // Random device engine, usually based on
    std::mt19937 gen(rd()); // Initializes with the random device
    std::uniform_real_distribution<> dis(0.0, 30.0);

    for (int i = 0; i < 50; ++i) // Fill sensor data with random variables
    {
        data_[i] = dis(gen);
    }
}
