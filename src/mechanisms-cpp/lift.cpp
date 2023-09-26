#include "main.h"

pros::ADIPotentiometer testpot('A');

// Helper Functions
void setLift(int left, int right){
    leftback2 = power;
    rightback2 = power;
}

void setLiftMotors(){
    int liftPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
    setLift(liftPower);
}