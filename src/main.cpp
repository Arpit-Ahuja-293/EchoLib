// <--------------------------------------------------------------- Includes --------------------------------------------------------------->
#include <bits/stdc++.h>
#include <vector>
#include <functional>
#include <string>
#include "main.h"
#include "equinox/api.hpp"
#include "equinox/chassis/chassis.hpp"
#include "config.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "taskhandler.h"
#include "misc.h"
#include "jam.h"
#include "autons.h"
#include "driver.h"
#include "distanceSense.h"
#include "screen.h"

std::vector<std::pair<float, float>> points;
// <------------------------------------------------------------ Initialize --------------------------------------------------------------->
void initialize() {
    pros::Task t_Select(autonSwitch);
    pros::lcd::initialize();
    chassis.setPose(0, 0, 0);
    chassis.calibrate(); 
    // Sensor::o_crossed.set_led_pwm(100);
    // Sensor::o_crossed.set_integration_time(5);
    Motor::intakeF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); 
    Motor::intakeM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);


    pros::Task screenTask([&]() {
        while (1) {
            // Misc::resetB1();
            pros::lcd::print(0, "X: %f", chassis.getPose().x);
            pros::lcd::print(1, "Y: %f", chassis.getPose().y);
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
            pros::lcd::print(6, "rightDistance: %f", getRightDist());
            pros::lcd::print(7, "rightDistance Confidence: %ld", Sensor::d_right.get_confidence());
            pros::delay(50);

        }
    });

    pros::Task autonSelect([]{ while(1){ autonSwitch(); pros::delay(Misc::DELAY); }});
    // pros::Task stopIntake([]{ while(1){ Jam::intake(); pros::delay(Misc::DELAY); }});
    // pros::Task screenC([]{ while (1) { Screen::update(); pros::delay(100); }});
}

void disabled() {}

void competition_initialize() {}

ASSET(example_txt); // PP

// <------------------------------------------------------------- Auton ------------------------------------------------------------->
void autonomous() {
    (autonState < autonRoutines.size()) ? autonRoutines[autonState].second() : Auton::Test::main();
}

// <--------------------------------------------------------------- Driver --------------------------------------------------------------->
void opcontrol() {

    pros::Task intakeTask(Driver::intake);
    pros::Task driverTask(Driver::joystick);
    pros::Task pistonTask(Driver::piston);
    TaskHandler::antiJam = false;
	leftMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST); rightMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    Motor::intakeF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    Motor::intakeM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    while(1) {
        pros::delay(Misc::DELAY);
    }
}