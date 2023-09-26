#include "main.h"

// Helper Functions
void setIntake(int power){
    intake_motor_left = power;
    intake_motor_right = power;
}

// Driver Control Functions
void setIntakeMotors(){
    
    //L2 triggers outtake, L1 triggers intake
    int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
    setIntake(intakePower);

}