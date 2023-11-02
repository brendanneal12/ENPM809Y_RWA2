#pragma once

#include <iostream>
#include <utility>

#include "sensor.h"

namespace RWA2
{
  class MobileRobot
  {
  protected:
    // ==================== attributes ====================
    std::pair<double, double> position_;
    double orientation_;
    double speed_{0.0};
    std::vector<std::unique_ptr<RWA2::Sensor>> sensors_;
    std::string model_;

  public:
    /**
     * @brief Construct a new Mobile Robot object
     * - first argument: x position
     * - second argument: y position
     * - third argument: orientation
     */
    MobileRobot() : MobileRobot(0, 0, 0) {}
    /**
     * @brief Construct a new Mobile Robot object
     * - first argument: x position
     * - second argument: y position
     * - third argument: orientation
     */

    MobileRobot(double orientation) : MobileRobot(0, 0, orientation) {}
    /**
     * @brief Construct a new Mobile Robot object
     * - first argument: x position
     * - second argument: y position
     * - third argument: orientation
     */
    MobileRobot(double x, double y) : MobileRobot(x, y, 0) {}

    /**
     * @brief Construct a new Mobile Robot object
     * @note This is a delegating constructor
     * - first argument: x position
     * - second argument: y position
     * - third argument: orientation
     * - fourth argument: battery charge
     */
    MobileRobot(double x, double y, double orientation)
        : position_{x, y},
          orientation_{orientation} {}

    // ==================== accessors ====================
    /**
     * @brief Get the position of the robot
     *
     * @return std::pair<double, double>
     */
    std::pair<double, double> get_position() const { return position_; }
    /**
     * @brief Get the orientation of the robot
     *
     * @return double
     */
    double get_orientation() const { return orientation_; }
    /**
     * @brief Get the speed of the robot
     *
     * @return double
     */
    double get_speed() const { return speed_; }

    // ==================== methods ====================
    /**
     * @brief Move the mobile robot
     */
    virtual void move();
    /**
     * @brief Rotate the mobile robot
     *
     * @param angle Angle for robot to rotate
     */
    virtual void rotate(double angle);
    /**
     * @brief Print the current status of the robot (position, orientation, and speed).
     */
    virtual void print_status();

    /**
     * @brief Add a sensor to the robot
     *
     * @param sensor sensor to add
     */
    void add_sensor(std::unique_ptr<RWA2::Sensor> sensor);

  }; // class MobileRobot
} // namespace RWA2