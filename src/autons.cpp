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
            chassis.setPose(0,0,0);
            //chassis.turnToHeading(0, 1000, {.maxSpeed = 90}); 
            chassis.moveToPoint(0, 13.548, 2500, {.maxSpeed = 90});
            chassis.turnToHeading(90, 800, {.maxSpeed = 90});
            chassis.moveToPoint(61.44, 13.899, 4500, {.maxSpeed = 60});
            chassis.turnToHeading(130, 650, {.maxSpeed = 90});
            chassis.moveToPoint(78, -5.368, 2500, {.maxSpeed = 60, .minSpeed = 15, .earlyExitRange = 1.25});
            chassis.swingToHeading(60, DriveSide::LEFT, 850, {.maxSpeed = 70});
            //going to top
            chassis.moveToPoint(122, 12.981, 2500, {.maxSpeed = 60});
            chassis.turnToHeading(0, 800, {.maxSpeed = 90});
            chassis.moveToPoint(122, 44.709, 3000, {.maxSpeed = 60});
            chassis.turnToHeading(-90, 800, {.maxSpeed = 90});
            chassis.moveToPoint(94.405, 44.925, 3000, {.maxSpeed = 60});
            chassis.turnToHeading(180, 800, {.maxSpeed = 90});
            chassis.moveToPoint(95.405, -5.196, 4500, {.maxSpeed = 60});
            chassis.swingToHeading(-90, DriveSide::RIGHT, 1000, {.maxSpeed = 60});
            //going to finish
            chassis.moveToPoint(74.204, -5.164, 2500, {.maxSpeed = 60});
            chassis.turnToHeading(-50, 400, {.maxSpeed = 90});
            chassis.moveToPoint(40.239, 17, 1250, {.maxSpeed = 127});
            chassis.swingToHeading(-110, DriveSide::LEFT, 700, {.maxSpeed = 127});
            chassis.moveToPose(-5.04, -1, -110, 5000, {.lead = 0.1,.maxSpeed = 127});
        }
    }
    //middle is long long is mid
    namespace Template {
        void left(){
            chassis.setPose(0, 0, 0);
            //0, 32.88
            //90
            //9.37, 32.25, 89.3
            chassis.moveToPoint(0, 32.44, 1050, {.maxSpeed = 127});
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            ::intake.move(127);
            chassis.waitUntil(3);
            Piston::loader.set_value(true);
            // 90
            chassis.turnToHeading(-90, 650, {.maxSpeed = 90}); 
            // 7.62, 37.16
            chassis.moveToPose(-14.07, 32.44, -89, 850, {.lead = 0.1, .maxSpeed = 127});
            chassis.waitUntilDone();
            Misc::cdrift(45,45,400);
            //18.5, 28.54, 90
            chassis.moveToPose(18.5, 33.62, -90, 1050, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntil(12);
            Piston::loader.set_value(false);
            chassis.waitUntil(14);
            ::intake.move(0);
            chassis.waitUntilDone();
            //long
            Piston::ballLock.set_value(true); // ball lock piston goes down
            Piston::middle.set_value(false);
            ::intake.move(127);
            Misc::cdrift(-20,-20,1000);
            chassis.turnToHeading(-190, 1000, {.maxSpeed = 127});
            chassis.waitUntil(10);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.moveToPoint(15.09, 12.52, 800, {.maxSpeed = 127});
            chassis.waitUntil(5);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntil(13);
            Piston::loader.set_value(true);
            //-319.84
            chassis.turnToHeading(-321.88, 700, {.maxSpeed = 90});
            chassis.waitUntil(20);
            Piston::loader.set_value(false);
            // //38.68, 25.30, -324.34
            chassis.moveToPoint(31.5, 32.16, 1100, {.maxSpeed = 115});
            chassis.waitUntilDone();
            Piston::loader.set_value(true);
            chassis.moveToPoint(17.49, 12.5, 1000, {.forwards = false, .maxSpeed = 127});
            chassis.waitUntil(15);
            Piston::loader.set_value(false);
            chassis.turnToHeading(-405.08, 700, {.maxSpeed = 90});
            chassis.moveToPose(27.87, -0.32, -409, 900, {.forwards = false, .lead = 0.1, .maxSpeed = 127});
            chassis.waitUntilDone();
            Misc::cdrift(-40,-40,450);
            //mid
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
            ::intake.move(70);
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
            chassis.setPose(0, 0, -90);
            //36.92, 0, -90
            chassis.moveToPoint(34.75, 0, 1050, {.forwards = false, .maxSpeed = 127});
            ::intake.move(127);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            // 90
            chassis.waitUntil(3);
            Piston::loader.set_value(true);
            chassis.turnToHeading(-180, 500, {.maxSpeed = 127});
            //35, -11, -180
            chassis.moveToPose(35, -13, -180, 700, {.lead = 0.1, .maxSpeed = 110});
            chassis.waitUntilDone();
            Misc::cdrift(35,35,350);
            //36.19l 15.95, -180
            chassis.moveToPose(36.191, 18, -180, 1050, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntil(10);
            Piston::loader.set_value(false);
            chassis.waitUntil(12);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true); // ball lock piston goes down
            Piston::middle.set_value(false);
            ::intake.move(127);
            Misc::cdrift(-20,-20,750);
            //-76.76
            chassis.turnToHeading(-80, 750, {.maxSpeed = 95});
            chassis.waitUntil(10);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            //15.6, 17.32, -64.76
            chassis.moveToPoint(15.6, 17.32, 800, {.maxSpeed = 127});
            //-29.73, 18.28, -99.2
            chassis.moveToPoint(-29.73, 17.88, 1050, {.maxSpeed = 127});
            //-150
            chassis.turnToHeading(-125, 450, {.maxSpeed = 90});
            //-54.93, -1.35, -127
            chassis.moveToPoint(-54.93, -1.35, 800, {.maxSpeed = 127});
            //-180
            chassis.turnToHeading(-180, 375, {.maxSpeed = 127});
            //-55.17, 8.75
            chassis.moveToPose(-54.97, 10, -180, 750, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntil(5);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true); // ball lock piston goes down
            Piston::middle.set_value(false);
            ::intake.move(127);
            Misc::cdrift(-20,-20,50);
            Piston::loader.set_value(true);
            Misc::cdrift(-20,-20,1000);
            //-53.57, -20.99, -180.86
            chassis.moveToPose(-53.57, -21.99, -180.86, 1000, {.lead = 0.1, .maxSpeed = 85});
            chassis.waitUntil(3);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntilDone();
            Misc::cdrift(35,35,200);
            //-54.01, -13.11, -180
            chassis.moveToPoint(-53.85, -13.87, 650, {.forwards = false, .maxSpeed = 127});
            //-136.54
            chassis.turnToHeading(-136.54, 550, {.maxSpeed = 90});
            //-16.58, 26.21, -138.45
            chassis.moveToPose(-16.58, 26.21, -138.45, 1050, {.forwards = false, .lead= 0.1, .maxSpeed = 127});
            chassis.waitUntil(10);
            ::intake.move(0);
            chassis.waitUntilDone();
            Misc::cdrift(-45,-45,200);
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
            ::intake.move(105);  
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
            chassis.moveToPose(31.2, -10.87, 180.84, 1250, {.lead = 0.45, .maxSpeed = 85});
            chassis.waitUntilDone();
            Misc::cdrift(30,30,600);
            pros::delay(175);
            //30.77, 18.70, 180
            chassis.moveToPose(30.27, 18.80, 180, 1050, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntil(12);
            Piston::loader.set_value(false);
            chassis.waitUntil(14);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true); // ball lock piston goes down
            Piston::middle.set_value(false);
            ::intake.move(127);
            Misc::cdrift(-20,-20,1400);
            //18.0, 8.63, 
            chassis.moveToPoint(21.25, 8.63, 1000, {.maxSpeed=127, .minSpeed=10, .earlyExitRange=1});
            //180
            chassis.turnToHeading(180, 700, {.maxSpeed=90, .minSpeed=20, .earlyExitRange=2});
            //19.14, 39.81, 180
            chassis.moveToPoint(22.34, 37, 1000, {.forwards = false, .maxSpeed=127});
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
            chassis.setPose(0,0,-33.8);
            //0, 19.88, 
            chassis.moveToPoint(-13.7, 20, 800, {.maxSpeed=127});
            ::intake.move(127);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntil(17);
            Piston::loader.set_value(true);
            chassis.turnToHeading(-139.25, 600, {.maxSpeed=90});
            chassis.moveToPose(0.52, 38, -138.6, 950, {.forwards = false, .lead= 0.1, .maxSpeed = 127});
            chassis.waitUntil(3);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
            ::intake.move(75);  
            pros::delay(400);
            //-38.63, 5.33, -178.45
            chassis.moveToPoint(-38.63, 5.33, 1250, {.maxSpeed = 127});
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.turnToHeading(-178.45, 400, {.maxSpeed = 127});
            //-38.96, 15.00, -179.7
            chassis.moveToPose(-38.96, 15, -179.7, 750, {.forwards = false, .lead = 0.1, .maxSpeed = 95});
            chassis.waitUntil(5);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true); // ball lock piston goes down
            Piston::middle.set_value(false);
            ::intake.move(127);
            Misc::cdrift(-20,-20,50);
            Piston::loader.set_value(true);
            Misc::cdrift(-20,-20,700);
            //-40.40, 15.04, -180
            //16.96
            if(Sensor::d_right.get_confidence() >= 10){
                chassis.setPose(-57.36+(getRightDist()) * fabs(cos((chassis.getPose(true).theta))), chassis.getPose().y, chassis.getPose().theta);
            }
            // pros::delay(2000);
            //17.3, 67, 63.9, (17.1, 47.4, 64)
            //0.6
            //-38.88, 12.89, -181.78
            chassis.moveToPose(-37.68, -12.89, -180.86, 1000, {.lead = 0.1, .maxSpeed = 85});
            chassis.waitUntil(3);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntil(5);
            Piston::hook.set_value(true);
            chassis.waitUntilDone();
            Misc::cdrift(45,45,1400);
            //-49.91, 5.26, -223.13
            chassis.moveToPoint(-52, 5.26, 900, {.forwards = false, .maxSpeed = 127});
            chassis.waitUntil(6);
            Piston::loader.set_value(false);
            chassis.waitUntilDone();
            chassis.turnToHeading(-180, 500, {.maxSpeed = 90});
            //-52.71, 82.46, -181.82
            chassis.moveToPoint(-52, 78.46, 1700, {.forwards = false, .maxSpeed = 80});
            chassis.waitUntilDone();
            Misc::distanceResetBackRight(-57.6, 113.48);
            pros::delay(350);
            //
            chassis.turnToHeading(90, 700, {.maxSpeed = 90});
            //-43.45, 86.49, -268.31
            //-42.35, 96.67
            chassis.moveToPoint(-40.25, 86.67, 800, {.maxSpeed = 127});
            // // //0
            chassis.turnToHeading(0, 500, {.maxSpeed = 127});
            // //-45.89, 75.07, -360, 
            chassis.moveToPose(-40, 72.01, 0, 1000, {.forwards = false, .lead = 0.1, .maxSpeed = 105});
            chassis.waitUntil(3);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true); 
            Piston::middle.set_value(false);
            ::intake.move(127);
            Misc::cdrift(-20,-20,50);
            Piston::loader.set_value(true);
            Misc::cdrift(-20,-20,1400);
            //-40.64, 103.89, 1.19
            chassis.moveToPose(-41.5, 103.89, 0.19, 1000, {.lead = 0.1, .maxSpeed = 85});
            chassis.waitUntil(3);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntilDone();
            Misc::cdrift(45,45,1400);
            //-41.90, 76.21, 0
            chassis.moveToPose(-40.3, 71.21, 0, 1000, {.forwards = false, .lead = 0.1, .maxSpeed = 105});
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true); // ball lock piston goes down
            Piston::middle.set_value(false);
            Misc::cdrift(-20,-20,50);
            Piston::loader.set_value(false);
            Misc::cdrift(-20,-20,1400);
            //-40.40, 15.04, -180
            //16.96
            if(Sensor::d_left.get_confidence() >= 10){
                chassis.setPose(-57.36+(getLeftDist()) * fabs(cos((chassis.getPose(true).theta))), chassis.getPose().y, chassis.getPose().theta);
            }
            //-14.27, 105.79, 90
            chassis.moveToPose(-14.4, 111.5, 87, 1250, {.lead = 0.4, .maxSpeed = 127});
            chassis.waitUntil(3);
            ::intake.move(127);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntilDone();
            Piston::park.set_value(true);
            pros::delay(300);
            Misc::cdrift(70, 70);
            Sensor::o_crossed.set_led_pwm(100);  // max brightness for reliable blue/tile detection
            Misc::runFloorOpticalSeq(
                []() { return Misc::optical_is_floor_blue(Sensor::o_crossed); },
                []() { return Misc::optical_is_floor_tile(Sensor::o_crossed); },
                50, 50);
            Misc::cdrift(45,45,450);
            //0
            chassis.turnToHeading(0, 500, {.maxSpeed = 127});
            chassis.waitUntilDone();
            Misc::cdrift(60,60,800);
            chassis.setPose(chassis.getPose().x, chassis.getPose().y, 0);
            Misc::cdrift(60,60,200);
            Misc::cdrift(-60, -60, 50);
            Piston::park.set_value(false);
            Misc::cdrift(-60, -60, 155);
            pros::delay(50);
            //70.95, 113.92
            Misc::distanceResetFrontRight(70.95, 113.92);
            pros::delay(400);
            //36.18, 96.54, 0
            chassis.moveToPoint(36.04, 80, 800, {.forwards = false, .maxSpeed = 127});
            // //42.38
            chassis.turnToHeading(41.94, 500, {.maxSpeed = 90});
            // //14.54, 72.63, 40.95
            chassis.moveToPose(15.08, 58.1, 41.50, 1000, {.forwards = false, .lead = 0.1, .maxSpeed = 127});
            chassis.waitUntil(3);
            ::intake.move(0);
            chassis.waitUntilDone();
            Misc::cdrift(-30,-30, 75);
            Piston::ballLock.set_value(false); // ball lock piston goes down
            Piston::middle.set_value(true);
            ::intake.move(43);  
            pros::delay(3000);
            ::intake.move(34);
            pros::delay(1800);
            // //51.57, 97.87, 47.6
            chassis.moveToPoint(51.57, 97.87, 1250, {.maxSpeed = 127});
            chassis.waitUntil(10);
            ::intake.move(127);
            chassis.waitUntil(20);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntil(21);
            Piston::loader.set_value(true);
            // //0
            chassis.turnToHeading(-0.8, 600, {.maxSpeed = 90});
            ::intake.move(127);
            if(Sensor::d_right.get_confidence() >= 10){
                chassis.setPose(70.95-(getRightDist()) * fabs(cos((chassis.getPose(true).theta))), chassis.getPose().y, chassis.getPose().theta);
            }
            // 53.63, 106.75, -0.8
            chassis.moveToPose(53.63, 109, -0.8, 1000, {.lead = 0.1, .maxSpeed = 85});
            chassis.waitUntilDone();
            Misc::cdrift(45,45,1200);
            //67.40, 79.82, -2.9
            chassis.moveToPoint(67.20, 79.82, 900, {.forwards = false, .maxSpeed = 127});
            chassis.waitUntil(6);
            Piston::loader.set_value(false);
            chassis.waitUntilDone();
            chassis.turnToHeading(-0.8, 500, {.maxSpeed = 90});
            //65.25, 14.94, -1.12
            chassis.moveToPoint(66, 14.94, 1700, {.forwards = false, .maxSpeed = 80});
            chassis.waitUntilDone();
            Misc::distanceResetBackRightTwo(70.95, -30.08);
            pros::delay(350);
            chassis.turnToHeading(-90, 700, {.maxSpeed = 90});
            //54.52, -2.36, 
            //-177.48, 
            //54.92, 6.59, -178
            chassis.moveToPoint(52.02, -2.36, 800, {.maxSpeed = 127});
            chassis.turnToHeading(-178, 500, {.maxSpeed = 127});
            chassis.moveToPose(52.42, 7.09, -178, 1000, {.forwards = false, .lead = 0.1, .maxSpeed = 105});
            chassis.waitUntil(3);
            ::intake.move(0);
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true); 
            Piston::middle.set_value(false);
            ::intake.move(127);
            Misc::cdrift(-20,-20,50);
            Piston::loader.set_value(true);
            Misc::cdrift(-20,-20,1400);
            //52.66, -21.71, -180
            //54.71, 6.46, -180
            //30.46, -26.80, -90
            chassis.moveToPose(53.2, -21.71, -180, 1000, {.lead = 0.1, .maxSpeed = 85});
            chassis.waitUntil(3);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntilDone();
            Misc::cdrift(45,45,1400);
            chassis.moveToPose(54.37, 7.1, -180, 1000, {.forwards = false, .lead = 0.1, .maxSpeed = 105});
            chassis.waitUntilDone();
            Piston::ballLock.set_value(true); // ball lock piston goes down
            Piston::middle.set_value(false);
            Misc::cdrift(-20,-20,50);
            Piston::loader.set_value(false);
            Misc::cdrift(-20,-20,1400);
            chassis.moveToPose(28.46, -29.5, -100, 1250, {.lead = 0.4, .maxSpeed = 127});
            chassis.waitUntil(3);
            ::intake.move(127);
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
            chassis.waitUntilDone();
            chassis.turnToHeading(-100, 400, {.maxSpeed = 127});
            Sensor::o_crossed.set_led_pwm(25); // max brightness for reliable blue/tile detection
            chassis.waitUntilDone();
            Piston::park.set_value(true);
            pros::delay(300);
            Misc::cdrift(69, 70);
            Sensor::o_crossed.set_led_pwm(25); // max brightness for reliable blue/tile detection
            Misc::runFloorOpticalSeqPark(
                []() { return Misc::optical_is_floor_red(Sensor::o_crossed); },
                []() { return Misc::optical_is_floor_tile(Sensor::o_crossed); },
                50, 50);

        }
    }
}

// Auton selection
std::vector<std::pair<std::string, AutonFunc>> autonRoutines = {
    {"Default Auton", Auton::Test::main},
    {"Solo AWP", Auton::Template::solo},
    {"Right 7 Rush", Auton::Template::rightSevenRush},
    {"Left 9 Split", Auton::Template::left},
    {"Right 4 Rush", Auton::Template::rightRush},
    {"Right 4 Qual", Auton::Template::rightFourRush},

    {"Skills", Auton::Skills::main},
};

void autonSwitch() {
    if(TaskHandler::autonSelect) {    
        pros::delay(Misc::DELAY);
        if (Sensor::autonSwitch.get_new_press()) { autonState++; if (autonState == autonRoutines.size()) autonState = 0; }
    }
    pros::lcd::set_text(4, autonRoutines[autonState].first);
}
