#include "driver.h"
#include "config.h"
#include "misc.h"
#include "pros/misc.h"
#include "taskhandler.h"

// Button constants
#define MATCHLOAD_DOINKER_BUTTON pros::E_CONTROLLER_DIGITAL_RIGHT
#define DRIVER_MACRO_BUTTON pros::E_CONTROLLER_DIGITAL_LEFT

// Joystick axis constants
#define THROTTLE_AXIS pros::E_CONTROLLER_ANALOG_LEFT_Y
#define STEER_AXIS pros::E_CONTROLLER_ANALOG_RIGHT_X


// Deceleration rates
#define THROTTLE_DECEL_RATE 5
#define STEER_DECEL_RATE 5

namespace Driver {
    bool b_loader = false;
    bool b_clamp = false;
    bool b_aligner = false;
    bool b_hook = false;
    bool b_driver = false;
    bool b_middle = false;
    int saberC = 0;
    double curveVal = 7.0;

    void joystick() {
        
        while(1){
            if(TaskHandler::driver) {
                // get left y and right x positions
                const int throttle = controller.get_analog(THROTTLE_AXIS);
                const int steer = controller.get_analog(STEER_AXIS);

                chassis.arcade(throttle, steer, true);
            }
            pros::delay(Misc::DELAY);
        }
    }

    /**
     * @brief Function that controls intake motors
     * R1: Intake in (bottom + middle forward, top reverse)
     * R2: Outtake (bottom + middle reverse, top forward)
     * Y: Slow intake (bottom + middle slow forward, top slow reverse)
     * UP: Slow outtake (bottom + middle slow reverse, top slow forward)
     * DOWN: Fast intake with top at medium speed
     */
    void moveIntake(){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            ::intake.move(127);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
        } // if intake button (R1) is pressed
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            ::intake.move(127);
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
        } // if outtake button (R2) is pressed
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
            ::intake.move(-127);
        }
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
            ::intake.move(115);
            Piston::ballLock.set_value(true); // ball lock piston goes down
            Piston::middle.set_value(false);
        }
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
            ::intake.move(127);
        }
        else{
            ::intake.move(0);
        } // if neither are pressed, intake doesn't move
    }


    /**
     * @brief Function that controls ball lock and middle pistons with triple state
     * L1 button cycles through three states:
     * State 1: balllock-extended, middle-retracted
     * State 2: both retracted
     * State 3: both extended
     */
    // void ballLockFunction(){
    //     static bool lock = false; // static lock boolean value
    //     if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){ // if controller L1 button is pressed
    //         if (!lock) { // if lock is false
    //             Piston::ballLock.set_value(true); // ball lock piston goes down
    //             Piston::middle.set_value(false);
    //             controller.rumble(".-.-");
    //             lock = true; // lock is set to true
    //         } else { // if lock is true
    //             Piston::ballLock.set_value(true);
    //             Piston::middle.set_value(true);
    //             lock = false; // lock is set back to false
    //         }
    //     }   
    // }

    /**
     * @brief Function that controls matchload doinker
     * RIGHT button toggles matchload doinker and runs bottom intake
     */
    void matchloadDoinkerControl(){
        static bool doink = true; // static doink boolean value
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){ // if controller right button is pressed
            if (doink) { // if doink is false
                Piston::loader.set_value(false); // matchload doinker mech goes down
                doink = false; // doink is set to true
            } else { // if doink is true
                Piston::loader.set_value(true); // matchload doinker goes back up 
                doink = true; // doink is set back to true
            }
        }
    }

    /**
     * @brief Function that controls trapdoor/middle goal piston
     * X button toggles trapdoor mover
     */
    void trapdoorDoinkerControl(){
        static bool oink = false; // static oink boolean value
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){ // if controller X button is pressed
            if (!oink) { // if oink is false
                Piston::middle.set_value(true); // trapdoor mover goes down
                controller.rumble(".-.-");
                oink = true; // oink is set to true
            } else { // if oink is true
                Piston::middle.set_value(false); // trapdoor mover goes back up
                oink = false; // oink is set back to false
            }
        }
    }

    /**
     * @brief Function that controls descore mechanism (wing piston)
     * L2 button toggles descore piston
     */
    void descoreMechanism(){
        static bool descore = false; // static descore boolean value
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){ // if controller L2 button is pressed
            if (!descore) { // if descore is false
                Piston::hook.set_value(true); // descore piston goes down
                descore = true; // descore is set to true
            } else { // if descore is true
                Piston::hook.set_value(false); // descore piston goes back up
                descore = false; // descore is set back to false
            }
        }
    }

    /**
     * @brief Main intake control task
     * Runs moveIntake function in a loop
     */
    void intake() {
        while(1){
            if(TaskHandler::intake){
                moveIntake();
            }
            pros::delay(Misc::DELAY);
        }
    }

    /**
     * @brief Main piston control task
     * Runs all piston control functions in a loop
     */
    void piston() {
        while(1){
            //ballLockFunction();
            matchloadDoinkerControl();
            trapdoorDoinkerControl();
            descoreMechanism();
            pros::delay(Misc::DELAY);
        }
    }
}
