#include "main.h"

//Helper function
void setDrive(int left, int right){
    leftfront = left;
    leftback1 = left;
    leftback2 = left;
    rightfront = right;
    rightback1 = right;
    rightback2 = right;
}

// Driver Control Functions
void setDriveMotors(){
    //declare controller sticks
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // Define the joystick deadzone
    const int JOYSTICK_DEADZONE = 10;

    // Apply the joystick deadzone
    if (abs(leftJoystick) < JOYSTICK_DEADZONE) {
      leftJoystick = 0;
    }
    if (abs(rightJoystick) < JOYSTICK_DEADZONE) {
      rightJoystick = 0;
    }

    setDrive(leftJoystick,rightJoystick);

}