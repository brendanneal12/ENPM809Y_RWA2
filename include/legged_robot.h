#pragma once

#include "mobile_robot.h"

namespace RWA2
{
    /**
     * @brief Class for legged robots
     *
     */
    class LeggedRobot final : public MobileRobot
    {

    private:
        // ==================== attributes ====================
        double height_;
        int leg_strength_;
        int number_of_legs_{2};

        // ==================== methods ====================
        void kick();
        void jump(double amount);

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
         * - eigth argument: height
         * - ninth argument: leg strength
         * - tenth argument: number of legs
         */
        LeggedRobot(double x, double y, double orientation, std::string botmodel, std::string battmodel,
                    int current_charge, bool is_charging, double height, int leg_strength, int number_of_legs) : MobileRobot(x, y, orientation, botmodel, battmodel, current_charge, is_charging),
                                                                                                                 height_{height}, leg_strength_{leg_strength}, number_of_legs_{number_of_legs}
        {
        }

        // ==================== destructor ====================
        /**
         * @brief Legged Robot Destructor.
         */
        ~LeggedRobot() {}

        // ==================== methods ====================
        /**
         * @brief Move the legged robot (override method)
         *
         * @param distance
         * @param angle
         */
        virtual void move(double distance, double angle) override;

        /**
         * @brief Print position, orientation, speed, current battery charge, height, leg strength, and number of legs (override method)
         */
        virtual void print_status() override;

    }; // class LeggedRobot
} // namespace RWA2