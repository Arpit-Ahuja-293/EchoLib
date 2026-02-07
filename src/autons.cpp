#include "autons.h"
#include "misc.h"
#include "pros/rtos.hpp"
#include "taskhandler.h"
#include "distanceSense.h"
#include "jam.h"
#include "config.h"

int autonState = 0;

namespace Auton {
    int state = 0;
    
    namespace Test {
        void main() { 
            chassis.setPose(0, 0, 0);
            chassis.turnToHeading(90, 5000, {.maxSpeed = 90});
        }
    }

    namespace Template {
        void left(){
            chassis.setPose(0, 0, 0);
            //0, 32.88
            //90
            //9.37, 32.25, 89.3
            chassis.moveToPoint(0, 30.68, 1050, {.maxSpeed = 127});
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            ::intake.move(127);
            chassis.waitUntil(3);
            Piston::loader.set_value(true);
            // 90
            chassis.turnToHeading(-90, 650, {.maxSpeed = 90}); 
            // 7.62, 37.16
            chassis.moveToPose(-13.37, 30.65, -88.5, 850, {.lead = 0.1, .maxSpeed = 127});
            chassis.waitUntilDone();
            Misc::cdrift(30,30,80);
            //18.5, 28.54, 90
            chassis.moveToPose(18.5, 31.65, -90, 1050, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntil(12);
            Piston::loader.set_value(false);
            chassis.waitUntil(14);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
            ::intake.move(127);
            Misc::cdrift(-20,-20,1000);
            //7.80, 31.09, -92
            chassis.moveToPoint(7.8, 31.09, 800, {.maxSpeed = 127});
            //-220.66, 
            chassis.turnToHeading(-220.66, 650, {.maxSpeed = 90});
            //24.68, 6.99, 
            chassis.moveToPoint(24.68, 6.99, 1000, {.maxSpeed = 127});
            chassis.waitUntil(5);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntil(15);
            Piston::loader.set_value(true);
            //-319.84
            chassis.turnToHeading(-318.84, 700, {.maxSpeed = 90});
            chassis.waitUntil(20);
            Piston::loader.set_value(false);
            //38.68, 25.30, -324.34
            chassis.moveToPoint(38.68, 26.05, 1100, {.maxSpeed = 115});
            chassis.waitUntilDone();
            Piston::loader.set_value(true);
            //28.13, 1.78, 
            //-405.94, 
            //37.30, -5.18, -405.94
            chassis.moveToPoint(28.13, 1.78, 1000, {.forwards = false, .maxSpeed = 127});
            chassis.waitUntil(15);
            Piston::loader.set_value(false);
            chassis.turnToHeading(-409.23, 700, {.maxSpeed = 90});
            //36.90, -7.14, -409.34
            chassis.moveToPose(36.9, -7.14, -409.23, 900, {.forwards = false, .lead = 0.1, .maxSpeed = 127});
            chassis.waitUntilDone();
            Misc::cdrift(-40,-40,410);
            Piston::ballLock.set_value(true); // ball lock piston goes down
            Piston::middle.set_value(false);
            ::intake.move(110);
            pros::delay(350);
            ::intake.move(-127);
            pros::delay(100);
            ::intake.move(100);
        }

        void right(){
            chassis.setPose(0, 0, 0);
            // 0.64, 36.745
            chassis.moveToPoint(0, 34.345, 1250, {.maxSpeed = 127});
            ::intake.move(127);
            // 90
            chassis.turnToHeading(90, 700, {.maxSpeed = 90});
            chassis.waitUntilDone();
            Piston::loader.set_value(true);
            pros::delay(200);
            // 7.62, 37.16
            chassis.moveToPose(9.85, 37.26, 90, 800, {.lead = 0.1, .maxSpeed = 127});
            chassis.waitUntilDone();
            Misc::cdrift(45, 45, 500);
            Misc::cdrift(-20, -20, 200);
            Misc::cdrift(45, 45, 300);
            Misc::cdrift(-20, -20, 200);
            chassis.moveToPose(-24.20, 38.14, 90, 1250, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true);
            pros::delay(850);
            //-8.91, 39.50
            chassis.moveToPoint(-7, 38.14, 1250, {.maxSpeed = 127});
            chassis.waitUntilDone();
            chassis.turnToHeading(180, 800, {.maxSpeed = 90});
            chassis.waitUntilDone();
            Piston::loader.set_value(false);
            //-7.08 11.66, 180
            chassis.moveToPose(-7, 0, 180, 1250, {.maxSpeed = 120});
            chassis.waitUntilDone();
            ::intake.move(127);
            Piston::ballLock.set_value(false);
            //-21.39 4.57 0
            chassis.swingToHeading(-35, DriveSide::RIGHT, 1000, {.maxSpeed = 70, .minSpeed = 10, .earlyExitRange = 2});
            chassis.waitUntilDone();
            Misc::cdrift(45, 45, 100);
            pros::delay(300);
            //-28.93 11.325 302
            //   chassis.swingToHeading(-80, DriveSide::LEFT, 1000, {.maxSpeed = 30, .minSpeed = 10, .earlyExitRange = 2});
            //   chassis.waitUntilDone();
            //-25.01 11.28 313.75
            chassis.moveToPose(-25.01, 11.28, 315.75, 1250, {.maxSpeed = 120});
            chassis.waitUntilDone();
            pros::delay(150);
            chassis.turnToHeading(-135, 800, {.maxSpeed = 90});
            chassis.waitUntilDone();
            //-32.67 0.05 226.41
            chassis.moveToPose(-35.45, -4, 223.8, 1250, {.maxSpeed = 127});
            chassis.waitUntil(13);
            ::intake.move(-47);
        }

        void solo(){          
            chassis.setPose(0, 0, 0);
            //0, 32.88
            //90
            //9.37, 32.25, 89.3
            chassis.moveToPoint(0, 31.18, 1050, {.maxSpeed = 127});
            ::intake.move(127);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntil(3);
            Piston::loader.set_value(true);
            // 90
            chassis.turnToHeading(90, 650, {.maxSpeed = 90});
            
            // 7.62, 37.16
            chassis.moveToPose(13.97, 30.65, 88.5, 700, {.lead = 0.1, .maxSpeed = 110});
            chassis.waitUntilDone();
            Misc::cdrift(30,30,200);
            //-18.5, 28.54, 90
            chassis.moveToPose(-18.5, 31.35, 90, 1050, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntil(10);
            Piston::loader.set_value(false);
            chassis.waitUntil(12);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
            ::intake.move(127);
            //184
            chassis.swingToHeading(184, DriveSide::LEFT, 1000, {.maxSpeed = 70});
            chassis.waitUntil(10);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            //-17.54, 11.95, 185.65
            chassis.moveToPoint(-17.54, 9.95, 800, {.maxSpeed = 127});
            chassis.turnToHeading(180, 300, {.maxSpeed = 90});
            //-14.11, -32.87, 181
            chassis.moveToPoint(-17.32, -32.87, 1250, {.maxSpeed = 127});
            // //135.91
            chassis.turnToHeading(135.44, 550, {.maxSpeed = 90});
            //-29.88, -20.73, 131.3
            //-29.97, -22.23, 138.18
            //-28.387, -19.91, 134
            chassis.moveToPose(-28.387, -19.91, 134.18, 1000, {.forwards = false, .lead= 0.1, .maxSpeed = 127});
            chassis.waitUntil(3);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true); // ball lock piston goes down
            Piston::middle.set_value(false);
            ::intake.move(113);
            pros::delay(350);
            ::intake.move(-127);
            pros::delay(100);
            ::intake.move(109);
            pros::delay(500);
            // 6.469, -59.72, 135.099 
            chassis.moveToPoint(6.469, -57.72, 1350, {.maxSpeed = 127});
            chassis.waitUntil(0.5);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntil(5);
            Piston::loader.set_value(true);
            //90
            chassis.turnToHeading(90, 600, {.maxSpeed = 90});
            //17.32, -60.95, 90.8
            chassis.moveToPose(22.32, -57.75, 88.5, 850, {.lead = 0.1, .maxSpeed = 127});
            chassis.waitUntilDone();
            pros::delay(175);
            chassis.moveToPose(-15.5, -58.23, 90, 1000, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntil(12);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
            ::intake.move(127);
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
            pros::delay(40);
            Motor::intakeF.move(127); 
            Misc::cdrift(-20,-20,1500);
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
            chassis.setPose(0, 0, 0);
            //0, 32.88
            //90
            //9.37, 32.25, 89.3
            chassis.moveToPoint(0, 31.68, 1050, {.maxSpeed = 127});
            ::intake.move(127);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntil(3);
            Piston::loader.set_value(true);
            // 90
            chassis.turnToHeading(90, 650, {.maxSpeed = 90});
            
            // 7.62, 37.16
            chassis.moveToPose(17.37, 31.65, 88.5, 850, {.lead = 0.1, .maxSpeed = 127});
            chassis.waitUntilDone();
            pros::delay(175);
            //-18.5, 28.54, 90
            chassis.moveToPose(-18.5, 31.85, 90, 1050, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntil(10);
            Piston::loader.set_value(false);
            chassis.waitUntil(12);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
            ::intake.move(127);
            pros::delay(1000);
            //184
            //3, 21.32, 115, 86
            chassis.moveToPose(3, 22.25, 115, 1000, {.lead = 0.3,.maxSpeed = 127});
            chassis.turnToHeading(90, 375, {.maxSpeed = 90});
            //-36.96, 20.17, 86.59
            chassis.moveToPoint(-34.75, 22.22, 1000, {.forwards = false, .maxSpeed = 127});
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
            Misc::cdrift(-20,-20,500);
            Piston::loader.set_value(true);
            Misc::cdrift(-20,-20,800);
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
            Piston::middle.set_value(true);
            Misc::cdrift(-30,-30,900);
            Misc::cdrift(20,85,350);
            Piston::middle.set_value(false);

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
            Misc::cdrift(-20,-20,1500);
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
            pros::delay(40);
            Motor::intakeF.move(127); 
            Misc::cdrift(-20,-20,500);
            Piston::loader.set_value(false);
            Misc::cdrift(-20,-20,600);
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
            pros::delay(20);
            Motor::intakeF.move(127);
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
            pros::delay(40);
            Motor::intakeF.move(127); 
            Misc::cdrift(-20,-20,500);
            Piston::loader.set_value(false);
            Misc::cdrift(-20,-20,500);
            // Motor::intakeU.brake();
        }

        void leftMiddle(){
             chassis.setPose(0,0,0);
            //0.64, 36.745
            chassis.moveToPoint(0, 34.345, 1250, {.maxSpeed=127});
            ::intake.move(127);
            //-90
            chassis.turnToHeading(-90,800,{.maxSpeed=90});
            //-9.83, 35.81
            chassis.waitUntilDone();
            Piston::loader.set_value(true);
            pros::delay(200);
            //7.62, 37.16
            chassis.moveToPose(-11.83, 34.08, -90, 1000, {.lead = 0.02,.maxSpeed=120});
            chassis.waitUntilDone();
            Misc::cdrift(45,45,250);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,150);
            //16.38, 34.06, -90.55
            chassis.moveToPose(24.20, 34.06, -90, 1250, {.forwards = false, .lead = 0.1, .maxSpeed = 110});
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true);
            pros::delay(1000);
            chassis.moveToPoint(14.2, 34.06, 800, {.maxSpeed=127});
            Piston::loader.set_value(false);
            //15.92, 16.53, -235.22
            chassis.moveToPose(15.92, 16.53, -235.22, 1250, {.lead = 0.6, .maxSpeed=127});
            chassis.waitUntil(5);
            Piston::ballLock.set_value(false);
            chassis.waitUntil(10);
            ::intake.move(127);
            //38.05, -3.18, -227.0
            chassis.moveToPoint(39.05, -4.18, 1500, {.maxSpeed=17});
            chassis.swingToHeading(-263, DriveSide::LEFT, 1000, {.maxSpeed=70, .minSpeed=10, .earlyExitRange=2});
            chassis.swingToHeading(-225, DriveSide::RIGHT, 1000, {.maxSpeed=70, .minSpeed=10, .earlyExitRange=2});
            chassis.moveToPoint(38.55, -3.88, 2500, {.maxSpeed=60});
            chassis.waitUntil(2.5);
            Piston::loader.set_value(true);
            chassis.waitUntil(6);
            Piston::middle.set_value(true);
            chassis.waitUntil(15);
            Piston::loader.set_value(false);
            chassis.waitUntilDone();
            pros::delay(200);
            ::intake.move(70);
            pros::delay(1500);

        }

        void rightSevenRush(){
            chassis.setPose(0,0,10);
            //4.58, 24.60, 9.55
            chassis.moveToPoint(4.58, 22.60, 900, {.maxSpeed=127, .minSpeed=10, .earlyExitRange=1});
            ::intake.move(127);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntil(12);
            Piston::loader.set_value(true);
            //138.03
            chassis.turnToHeading(138.03, 600, {.maxSpeed=90});
            //32.14, -10.75, 180.84
            chassis.moveToPose(31.8, -10.75, 180.84, 1250, {.lead = 0.45, .maxSpeed = 85});
            chassis.waitUntilDone();
            Misc::cdrift(30,30,575);
            pros::delay(200);
            //30.77, 18.70, 180
            chassis.moveToPose(30.57, 18.80, 180, 1050, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntil(12);
            Piston::loader.set_value(false);
            chassis.waitUntil(14);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
            ::intake.move(127);
            Misc::cdrift(-20,-20,1400);
            //18.0, 8.63, 
            chassis.moveToPoint(22.25, 8.63, 1000, {.maxSpeed=127, .minSpeed=10, .earlyExitRange=1});
            //180
            chassis.turnToHeading(180, 700, {.maxSpeed=90, .minSpeed=20, .earlyExitRange=2});
            //19.14, 39.81, 180
            chassis.moveToPoint(23.34, 37, 1000, {.forwards = false, .maxSpeed=127});
            chassis.waitUntil(10);
            ::intake.move(0);
            // chassis.moveToPoint(30.712, 7.538, 700, {.maxSpeed=127});
            // //125
            // chassis.turnToHeading(125,700,{.maxSpeed=127,.minSpeed=20,.earlyExitRange=3});
            // chassis.moveToPose(24.86,34.77,180,1500,{.forwards=false,.horizontalDrift=8,.lead=0.45,.maxSpeed=80,.minSpeed=0,.earlyExitRange=0}); 
            chassis.waitUntilDone();
            Misc::cdrift(0,15);
            chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
            //24.86, 20.10, 180
        }

        void rightRush(){
            chassis.setPose(0,0,10);
            //4.58, 24.60, 9.55
            chassis.moveToPoint(4.58, 22.60, 900, {.maxSpeed=127, .minSpeed=10, .earlyExitRange=1});
            ::intake.move(127);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntil(12);
            Piston::loader.set_value(true);
            //29.51, 10.32, -62.04
            chassis.moveToPose(30.81, 10.32, -62.04, 1250, {.forwards = false, .lead = 0.4, .maxSpeed = 100, .minSpeed=10, .earlyExitRange=1});
            chassis.turnToHeading(180, 700, {.maxSpeed=90, .minSpeed=20, .earlyExitRange=2});
            chassis.moveToPoint(29.89, 19.80, 800, {.forwards = false,.maxSpeed = 127});
            chassis.waitUntil(4);
            Piston::loader.set_value(false);
            chassis.waitUntil(5);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
            ::intake.move(127);
            Misc::cdrift(-20,-20,1000);
            //18.0, 8.63, 
            chassis.moveToPoint(21, 8.63, 1000, {.maxSpeed=127, .minSpeed=10, .earlyExitRange=1});
            //180
            chassis.turnToHeading(180, 700, {.maxSpeed=90, .minSpeed=20, .earlyExitRange=2});
            //19.14, 39.81, 180
            chassis.moveToPoint(22.29, 37, 1000, {.forwards = false, .maxSpeed=127});
            chassis.waitUntil(10);
            ::intake.move(0);
            chassis.waitUntilDone();
            Misc::cdrift(0,15);
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
            chassis.setPose(0,0,0);
            // Your skills auton code here
            chassis.moveToPoint(0, 34.345, 1250, {.maxSpeed=127});
            pros::Task intakeUnjammer(intakeUnjam);
            ::intake.move(127);
            //90
            chassis.turnToHeading(90,800,{.maxSpeed=90});
            intakeUnjammer.suspend();
            chassis.waitUntilDone();
            Piston::loader.set_value(true);
            pros::delay(150);
            //7.62, 37.16
            chassis.moveToPose(10.35, 37.56, 90, 1000, {.lead = 0.1, .maxSpeed=120});
            chassis.waitUntilDone();
            Misc::cdrift(45,45,500);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,800);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,500);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,400);
            chassis.moveToPoint(3.15, 37.56, 1000, {.forwards = false, .maxSpeed=127});
            ::intake.move(0);
            //move back
            //-13.23, 51.35, 124.67
            chassis.moveToPose(-13.23, 53.0, 124.67, 1250, {.forwards = false, .lead = 0.3, .maxSpeed = 127, .minSpeed = 20, .earlyExitRange = 2});
            chassis.turnToHeading(90, 700, {.maxSpeed=90, .minSpeed=10, .earlyExitRange=2});
            //go to other side
            //-73.26, 50.20, 90
            chassis.moveToPoint(-73.26, 49.85, 2500, {.forwards = false, .maxSpeed=127, .minSpeed=20, .earlyExitRange=2});
            chassis.waitUntil(20);
            Piston::loader.set_value(false);
            //-87.08, 35.83, 0
            chassis.moveToPoint(-87.08, 35.83, 1000, {.forwards = false, .maxSpeed=127});
            chassis.turnToHeading(-90, 800, {.maxSpeed=90});
            chassis.waitUntilDone();
            if(Sensor::d_right.get_confidence() >= 10){
                chassis.setPose(chassis.getPose().x, 54.55-(getRightDist()) * fabs(sin((chassis.getPose(true).theta))), chassis.getPose().theta);
            }
            //-80.28, 34.03, -90
            chassis.moveToPose(-74.45, 35.33, -90, 1300, {.forwards = false, .lead = 0.05,.maxSpeed=85});
            intakeUnjammer.resume();
            chassis.waitUntil(1);
            ::intake.move(127);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true);
            pros::delay(3000);
            //hard reset
            //35.45, 19.1
            //-107.37, 35.26, -91.0
            chassis.moveToPose(-107.37, 34.96, -90, 1250, {.lead = 0.05, .maxSpeed = 115});
            intakeUnjammer.suspend();
            chassis.waitUntil(2.5);
            Piston::ballLock.set_value(false);
            chassis.waitUntil(3);
            Piston::loader.set_value(true);
            chassis.waitUntilDone();
            Misc::cdrift(45,45,500);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,800);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,500);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,400);
            chassis.moveToPose(-74.45, 35.53, -90, 2500, {.forwards = false, .lead = 0.05,.maxSpeed=45});
            intakeUnjammer.resume();
            chassis.waitUntil(10);
            Piston::loader.set_value(false);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true);
            pros::delay(3000);
            if(Sensor::d_right.get_confidence() >= 10){
                chassis.setPose(chassis.getPose().x, 54.55-(getRightDist()) * fabs(sin((chassis.getPose(true).theta))), chassis.getPose().theta);
            }
            //move forward
            //-85.35, 35.88, 
            chassis.moveToPoint(-88.35, 35.88, 800, {.maxSpeed=127, .minSpeed=10, .earlyExitRange=1});
            //swing to 180
            chassis.swingToHeading(-182, DriveSide::LEFT, 800, {.maxSpeed=90, .minSpeed=20, .earlyExitRange=2});
            intakeUnjammer.suspend();
            //move to other side
            //-89.72, -58.98, -180
            chassis.moveToPoint(-91.42, -59.98, 2500, {.maxSpeed=127});
            chassis.turnToHeading(-90, 800, {.maxSpeed=90});
            Piston::ballLock.set_value(false);
            chassis.waitUntilDone();
            //-102.3, -62.77
            //18.6, -57.3
            if(Sensor::d_left.get_confidence() >= 10){
                chassis.setPose(chassis.getPose().x, -75.98+(getLeftDist()) * fabs(sin((chassis.getPose(true).theta))), chassis.getPose().theta);
            }
            Piston::loader.set_value(true);
            pros::delay(200);
            chassis.moveToPose(-102.3, -57.3, -90, 1000, {.lead = 0.1, .maxSpeed=120});
            chassis.waitUntilDone();
            Misc::cdrift(45,45,500);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,800);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,500);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,400);
            chassis.moveToPoint(-94, -58.3, 1000, {.forwards = false, .maxSpeed=127});
            ::intake.move(0);
            //-78, -68.11, -59.91
            chassis.moveToPose(-78, -69.91, -59.91, 1250, {.forwards = false, .lead = 0.3, .maxSpeed = 127, .minSpeed = 20, .earlyExitRange = 2});
            chassis.turnToHeading(-92, 700, {.maxSpeed=90, .minSpeed=10, .earlyExitRange=2});
            //-18.96, -67.41
            chassis.moveToPoint(-19.96, -67.41, 2500, {.forwards = false, .maxSpeed=127});
            chassis.waitUntil(5);
            ::intake.move(0);
            chassis.waitUntil(20);
            Piston::loader.set_value(false);
            //-3.38, -56.28
            chassis.moveToPoint(-7.38, -54.98, 1000, {.forwards = false, .maxSpeed=127});
            //-20.24
            chassis.turnToHeading(90, 800, {.maxSpeed=90});
            chassis.waitUntilDone();
            if(Sensor::d_right.get_confidence() >= 10){
                chassis.setPose(chassis.getPose().x, -78.59+(getRightDist()) * fabs(sin((chassis.getPose(true).theta))), chassis.getPose().theta);
            }
            //-14.40, -53.80, 90
            chassis.moveToPose(-20.24, -59.87, 90, 1300, {.forwards = false, .lead = 0.05,.maxSpeed=85});
            intakeUnjammer.resume();
            chassis.waitUntil(1);
            ::intake.move(127);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true);
            pros::delay(3000);
            //-16.7, -53.1
            //-59.7
            //8.76, -58.96
            chassis.moveToPose(9.76, -58.8, 90, 1250, {.lead = 0.05, .maxSpeed = 115});
            intakeUnjammer.suspend();
            chassis.waitUntil(2.5);
            Piston::ballLock.set_value(false);
            chassis.waitUntil(3);
            Piston::loader.set_value(true);
            chassis.waitUntilDone();
            Misc::cdrift(45,45,500);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,800);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(45,45,500);
            Misc::cdrift(-20,-20,200);
            Misc::cdrift(35,35,400);
            chassis.moveToPose(-20.24, -60, 90, 2500, {.forwards = false, .lead = 0.05,.maxSpeed=45});
            intakeUnjammer.resume();
            chassis.waitUntil(10);
            Piston::loader.set_value(false);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true);
            pros::delay(3000);
            if(Sensor::d_right.get_confidence() >= 10){
                chassis.setPose(chassis.getPose().x, -78.59+(getRightDist()) * fabs(sin((chassis.getPose(true).theta))), chassis.getPose().theta);
            }
            //16.66, -31.09
            chassis.moveToPose(17.26, -28.49, 0, 1250, {.lead = 0.3, .maxSpeed = 127});
            intakeUnjammer.suspend();
            chassis.waitUntilDone();
            Piston::loader.set_value(true);
            Misc::cdrift(120,120,1100);
            Piston::loader.set_value(false);
        }
    }
}

// Auton selection
std::vector<std::pair<std::string, AutonFunc>> autonRoutines = {
    {"Default Auton", Auton::Template::solo},
    {"Solo AWP", Auton::Template::solo},
    {"Right 4 Rush", Auton::Template::rightFourRush},
    {"Left 9 Split", Auton::Template::left},
    {"Left 7 Split", Auton::Template::leftMiddle},
    {"Left 4 Rush", Auton::Template::left},

    {"Skills", Auton::Skills::main},
};

void autonSwitch() {
    if(TaskHandler::autonSelect) {    
        pros::delay(Misc::DELAY);
        if (Sensor::autonSwitch.get_new_press()) { autonState++; if (autonState == autonRoutines.size()) autonState = 0; }
    }
    pros::lcd::set_text(4, autonRoutines[autonState].first);
}
