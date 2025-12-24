// <--------------------------------------------------------------- Includes --------------------------------------------------------------->
#include <bits/stdc++.h>
#include <vector>
#include <functional>
#include <string>
#include "main.h"
#include "equinox/api.hpp"
#include "equinox/chassis/chassis.hpp"
#include "liblvgl/lvgl.h"
#include "liblvgl/llemu.hpp"
#include "brainScreenLVGL.h"
#include "config.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "taskhandler.h"
#include "misc.h"
#include "color.h"
#include "jam.h"
#include "autons.h"
#include "driver.h"
#include "screen.h"

std::vector<std::pair<float, float>> points;

// LV_IMG_DECLARE(tdbg);
// LV_IMG_DECLARE(WORLDS_logo);
LV_IMG_DECLARE(WO_logo);
LV_IMG_DECLARE(Final_log);
LV_IMG_DECLARE(screen);
LV_IMG_DECLARE(sixseven);
LV_IMG_DECLARE(gay);
// lv_obj_t * sbg = lv_img_create(lv_scr_act());
lv_obj_t * sixSeven = lv_img_create(lv_scr_act());
lv_obj_t * sKiss = lv_img_create(lv_scr_act());
lv_obj_t * slogo = lv_img_create(lv_scr_act());
lv_obj_t * Wlogo = lv_img_create(lv_scr_act());
lv_obj_t * Slogo = lv_img_create(lv_scr_act());

// lv_img_set_src(Wlogo, &WORLDS_logo);
// lv_obj_set_pos(Wlogo, 10, 3);
// <------------------------------------------------------------ Initialize --------------------------------------------------------------->
void initialize() {
    pros::Task t_Select(autonSwitch);
    pros::lcd::initialize();
    chassis.setPose(0, 0, 0);
    chassis.calibrate(); 
    Sensor::o_colorSort.set_led_pwm(100);
    Sensor::o_colorSort.set_integration_time(5);
    Sensor::o_crossed.set_led_pwm(100);
    Sensor::o_crossed.set_integration_time(5);
    Motor::intakeF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); 
    Motor::intakeM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    Motor::intakeU.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    // lv_init();
    // set_up();
    // pros::Task LVGL_upd([&]() { screen_upd(); });

	// lv_img_set_src(slogo, &Final_log);
	// lv_obj_set_pos(slogo, 20, 15);

    // lv_img_set_src(Slogo, &screen);
	// lv_obj_set_pos(Slogo, 0, 0);

    // lv_img_set_src(sixSeven, &sixseven);
	// lv_obj_set_pos(sixSeven, 160, 0);

    pros::Task screenTask([&]() {
        while (1) {
            // Misc::resetB1();
            pros::lcd::print(0, "X: %f", chassis.getPose().x);
            pros::lcd::print(1, "Y: %f", chassis.getPose().y);
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
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
    // pros::lcd::shutdown();
    // lv_init();
    // lv_img_set_src(sKiss, &gay);
	// lv_obj_set_pos(sKiss, 0, 0);

    // lv_img_set_src(sixSeven, &sixseven);
	// lv_obj_set_pos(sixSeven, 140, 0);

    pros::Task intakeTask(Driver::intake);
    pros::Task driverTask(Driver::joystick);
    pros::Task pistonTask(Driver::piston);
    TaskHandler::colorSort = false;
    TaskHandler::antiJam = false;
	leftMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST); rightMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    Motor::intakeF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    Motor::intakeM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    Motor::intakeU.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    // Lift::setState(0);
    // Piston::tipper.set_value(false);
    // pros::lcd::clear();
    // lv_img_set_src(sbg, &tdbg);
	// lv_obj_set_pos(sbg,0,0);
	// lv_img_set_src(slogo, &logo);
	// lv_obj_set_pos(slogo,105,-15);
    while(1) {
        // Sensor::o_colorSort.set_led_pwm(100);
        // Color::colorSort(Color::colorVals::BLUE);
        
        // if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        //     TaskHandler::isDriver = false;
        //     Misc::cdrift(30,30,230,true);
        //     TaskHandler::isDriver = true;
        // }
        // if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) Driver::release();
        // right = goal tip
        // down = left doinker
        // b = right do
        // 
        pros::delay(Misc::DELAY);
    }
}