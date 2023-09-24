#include "main.h"

// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {4,5,6}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{1,2,3}

  // IMU Port
  ,21

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,4.125

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,36/84

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

// Define the drivestick
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Define the joystick deadzone
const int JOYSTICK_DEADZONE = 10;

void opcontrol() {
  // Set the drive brake type
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {
    // Get the joystick values
    int forward = controller.get_analog(ANALOG_LEFT_Y);
    int back = controller.get_analog(ANALOG_LEFT_X);
    int left = controller.get_analog(ANALOG_RIGHT_Y);
    int right = controller.get_analog(ANALOG_RIGHT_X);

    // Apply the joystick deadzone
    if (abs(forward) < JOYSTICK_DEADZONE) {
      forward = 0;
    }
    if (abs(back) < JOYSTICK_DEADZONE) {
      back = 0;
    }
    if (abs(left) < JOYSTICK_DEADZONE) {
      left = 0;
    }
    if (abs(right) < JOYSTICK_DEADZONE) {
      right = 0;
    }

    // Calculate the left and right motor speeds
    int left_speed = (forward - back + left - right) * 3 / 7;
    int right_speed = (forward - back - left + right) * 3 / 7;

    // Set the motor speeds
    chassis.tank(left_speed, right_speed);
    
    // Wait for a short amount of time to prevent the loop from running too fast
    pros::delay(20);
  }
}



// Sample code by copilot

// Define the chassis motors
// pros::Motor left_chassis_1(4, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor left_chassis_2(5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor left_chassis_3(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor right_chassis_1(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor right_chassis_2(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
// pros::Motor right_chassis_3(3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

// Define the drivestick
// pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Define the chassis
// pros::Chassis chassis({left_chassis_1, left_chassis_2, left_chassis_3}, {right_chassis_1, right_chassis_2, right_chassis_3});

// Define the joystick deadzone
// const int JOYSTICK_DEADZONE = 10;

// void opcontrol() {
//   // Set the drive brake type
//   chassis.set_drive_brake(MOTOR_BRAKE_COAST);

//   while (true) {
//     // Get the joystick values
//     int forward = controller.get_analog(ANALOG_LEFT_Y);
//     int back = controller.get_analog(ANALOG_LEFT_X);
//     int left = controller.get_analog(ANALOG_RIGHT_Y);
//     int right = controller.get_analog(ANALOG_RIGHT_X);

//     // Apply the joystick deadzone
//     if (abs(forward) < JOYSTICK_DEADZONE) {
//       forward = 0;
//     }
//     if (abs(back) < JOYSTICK_DEADZONE) {
//       back = 0;
//     }
//     if (abs(left) < JOYSTICK_DEADZONE) {
//       left = 0;
//     }
//     if (abs(right) < JOYSTICK_DEADZONE) {
//       right = 0;
//     }

//     // Calculate the left and right motor speeds
//     int left_speed = (forward - back + left - right) * 3 / 7;
//     int right_speed = (forward - back - left + right) * 3 / 7;

//     // Set the motor speeds
//     chassis.tank(left_speed, right_speed);
    
//     // Wait for a short amount of time to prevent the loop from running too fast
//     pros::delay(20);
//   }
// }