#include "autons.h"
#include "taskhandler.h"
#include "config.h"

int autonState = 0;

namespace Auton {
    int state = 0;
    
    namespace Test {
        void main() { 
            Misc::cdrift(55,55,550);
        }
    }

    namespace Template {
        void left(){
            chassis.setPose(0,0,0);
            chassis.moveToPoint(0,24,10000,{.maxSpeed=110});
        }

        void right(){
            
        }

        void solo(){          
            
        }

        void leftseven(){
            chassis.setPose(48,-15,270);
            Piston::hook.set_value(true);
            Motor::intakeF.move(127); 
            chassis.moveToPoint(22,-22.5,1750,{.forwards=true,.maxSpeed=127,.minSpeed=10,.earlyExitRange=1});
            chassis.waitUntil(6);
            Piston::loader.set_value(true);
            chassis.waitUntilDone();
            chassis.turnToPoint(66,-42,400,{.maxSpeed=90,.minSpeed=10,.earlyExitRange=0});
            // chassis.moveToPoint(63,-45,400,{.forwards=true,.maxSpeed=127,.minSpeed=10,.earlyExitRange=1});
            chassis.moveToPose(65,-44.5,90,1250,{.forwards=true,.horizontalDrift=8,.lead=0.41,.maxSpeed=127,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            Misc::cdrift(45,45,350);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,590);
            chassis.moveToPoint(20,-46,1250,{.forwards=false,.maxSpeed=90,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntilDone();
            Motor::intakeF.move(-127); 
            Motor::intakeU.move(-127);
            pros::delay(40);
            Motor::intakeF.move(127); 
            Motor::intakeU.move(127);
            Misc::cdrift(-20,-20,1500);
            Motor::intakeU.brake();
            Piston::loader.set_value(false);

            chassis.moveToPoint(42,-32,1250,{.forwards=true,.maxSpeed=127,.minSpeed=10,.earlyExitRange=2});
            chassis.waitUntilDone();
            Piston::hook.set_value(false);
            chassis.moveToPoint(14,-36,1750,{.forwards=false,.maxSpeed=85,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            Misc::cdrift(0,-15);
            chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
        }

        void rightFourRush(){
            chassis.setPose(0,0,0);
            //0.64, 36.745
            chassis.moveToPoint(0, 34.345, 1250, {.maxSpeed=127});
            ::intake.move(127);
            Motor::intakeU.move(-127); 
            //90
            chassis.turnToHeading(90,800,{.maxSpeed=90});
            chassis.waitUntilDone();
            Piston::loader.set_value(true);
            pros::delay(200);
            //7.62, 37.16
            chassis.moveToPose(9.35, 37.26, 90, 1000, {.lead = 0.1, .maxSpeed=120});
            chassis.waitUntilDone();
            Misc::cdrift(45,45,250);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,150);
            chassis.moveToPose(-24.20, 38.14, 90, 1250, {.forwards = false, .lead = 0.1, .maxSpeed = 110});
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true);
            pros::delay(1000);
            chassis.moveToPoint(-14.2, 38.14, 800, {.maxSpeed=127});
            Piston::loader.set_value(false);
            chassis.turnToHeading(0, 800, {.maxSpeed=90});
            //-16.25, 45.27
            chassis.moveToPoint(-16.25, 48.9, 800, {.maxSpeed=127});
            chassis.turnToHeading(-90, 800, {.maxSpeed=90});
            //-41.56, 47.03, -89.5
            chassis.moveToPoint(-44.84, 48.03, 1250, {.maxSpeed=110});
            
        }

        void rushAWP(){
            chassis.setPose(48,-15,270);
            Piston::hook.set_value(true);
            Motor::intakeF.move(127); 

            chassis.moveToPose(8.5,-46.5,180,1250,{.forwards=true,.horizontalDrift=11,.lead=0.44,.maxSpeed=127,.minSpeed=0,.earlyExitRange=1});
            chassis.waitUntilDone();
            
            chassis.moveToPoint(29,-36,1250,{.forwards=false,.maxSpeed=127,.minSpeed=20,.earlyExitRange=2});
            chassis.moveToPoint(39,-48.5,1250,{.forwards=false,.maxSpeed=127,.minSpeed=0,.earlyExitRange=1});
            chassis.turnToHeading(90,650,{.maxSpeed=127,.minSpeed=0,.earlyExitRange=1});
            
            // chassis.moveToPoint(20,-50,1250,{.forwards=false,.maxSpeed=75,.minSpeed=10,.earlyExitRange=3});

            // chassis.moveToPose(25,-47.5,90,1500,{.forwards=false,.horizontalDrift=8,.lead=0.3,.maxSpeed=127,.minSpeed=0,.earlyExitRange=1});
            chassis.waitUntilDone();
            Misc::cdrift(-60,-60,450);
            Motor::intakeU.move(127);
            Misc::cdrift(-20,-20,500);
            Piston::loader.set_value(true);
            Misc::cdrift(-20,-20,800);
            Motor::intakeU.brake();
            chassis.moveToPoint(52.5,-49.5,1250,{.forwards=true,.maxSpeed=95,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntilDone();
            Misc::cdrift(35,35,350);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,590);

            chassis.moveToPoint(9,-12,1250,{.forwards=false,.maxSpeed=127,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntil(5);
            Piston::loader.set_value(false);
            chassis.waitUntilDone();
            // Piston::loader.set_value(false);
            // Misc::cdrift(-40,-40,150);
            Motor::intakeU.move(55);
            Piston::middle.set_value(true);
            Misc::cdrift(-30,-30,900);
            Misc::cdrift(20,85,350);
            Piston::middle.set_value(false);
            Motor::intakeU.brake();

            chassis.moveToPoint(20,22,1250,{.forwards=true,.maxSpeed=127,.minSpeed=10,.earlyExitRange=1});
            chassis.waitUntil(19);

            // chassis.waitUntilDone();

            //new
            Piston::loader.set_value(true);
            chassis.waitUntilDone();
            chassis.moveToPoint(54,42,200,{.forwards=true,.maxSpeed=127,.minSpeed=0,.earlyExitRange=3});
            // chassis.turnToPoint(56,41,400,{.maxSpeed=90,.minSpeed=10,.earlyExitRange=0});
            // chassis.moveToPoint(63,-45,400,{.forwards=true,.maxSpeed=127,.minSpeed=10,.earlyExitRange=1});
            chassis.moveToPose(60,49,90,1250,{.forwards=true,.horizontalDrift=7,.lead=0.54,.maxSpeed=127,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            Misc::cdrift(30,30,250);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,400);
            chassis.moveToPoint(20,49.5,950,{.forwards=false,.maxSpeed=90,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntilDone();
            Motor::intakeU.move(127);
            Misc::cdrift(-20,-20,1500);
            Motor::intakeU.brake();
            Piston::loader.set_value(false);
        }

        void safeAWP(){
            chassis.setPose(50,8,180);
            Motor::intakeF.move(127);
            Piston::hook.set_value(true);
            Misc::cdrift(50,50,500);
            // pros::delay(250);
            Misc::cdrift(-10,-10,120);
            Misc::cdrift(-20,-20,80);
            

            chassis.moveToPoint(48,46.5,1200,{.forwards=false,.maxSpeed=127,.minSpeed=0,.earlyExitRange=1.5});
            chassis.waitUntilDone();
            // chassis.turnToHeading(270,1200,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=1});
            // chassis.waitUntilDone();
            Piston::loader.set_value(true);
            pros::delay(100);
            chassis.turnToPoint(65,49.2,750,{.forwards=true,.maxSpeed=90,.minSpeed=0,.earlyExitRange=1.5});
            chassis.waitUntilDone();
            
            Misc::cdrift(45,45,500);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,450);

            chassis.moveToPoint(30,49.5,950,{.forwards=false,.maxSpeed=85,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntilDone();
            Motor::intakeF.move(-127); 
            Motor::intakeU.move(-127);
            pros::delay(40);
            Motor::intakeF.move(127); 
            Motor::intakeU.move(127);
            Misc::cdrift(-20,-20,500);
            Piston::loader.set_value(false);
            Misc::cdrift(-20,-20,600);
            Motor::intakeU.brake();
            Misc::cdrift(95,55,200);
            chassis.moveToPoint(28.2,26,1250,{.forwards=true,.maxSpeed=127,.minSpeed=10,.earlyExitRange=3});
            chassis.waitUntilDone();
            Misc::cdrift(-10,80,150);
            chassis.moveToPoint(27.2,-24,1150,{.forwards=true,.maxSpeed=127,.minSpeed=0,.earlyExitRange=1});
            chassis.waitUntil(17);
            Piston::loader.set_value(true);
            chassis.waitUntilDone();
            Piston::loader.set_value(false);


            chassis.moveToPoint(9,-5,750,{.forwards=false,.maxSpeed=80,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntilDone();
            Motor::intakeF.move(-127);
            Motor::intakeU.move(-127);
            pros::delay(20);
            Motor::intakeF.move(127);
            Motor::intakeU.move(55);
            Piston::middle.set_value(true);
            // Piston::loader.set_value(false);
            // Misc::cdrift(-40,-40,150);
            // Motor::intakeF.move(127);
            // Motor::intakeU.move(55);
            // Piston::middle.set_value(true);
            Misc::cdrift(-30,-30,150);
            Misc::cdrift(-10,-10,600);
            // Misc::cdrift(20,85,350);
            Piston::middle.set_value(false);
            Motor::intakeU.brake();


            chassis.moveToPoint(48,-45.5,1100,{.forwards=true,.maxSpeed=127,.minSpeed=0,.earlyExitRange=1.5});
            chassis.waitUntilDone();
            // chassis.turnToHeading(270,1200,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=1});
            // chassis.waitUntilDone();
            Piston::loader.set_value(true);
            pros::delay(100);
            chassis.turnToPoint(65,-46.2,700,{.forwards=true,.maxSpeed=90,.minSpeed=0,.earlyExitRange=2});
            chassis.waitUntilDone();
            Misc::cdrift(45,45,850);
            // Misc::cdrift(-20,-20,200);
            // Misc::cdrift(35,35,590);
            
            // Misc::cdrift(50,50,550);
            // Misc::cdrift(-20,-20,200);
            // Misc::cdrift(35,35,590);

            chassis.moveToPoint(30,-46.7,950,{.forwards=false,.maxSpeed=90,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntilDone();
            Motor::intakeF.move(-127); 
            Motor::intakeU.move(-127);
            pros::delay(40);
            Motor::intakeF.move(127); 
            Motor::intakeU.move(127);
            Misc::cdrift(-20,-20,500);
            Piston::loader.set_value(false);
            Misc::cdrift(-20,-20,500);
            // Motor::intakeU.brake();
        }

        void leftMiddle(){
            chassis.setPose(48,-15,270);
            Piston::hook.set_value(true);
            Motor::intakeF.move(127); 

            chassis.moveToPose(8.5,-46.5,180,1250,{.forwards=true,.horizontalDrift=11,.lead=0.44,.maxSpeed=127,.minSpeed=0,.earlyExitRange=1});
            chassis.waitUntilDone();
            
            chassis.moveToPoint(29,-36,1250,{.forwards=false,.maxSpeed=127,.minSpeed=20,.earlyExitRange=2});
            chassis.moveToPoint(39,-48.5,1250,{.forwards=false,.maxSpeed=127,.minSpeed=0,.earlyExitRange=1});
            chassis.turnToHeading(90,650,{.maxSpeed=127,.minSpeed=0,.earlyExitRange=1});
            
            // chassis.moveToPoint(20,-50,1250,{.forwards=false,.maxSpeed=75,.minSpeed=10,.earlyExitRange=3});

            // chassis.moveToPose(25,-47.5,90,1500,{.forwards=false,.horizontalDrift=8,.lead=0.3,.maxSpeed=127,.minSpeed=0,.earlyExitRange=1});
            chassis.waitUntilDone();
            Misc::cdrift(-60,-60,450);
            Motor::intakeU.move(127);
            Misc::cdrift(-20,-20,500);
            Piston::loader.set_value(true);
            Misc::cdrift(-20,-20,800);
            Motor::intakeU.brake();
            chassis.moveToPoint(52.5,-49.5,1250,{.forwards=true,.maxSpeed=95,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntilDone();
            Misc::cdrift(35,35,350);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,590);

            chassis.moveToPoint(9,-12,1250,{.forwards=false,.maxSpeed=127,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntil(5);
            Piston::loader.set_value(false);
            chassis.waitUntilDone();
            // Piston::loader.set_value(false);
            // Misc::cdrift(-40,-40,150);
            Motor::intakeU.move(55);
            Piston::middle.set_value(true);
            Misc::cdrift(-30,-30,900);
            Misc::cdrift(20,85,350);
            Piston::middle.set_value(false);
            Motor::intakeU.brake();
            
            chassis.moveToPoint(38,-25,1250,{.forwards=true,.maxSpeed=127,.minSpeed=10,.earlyExitRange=2});
            chassis.waitUntilDone();
            Piston::hook.set_value(false);
            chassis.turnToHeading(90,800,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=2});
            chassis.moveToPoint(14,-28,1750,{.forwards=false,.maxSpeed=85,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            Misc::cdrift(0,-15);
            chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

        }
    }

    namespace Qual {
        void leftB(){
            Template::left();
        }

        void rightB(){
            Template::right();
        }

        void soloB(){
            Template::solo();
        }

        void leftR(){
            Template::left();
        }

        void rightR(){
            Template::right();
        }

        void soloR(){
            Template::solo();
        }
    }

    namespace Elim {
        void left(){

        }

        void right(){

        }

        void solo(){

        }
    }

    namespace Skills {
        void main(){
            // From pov of red, left = 0;
            chassis.setPose(-50,17.5,0);
            Motor::intakeF.move(127);
            Piston::hook.set_value(true);
            chassis.moveToPoint(-48,46,1250,{.forwards=true,.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            // chassis.turnToHeading(270,1200,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=1});
            // chassis.waitUntilDone();
            Piston::loader.set_value(true);
            pros::delay(100);
            chassis.turnToPoint(-65,47,1250,{.forwards=true,.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            
            Misc::cdrift(35,35,700);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,800);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,800);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,800);

            // chassis.moveToPoint(-20,-49,1250,{.forwards=false,.maxSpeed=90,.minSpeed=0,.earlyExitRange=3});
            // chassis.waitUntilDone();
            // Motor::intakeU.move(127);
            // Misc::cdrift(-20,-20,2500);
            // Motor::intakeU.brake();
            // Piston::loader.set_value(false);

            chassis.moveToPoint(-42,64,1250,{.forwards=false,.maxSpeed=90,.minSpeed=10,.earlyExitRange=2});
            chassis.waitUntilDone();
            chassis.turnToHeading(270,800,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            Piston::loader.set_value(false);
            // Misc::reset2(-1);
            chassis.moveToPoint(30,64,1250,{.forwards=false,.maxSpeed=90,.minSpeed=0,.earlyExitRange=1});
            chassis.waitUntilDone();
            // chassis.turnToHeading(270,800,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            // chassis.waitUntilDone();
            // pros::delay(500);
            // Misc::resetB1();
            // pros::delay(300);
            // pros::delay(1000000000);
            chassis.moveToPoint(42,51,1250,{.forwards=false,.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            // pros::delay(1000000000);
            chassis.turnToHeading(90,800,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.moveToPoint(20,49.5,1250,{.forwards=false,.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            Motor::intakeF.move(-127);
            Motor::intakeU.move(-127);
            pros::delay(150);
            Motor::intakeF.move(127);
            Motor::intakeU.move(127);
            Misc::cdrift(-20,-20,1000);
            Piston::loader.set_value(true);
            Misc::cdrift(-20,-20,1500);
            Motor::intakeU.brake();

            chassis.moveToPoint(45,49,1250,{.forwards=true,.maxSpeed=95,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntilDone();
            Misc::cdrift(35,35,700);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,800);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,800);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,800);
            // Misc::cdrift(-20,-20,200);
            // Misc::cdrift(35,35,800);

            chassis.moveToPoint(25,49,1250,{.forwards=false,.maxSpeed=85,.minSpeed=0,.earlyExitRange=1});
            chassis.waitUntilDone();
            Motor::intakeF.move(-127);
            Motor::intakeU.move(-127);
            pros::delay(150);
            Motor::intakeF.move(127);
            Motor::intakeU.move(127);
            Misc::cdrift(-20,-20,1000);
            Piston::loader.set_value(false);
            Misc::cdrift(-20,-20,1500);
            Motor::intakeU.brake();

            Misc::cdrift(90,45,200);
            // chassis.moveToPoint(20,24,1500,{.forwards=true,.maxSpeed=70,.minSpeed=10,.earlyExitRange=3});
            // chassis.waitUntilDone();
            // Misc::cdrift(-10,80,150);
            // chassis.moveToPoint(19,-25,2500,{.forwards=true,.maxSpeed=55,.minSpeed=0,.earlyExitRange=1});
            // chassis.waitUntilDone();
            pros::delay(200);

            chassis.moveToPoint(17,26,1500,{.forwards=true,.maxSpeed=70,.minSpeed=10,.earlyExitRange=3});
            chassis.waitUntilDone();
            Misc::cdrift(-10,80,150);
            chassis.moveToPoint(17.5,-25,2500,{.forwards=true,.maxSpeed=55,.minSpeed=0,.earlyExitRange=1});
            chassis.waitUntilDone();
            pros::delay(200);
            // chassis.waitUntil(17);
            // Piston::loader.set_value(true);
            // chassis.waitUntilDone();
            // Piston::loader.set_value(false);


            chassis.moveToPoint(9,-13,750,{.forwards=false,.maxSpeed=90,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntilDone();
            Motor::intakeF.move(-127);
            Motor::intakeU.move(-127);
            pros::delay(150);
            Motor::intakeF.move(127);
            Motor::intakeU.move(55);
            Piston::middle.set_value(true);
            Misc::cdrift(-30,-30,2000);
            Piston::middle.set_value(false);
            Motor::intakeU.brake();


            chassis.moveToPoint(37,-45,1100,{.forwards=true,.maxSpeed=127,.minSpeed=0,.earlyExitRange=1});
            chassis.waitUntilDone();
            // chassis.turnToHeading(270,1200,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=1});
            // chassis.waitUntilDone();
            Piston::loader.set_value(true);
            pros::delay(100);
            chassis.turnToPoint(65,-45,700,{.forwards=true,.maxSpeed=90,.minSpeed=0,.earlyExitRange=2});
            chassis.waitUntilDone();
            
            Misc::cdrift(50,50,550);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,590);
            Misc::cdrift(50,50,550);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,590);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,590);

            chassis.moveToPoint(36,-62,1250,{.forwards=false,.maxSpeed=90,.minSpeed=10,.earlyExitRange=2});
            chassis.waitUntilDone();
            Piston::loader.set_value(false);
            chassis.turnToHeading(268,800,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            // Piston::loader.set_value(false);
            // Misc::reset2(-1);
            chassis.moveToPoint(-24,-63.5,1250,{.forwards=true,.maxSpeed=90,.minSpeed=10,.earlyExitRange=2});
            chassis.waitUntilDone();
            // pros::delay(500);
            // Misc::resetB2();
            // pros::delay(100);
            chassis.moveToPoint(-51,-49,1250,{.forwards=true,.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.turnToHeading(270,800,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.moveToPoint(-20,-49,1250,{.forwards=false,.maxSpeed=85,.minSpeed=0,.earlyExitRange=2});
            chassis.waitUntilDone();
            Motor::intakeF.move(-127);
            Motor::intakeU.move(-127);
            pros::delay(150);
            Motor::intakeF.move(127);
            Motor::intakeU.move(127);
            Misc::cdrift(-20,-20,1000);
            Piston::loader.set_value(true);
            Misc::cdrift(-20,-20,1500);
            Motor::intakeU.brake();

            chassis.moveToPoint(-55,-49,1500,{.forwards=true,.maxSpeed=70,.minSpeed=0,.earlyExitRange=3});
            chassis.waitUntilDone();
            Misc::cdrift(35,35,700);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,800);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,800);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,800);

            chassis.moveToPoint(-32,-49,1250,{.forwards=false,.maxSpeed=85,.minSpeed=0,.earlyExitRange=1});
            chassis.waitUntilDone();
            Motor::intakeF.move(-127);
            Motor::intakeU.move(-127);
            pros::delay(150);
            Motor::intakeF.move(127);
            Motor::intakeU.move(127);
            Misc::cdrift(-20,-20,1000);
            Piston::loader.set_value(false);
            Misc::cdrift(-20,-20,1500);
            Motor::intakeU.brake();
            Misc::cdrift(80,20,500);
            // chassis.moveToPoint(-48,-53,1250,{.forwards=true,.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});

            chassis.moveToPoint(-71,-28,1500,{.forwards=false,.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.turnToHeading(351,800,{.maxSpeed=90,.minSpeed=0,.earlyExitRange=0});
            chassis.waitUntilDone();
            // Misc::cdrift(65,65,2500);
            // Misc::park(65,65,2500);
            // Misc::park(65,65,2000);
            // Misc::cdrift(40,40,700);
            Motor::intakeF.move(-127);
            Misc::cdrift(30,33,1300);
            Piston::loader.set_value(true);
            Misc::cdrift(-20,-20,150);
            pros::delay(400);
            Misc::park(70,70,1000);
            Misc::cdrift(25,25);
        }
    }
}

// Auton selection
std::vector<std::pair<std::string, AutonFunc>> autonRoutines = {
    {"Default Auton", Auton::Template::rightFourRush},
    
    {"Left", Auton::Template::leftseven},
    {"Right", Auton::Template::rightFourRush},
    {"Rush AWP", Auton::Template::rushAWP},
    {"Solo", Auton::Template::safeAWP},

    {"Left Middle", Auton::Template::leftMiddle},

    {"Skills", Auton::Skills::main},
};

void autonSwitch() {
    if(TaskHandler::autonSelect) {    
        pros::delay(Misc::DELAY);
        if (Sensor::autonSwitch.get_new_press()) { autonState++; if (autonState == autonRoutines.size()) autonState = 0; }
    }
    pros::lcd::set_text(4, autonRoutines[autonState].first);
}
