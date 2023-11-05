#pragma once

#include "mobile_robot.h"

namespace RWA2
{
    class WheeledRobot final : public MobileRobot
    {

    private:
        // ==================== attributes ====================
        int number_of_wheels_{2};
        double wheel_diameter_;
        double desired_speed_;

        // ==================== methods ====================
        void accelerate(double amount);
        void deceletate(double amount);
        void brake();

    protected:
        // ==================== methods ====================
        virtual void rotate(double angle) override;

    public:
        // ==================== constructor ====================
        /**
         * @brief Construct a new Wheeled Robot object
         * - first argument: x position
         * - second argument: y position
         * - third argument: orientation
         * - fourth argument: robot model name
         * - fifth argument: battery model name
         * - sixth argument: current battery charge
         * - seventh argument: is charging?
         * - eigth argument: number of wheels
         * - ninth argument: wheel diameter
         * - tenth argument: desired speed
         */
        WheeledRobot(double x, double y, double orientation, std::string botmodel, std::string battmodel,
                     int current_charge, bool is_charging, int number_of_wheels, double wheel_diameter, double desired_speed) : MobileRobot(x, y, orientation, botmodel, battmodel, current_charge, is_charging),
                                                                                                                                number_of_wheels_{number_of_wheels}, wheel_diameter_{wheel_diameter}, desired_speed_{desired_speed}
        {
        }

        // ==================== destructor ====================
        /**
         * @brief WheeledRobot Destructor.
         */
        ~WheeledRobot() {}

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

    }; // class WheeledRobot
} // namespace RWA2