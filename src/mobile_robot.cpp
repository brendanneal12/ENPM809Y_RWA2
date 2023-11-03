#include <chrono>
#include <iostream>
#include <thread>

#include "mobile_robot.h"

void RWA2::MobileRobot::add_sensor(std::unique_ptr<RWA2::Sensor> sensor)
{
    sensors_.push_back(std::move(sensor));
}

void RWA2::MobileRobot::get_sensor_reading(unsigned int period) const{
  for (const auto& sensor : sensors_) {
    sensor->read_data(period);
  }
}

void RWA2::MobileRobot::rotate(double angle) {
  std::cout << "MobileRobot: Rotating " << angle << " degrees\n";
}

void RWA2::MobileRobot::move(double distance, double angle) {
  std::cout << "MobileRobot: Moving\n";
}

void RWA2::MobileRobot::print_status() {
  std::cout << "================\n";
  std::cout
      << "Position: (" << position_.first << ", "
      << position_.second << "), Orientation: " << orientation_
      << ", Speed: " << speed_ << "\n";
}