#include "globals.hpp"
void intake(){
    bttm_intake_11w.move(100);
    top_intake_11w.move(-127);
    pushythingy_55w.move(-127);
    flywheel_55w.move(- 127);
    top_piston.set_value(false);
}
void highScore(){
    bttm_intake_11w.move(100);
    top_intake_11w.move(-127);
    indexer_55w.move(74);
    flywheel_55w.move(127);
    agitator_55w.move(127);
    pushythingy_55w.move(127);
    top_piston.set_value(true);

}
void midScore(){
    bttm_intake_11w.move(127);
    top_intake_11w.move(-37);
    indexer_55w.move(74);
    agitator_55w.move(74);
    pushythingy_55w.move(127);
    top_piston.set_value(true);
}
void lowScore(){
    bttm_intake_11w.move(-50);
    indexer_55w.move(39);
    agitator_55w.move(127);
    pushythingy_55w.move(127);
    top_piston.set_value(false);
}
void reverse(){
    bttm_intake_11w.move(-127);
    top_intake_11w.move(127);
    flywheel_55w.move(-127);
    pushythingy_55w.move(127);
    indexer_55w.move(-74);
    top_piston.set_value(false);
}
void prep(){
    bttm_intake_11w.move(100);
    top_intake_11w.move(-127);
    pushythingy_55w.move(127);
    flywheel_55w.move(127);
    top_piston.set_value(false);
}
void bttmUp(){
bttm_piston.set_value(true);
}
void bttmDown(){
bttm_piston.set_value(false);
}
void descorerUp(){
descorer_piston.set_value(false);
}
void descorerDown(){
descorer_piston.set_value(true);
}
void intakeControls(){
    // --- Intake Controls ---
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intake();
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            lowScore();
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            highScore();
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            midScore();
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
            reverse();
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
            prep();
        }
        else {
            bttm_intake_11w.move(0);
            top_intake_11w.move(0);
            indexer_55w.move(0);
            agitator_55w.move(0);
            flywheel_55w.move(0);
            pushythingy_55w.move(0);
        }
}
void pnuematicControls(){
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        bttmUp();
        }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        bttmDown();
        }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        descorerUp();
        }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        descorerDown();
        }
}
void driverControls(){
    int dir = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    left_mg.move(dir - turn);
    right_mg.move(dir + turn);
}