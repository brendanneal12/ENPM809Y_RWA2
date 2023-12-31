#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <utility>
#include <vector>

/**
 * @brief Namespace for RWA2
 *
 */
namespace RWA2
{
    /**
     * @brief Class for the sensor
     *
     */
    class Sensor final
    {
    private:
        // ==================== attributes ====================
        std::string model_;
        std::array<double, 50> data_;

    public:
        // ==================== constructors ====================
        /**
         * @brief Construct a new sensor object
         * -first argument: sensor model name.
        */
        Sensor(std::string model_name) : model_{model_name} {}

        // ==================== destructor ====================
        /**
         * @brief Sensor Class Destructor.
         */
        ~Sensor() {}

        // ==================== methods ====================
        /**
         * @brief Generate 50 random numbers to mimic sensor readings.
         *
         * @param duration Period of the reading (in s)
         */
        void read_data(unsigned int duration);

    }; // class Sensor
} // namespace RWA2