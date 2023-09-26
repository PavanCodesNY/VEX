#include "main.h"

// Motors
pros::Motor leftfront(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftback1(2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftback2(3, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightfront(4, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightback1(5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightback2(6, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor linear_puncher(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake_motor_left(8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake_motor_right(9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);