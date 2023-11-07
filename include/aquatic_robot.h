#pragma once

#include "mobile_robot.h"

namespace RWA2
{
    /**
     * @brief Class for aquatic robots
     *
     */
    class AquaticRobot final : public MobileRobot
    {

    private:
        // ==================== attributes ====================
        bool has_fins_;
        double depth_{0.0};
        bool is_diving_ = false;

        // ==================== methods ====================
        void dive(double depth);
        void surface();

    protected:
        // ==================== methods ====================
        virtual void rotate(double angle) override;

    public:
        // ==================== constructor ====================
        /**
         * @brief Construct a new Aquatic Robot object
         * - first argument: x position
         * - second argument: y position
         * - third argument: orientation
         * - fourth argument: robot model name
         * - fifth argument: battery model name
         * - sixth argument: current battery charge
         * - seventh argument: is charging?
         * - eigth argument: has fins?
         */
        AquaticRobot(double x, double y, double orientation, std::string botmodel, std::string battmodel,
                     int current_charge, bool is_charging, bool has_fins) : MobileRobot(x, y, orientation, botmodel, battmodel, current_charge, is_charging), has_fins_{has_fins}
        {
        }

        // ==================== destructor ====================
        /**
         * @brief AquaticRobot Destructor.
         */
        ~AquaticRobot() {}

        // ==================== methods ====================
        /**
         * @brief Move the aquatic robot (override method)
         *
         * @param distance
         * @param angle
         */
        virtual void move(double distance, double angle) override;

        /**
         * @brief Print position, orientation, speed, current battery charge, fin info, depth, and dive status (override method)
         */
        virtual void print_status() override;

    }; // class AquaticRobot
} // namespace RWA2