
#include "helpers.hpp"
#include "globals.hpp"

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
 // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    chassis.moveToPose(-2, 13, -47, 3000,{}, false);
    intake();
    chassis.moveToPose(-15, 20.75, -57, 2000);
    chassis.moveToPose(-47, 1, 0, 3000);
    top_piston.set_value(true);
    chassis.moveToPose(-43.25,14,0,2000, {}, false);
    highScore();
    // turn to face heading 90 with a very long timeout

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

