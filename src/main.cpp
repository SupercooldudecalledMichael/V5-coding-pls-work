
#include "helpers.hpp"
#include "globals.hpp"
#include "pros/motors.h"
//This is the skills
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
    bttmUp();
    intake();
    chassis.moveToPoint(0, 14, 5000, {.minSpeed=127}, false); 
    //chassis.moveToPose(0, 2, 0, 14000);
    //auto win point
    //chassis.moveToPose(-2, 13, -47, 3000,{}, false);
    //intake();
    //chassis.moveToPose(-16, 21.75, -57, 2000);
    //chassis.moveToPose(-43.5, 1, 1, 3000);
    //top_piston.set_value(true);
    //chassis.moveToPose(-40.75,15,1,2000, {}, false);
    //highScore();
    
    //auto skills
    //chassis.moveToPose(0,10,0,1500);
    //chassis.moveToPose(2,32.7,-80,3000);
    //intake();
    //bttmDown();
    //chassis.moveToPose(-70,26,-80,1000, {.minSpeed=99});
    //chassis.moveToPoint(70, 26,200, {.forwards=false, .minSpeed=50});
    //chassis.moveToPoint(-70,26,1250, {.minSpeed=100});
    //chassis.moveToPoint(70, 26,200, {.forwards=false, .minSpeed=50});
    //chassis.moveToPoint(-70,26,1250, {.minSpeed=100});
    //chassis.moveToPoint(70, 26,200, {.forwards=false, .minSpeed=50});
    //chassis.moveToPoint(-70,26,1250, {.minSpeed=100});
    //pros::delay(2000);
    //chassis.moveToPoint(-4, 30, 1000, {.forwards=false});
    //chassis.turnToHeading(330, 2000, {}, false);
    //pros::delay(500);
    //bttmUp();
    //alignerUp();
    //chassis.moveToPoint(6, 34.75, 3000, {}, false);
    //highScore();
    //pros::delay(5000);
    //chassis.moveToPoint(-2, 34, 2000, {.forwards=false}, false);
    //chassis.turnToHeading(220, 1000);
    //chassis.moveToPoint(-28, 20, 2500, {}, false);
    //chassis.turnToHeading(170, 1000, {}, false);
    //bttmUp();
    //chassis.moveToPoint(-26, -14, 1600, {.forwards=false, .minSpeed=127});
    //chassis.moveToPoint(-26, 0, 1600, {.forwards=true, .minSpeed=127});
    //chassis.moveToPoint(-26, -14, 1600, {.forwards=false, .minSpeed=127});
    //chassis.moveToPoint(-26, 0, 1600, {.forwards=true, .minSpeed=127});
    //chassis.moveToPoint(-26, -14, 1600, {.forwards=false, .minSpeed=127});
    //chassis.moveToPoint(-26, 0, 1600, {.forwards=true, .minSpeed=127});
    //chassis.moveToPoint(-26, -14, 1600, {.forwards=false, .minSpeed=127});
    //chassis.moveToPoint(-26, 0, 1600, {.forwards=true, .minSpeed=127});
    //chassis.moveToPoint(-26, -14, 1600, {.forwards=false, .minSpeed=127});
    //chassis.moveToPoint(-26, 0, 1600, {.forwards=true, .minSpeed=127});
    
//KKK I HATE Niggersssss In my butt nig nig nig nig niggers in my butt nig nig nig nig nig niggers nig nig nig fuck me im a nigger
    
    //chassis.moveToPose(12, 29, 240, 4000, {.forwards=false, .minSpeed=40}, false);
    //unJam = false;
    //chassis.moveToPose(2, -61, 268.5, 4000, {.minSpeed=40}, false);
    //chassis.moveToPose(-4.75, -60, 268.5, 4000, {.minSpeed=127}, false);
    //chassis.moveToPose(-15.75, -60, 268.5, 6000, {.minSpeed=127}, false);
    //intake();
    //chassis.moveToPose(-16.75, -60, 268.5, 2000, {.minSpeed=127}, false);
    //pros::delay(1000);
    //chassis.moveToPose(8, -59.5, -70, 2000, {.forwards=false, .minSpeed=68}, false);
    //bttmUp();
    //chassis.moveToPose(-17, -30, 0, 1500);
    //chassis.moveToPose(-14, -40.35, -100, 3000, {.minSpeed=68});
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

