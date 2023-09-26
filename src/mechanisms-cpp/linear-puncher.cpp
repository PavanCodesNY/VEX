#include "main.h"

// Helper Functions
void setPuncher(int power){
    linear_puncher = power;
}

void setPuncherMotors(){
    int puncherPower = 127 * controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    setIntake(puncherPower);
}