#pragma once

#include "mobile_robot.h"

namespace RWA2
{
    class AerialRobot final : public MobileRobot
    {

    private:
        // ==================== attributes ====================
        bool has_wings_;
        double altitude_{0.0};
        bool is_flying_ = false;

        // ==================== methods ====================
        void takeoff(double altitude);
        void land();

    protected:
        // ==================== methods ====================
        virtual void rotate(double angle) override;

    public:
        // ==================== constructor ====================
        /**
         * @brief Construct a new Aerial Robot object
         * - first argument: x position
         * - second argument: y position
         * - third argument: orientation
         * - fourth argument: robot model name
         * - fifth argument: battery model name
         * - sixth argument: current battery charge
         * - seventh argument: is charging?
         * - eigth argument: has wings?
         */
        AerialRobot(double x, double y, double orientation, std::string botmodel, std::string battmodel,
                    int current_charge, bool is_charging, bool has_wings) : MobileRobot(x, y, orientation, botmodel, battmodel, current_charge, is_charging), has_wings_{has_wings}
        {
        }
        // ==================== destructor ====================
        /**
         * @brief AerialRobot Class Destructor.
         */
        ~AerialRobot() {}

        // ==================== methods ====================
        /**
         * @brief Move the aerial robot (override method)
         *
         * @param distance
         * @param angle
         */
        virtual void move(double distance, double angle) override;

        /**
         * @brief Print the current status of the robot (override method)
         */
        virtual void print_status() override;

    }; // class AerialRobot
} // namespace RWA2