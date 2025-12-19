#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <future> // IWYU pragma: keep

pros::Motor bttm_intake_11w(11, pros::v5::MotorGears::blue);
pros::Motor top_intake_11w(13, pros::v5::MotorGears::blue);
pros::Motor flywheel_55w(14, pros::v5::MotorGears::green);
pros::Motor agitator_55w(21, pros::v5::MotorGears::green);
pros::Motor indexer_55w(20, pros::v5::MotorGears::green);
pros::Motor pushythingy_55w(16,pros::v5::MotorGears::green);
pros::adi::DigitalOut bttm_piston(6,false);
pros::adi::DigitalOut top_piston(7,false);
pros::adi::DigitalOut descorer_piston(8,true);
// create an imu on port 10
pros::Imu imu(-12);
// create a v5 rotation sensor on port 1
pros::Rotation rotation_sensor_left(10);
// create a v5 rotation sensor on port 1
pros::Rotation rotation_sensor_right(1);
// create a v5 rotation sensor on port 1
pros::Rotation rotation_sensor_bottom(6);
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup left_mg({4,5});
pros::MotorGroup right_mg({-7,-8});
// drivetrain settings
lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              &right_mg, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              333.333333,// drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&rotation_sensor_bottom, lemlib::Omniwheel::NEW_275, -4.5);
 // vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel_1(&rotation_sensor_left, lemlib::Omniwheel::NEW_275, -7.5, 0.5);
lemlib::TrackingWheel vertical_tracking_wheel_2(&rotation_sensor_right, lemlib::Omniwheel::NEW_275, 7.5, 0.5);
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                             nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr,//&horizontal_tracking_wheel_2, //set to nullptr as we don't have a second one
                            &imu // inertial sensor
);
// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular PID controller  
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);