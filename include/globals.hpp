#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <future> // IWYU pragma: keep

extern pros::Motor bttm_intake_11w;
extern pros::Motor top_intake_11w;
extern pros::Motor flywheel_55w;
extern pros::Motor agitator_55w;
extern pros::Motor indexer_55w;
extern pros::Motor pushythingy_55w;
extern pros::adi::DigitalOut bttm_piston;
extern pros::adi::DigitalOut top_piston;
extern pros::adi::DigitalOut descorer_piston;
// create an imu on port 10
extern pros::Imu imu;
// create a v5 rotation sensor on port 1
extern pros::Rotation rotation_sensor_left;
// create a v5 rotation sensor on port 1
extern pros::Rotation rotation_sensor_right;
// create a v5 rotation sensor on port 1
extern pros::Rotation rotation_sensor_bottom;
extern pros::Controller master;
extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;
// drivetrain settings
extern lemlib::Drivetrain drivetrain;
// horizontal tracking wheel
extern lemlib::TrackingWheel horizontal_tracking_wheel;
 // vertical tracking wheel
extern lemlib::TrackingWheel vertical_tracking_wheel_1;
extern lemlib::TrackingWheel vertical_tracking_wheel_2;
extern lemlib::OdomSensors sensors;
// lateral PID controller
extern lemlib::ControllerSettings lateral_controller;

// angular PID controller  
extern lemlib::ControllerSettings angular_controller;
extern lemlib::Chassis chassis;