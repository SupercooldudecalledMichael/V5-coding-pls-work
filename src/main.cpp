
#include "helpers.hpp"
#include "globals.hpp"
#include "pros/motors.h"

/*
git add .
git commit -m"ooga booga"
git push origin master

*/


void initialize() {
    pros::lcd::initialize();
    chassis.calibrate();
    bttm_piston.set_value(true);
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
    chassis.setPose(0, 0, 0);
    //auto win point
    //chassis.moveToPose(-2, 13, -47, 3000,{}, false);
    //intake();
    //chassis.moveToPose(-16, 21.75, -57, 2000);
    //chassis.moveToPose(-43.5, 1, 1, 3000);
    //top_piston.set_value(true);
    //chassis.moveToPose(-40.75,15,1,2000, {}, false);
    //highScore();
    
    //auto skills
    chassis.moveToPose(2,32.25,-90,4000);
    bttmDown();
    chassis.moveToPose(-15,30,-90,4000, {.minSpeed=50});
    intake();
    chassis.moveToPose(-14,30,-90,500, {.minSpeed=50});
    chassis.moveToPose(-15,30,-90,500, {.minSpeed=50});
    chassis.moveToPose(-14,30,-90,500, {.minSpeed=50});
    chassis.moveToPose(-15,30,-90,500, {.minSpeed=50});
    chassis.moveToPose(13, 30, 240, 4000, {.forwards=false, .minSpeed=40});
    chassis.moveToPose(-3, -62, 270.5, 4000, {.minSpeed=40});
    chassis.moveToPose(-14.75, -62, 270.5, 4000, {.minSpeed=40});
    intake();
    //auoto skills
    //chassis.moveToPoint(0, 40, 9000,  {.forwards = true, .minSpeed = 127});
}


void opcontrol() {
    while (true) {
        intakeControls();
        pnuematicControls();
        driverControls();
        // --- Pneumatic Controls ---
        
        

        // --- Drive Controls ---
        

        pros::delay(20);
    }
}

