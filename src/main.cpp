#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/pose.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

pros::Motor bttm_intake_11w(11, pros::v5::MotorGears::blue);
pros::Motor top_intake_11w(13, pros::v5::MotorGears::blue);
pros::Motor flywheel_55w(14, pros::v5::MotorGears::green);
pros::Motor agitator_55w(21, pros::v5::MotorGears::green);
pros::Motor indexer_55w(20, pros::v5::MotorGears::green);
pros::Motor pushythingy_55w(16,pros::v5::MotorGears::green);
pros::adi::DigitalOut piston(6,false);
// create an imu on port 10
pros::Imu imu(12);
// create a v5 rotation sensor on port 1
pros::Rotation rotation_sensor_left(10);
// create a v5 rotation sensor on port 1
pros::Rotation rotation_sensor_right(1);
// create a v5 rotation sensor on port 1
pros::Rotation rotation_sensor_bottom(-18);
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup left_mg({4,5});
pros::MotorGroup right_mg({-7,-8});
// drivetrain settings
lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              &right_mg, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              400,// drivetrain rpm is 360
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
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
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
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);
void initialize() {
    pros::lcd::initialize();
    chassis.calibrate();
    
    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources

    
            pros::delay(50);
        }
    });
}

void disabled() {}
void competition_initialize() {}
void autonomous() {
 // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.turnToHeading(90, 5000);
}


void opcontrol() {
    lemlib::Pose poseA(chassis.getPose().x, chassis.getPose().y, 0);
    chassis.setPose(poseA);
    while (true) {
        // --- Intake Controls ---
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            bttm_intake_11w.move(127);
            top_intake_11w.move(-127);
            pushythingy_55w.move(-127);
            flywheel_55w.move(-127);
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            bttm_intake_11w.move(-127);
            indexer_55w.move(127);
            agitator_55w.move(127);
            pushythingy_55w.move(127);
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            bttm_intake_11w.move(127);
            top_intake_11w.move(-127);
            indexer_55w.move(127);
            flywheel_55w.move(127);
            agitator_55w.move(127);
            pushythingy_55w.move(127);
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            bttm_intake_11w.move(127);
            indexer_55w.move(127);
            agitator_55w.move(127);
            pushythingy_55w.move(127);
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
            bttm_intake_11w.move(-127);
            top_intake_11w.move(127);
            flywheel_55w.move(-127);
            pushythingy_55w.move(127);
            indexer_55w.move(127);
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
            bttm_intake_11w.move(-62);
            indexer_55w.move(127);
            agitator_55w.move(127);
            pushythingy_55w.move(127);
            top_intake_11w.move(62);
            flywheel_55w.move(-127);
        }
        else {
            bttm_intake_11w.move(0);
            top_intake_11w.move(0);
            indexer_55w.move(0);
            agitator_55w.move(0);
            flywheel_55w.move(0);
            pushythingy_55w.move(0);
        }

        // --- Pneumatic Controls ---
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            piston.set_value(true);
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            piston.set_value(false);
        }

        // --- Drive Controls ---
        int dir = master.get_analog(ANALOG_LEFT_Y);
        int turn = master.get_analog(ANALOG_RIGHT_X);
        left_mg.move(dir - turn);
        right_mg.move(dir + turn);

        pros::delay(20);
    }
}

