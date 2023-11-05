#pragma once

#include <iostream>
#include <utility>
#include <string>

#include "sensor.h"
#include "battery.h"

namespace RWA2
{
  class MobileRobot
  {
  protected:
    // ==================== attributes ====================
    std::pair<double, double> position_;
    double orientation_;
    double speed_{0.0};
    RWA2::Battery battery_;
    std::vector<std::unique_ptr<RWA2::Sensor>> sensors_;
    std::string model_;

    // ==================== methods ====================
    virtual void rotate(double angle);

  public:
    // ==================== constructor ====================
    /**
     * @brief Construct a new Mobile Robot object
     * - first argument: x position
     * - second argument: y position
     * - third argument: orientation
     * - fourth argument: robot model name
     * - fifth argument: battery model name
     * - sixth argument: current battery charge
     * - seventh argument: is charging
     */
    MobileRobot(double x, double y, double orientation, std::string botmodel, std::string battmodel, int current_charge, bool is_charging)
        : position_{x, y},
          orientation_{orientation},
          model_{botmodel},
          battery_{battmodel, current_charge, is_charging} {}

    // ==================== destructor ====================

    /**
     * @brief MobileRobot Virtual Destructor.
     */
    virtual ~MobileRobot() {}

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

    /**
     * @brief Get the battery level of the robot
     *
     * @return double
     */
    double get_battery_level() const { return battery_.get_current_charge(); }

    /**
     * @brief Initiate Sensor Read
     * @param period period of the sensor reading
     */
    void get_sensor_reading(unsigned int period) const;

    // ==================== methods ====================
    /**
     * @brief Move the mobile robot (pure virtual method)
     *
     * @param distance
     * @param angle
     */
    virtual void move(double distance, double angle) = 0;

    /**
     * @brief Print the current status of the robot (position, orientation, and speed) (virtual method).
     */
    virtual void print_status();

    /**
     * @brief Add a sensor to the robot.
     *
     * @param sensor
     */
    void add_sensor(std::unique_ptr<RWA2::Sensor> sensor);

  }; // class MobileRobot
} // namespace RWA2