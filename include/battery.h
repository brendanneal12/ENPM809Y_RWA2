#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

/**
 * @brief Namespace for the RWA2
 *
 */
namespace RWA2
{
    /**
     * @brief Class for the battery
     *
     */
    class Battery final
    {
    private:
        // ==================== attributes ====================
        std::string model_;
        int current_charge_;
        bool is_charging_;

        // ==================== methods ====================
        void stop_charging();

    public:
        // ==================== constructors ====================
        /**
         * @brief Construct a new Battery object
         * - first argument: battery model name
         * - second argument: current battery charge
         * - third argument: is charging
         */
        Battery(std::string model, int current_charge, bool is_charging)
            : model_{model},
              current_charge_{current_charge},
              is_charging_{is_charging} {}

        // ==================== destructor ====================

        /**
         * @brief Battery Class Destructor.
         */
        ~Battery() {}

        // ==================== accessors ====================
        /**
         * @brief Get the current charge of the battery
         *
         * @return double
         */
        double get_current_charge() const { return current_charge_; }

        // ==================== methods ====================

        /**
         * @brief Start charging the battery
         *
         */
        void start_charging();

        /**
         * @brief Discharge the battery - each time the robot moves, the battery discharges by 1 percent
         * @param amount
         */
        void discharge(double amount);

    }; // class Battery
} // namespace RWA2
