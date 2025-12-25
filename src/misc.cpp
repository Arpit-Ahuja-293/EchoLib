#include "misc.h"
#include "config.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>
#include <functional>

namespace Misc {
    pros::motor_brake_mode_e_t brakeState = pros::E_MOTOR_BRAKE_HOLD;
    pros::motor_brake_mode_e_t brakeStateI = pros::E_MOTOR_BRAKE_COAST;
    int val = 0;
    bool turningRed = false;

    void led(){
        while(1){
            // Sensor::o_crossed.set_integration_time(5);
            // Sensor::o_crossed.set_led_pwm(100);
            pros::delay(50);
        }
    }

    void togglePiston(pros::adi::DigitalOut &piston, bool &state) {
        state = !state;
        piston.set_value(state);
    }

    void cdrift(float lV, float rV, int timeout, bool cst) {
        (cst == true) ? (leftMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST), rightMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST)) : (leftMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE), rightMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE));
        leftMotors.move(lV);
        rightMotors.move(rV);
        pros::delay(timeout);
        leftMotors.brake();
        rightMotors.brake();
    }

    void cdrift(float lV, float rV) {
        leftMotors.move(lV);
        rightMotors.move(rV);
    }

    void cbrake(bool cst) {
        (cst == true) ? (leftMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST), rightMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST)) : (leftMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE), rightMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE));
        leftMotors.brake();
        rightMotors.brake();
    }

    void chain(std::vector<std::pair<float, float>>& waypoints, int angular, int lateral) {
        while(!waypoints.empty()){
            std::pair<int, int> target = waypoints.front();
            chassis.turnToPoint(target.first,target.second,angular,{.minSpeed = 10,.earlyExitRange = 2});
            chassis.moveToPoint(target.first,target.second,lateral,{.minSpeed = 10,.earlyExitRange = 2});
            chassis.waitUntilDone();
            waypoints.erase(waypoints.begin());
        }
    }

    void linear(double dist, int timeout, equinox::MoveToPointParams p, bool async) {
        equinox::Pose pose = chassis.getPose(true);
        dist < 0 ? p.forwards = false : p.forwards = true;
        chassis.moveToPoint(
        pose.x + std::sin(pose.theta) * dist,
        pose.y + std::cos(pose.theta) * dist,
        timeout, p, async);
    }

    void driveFor(float distance, float maxSpeed, int timeout, float minspeed, float exit) {
        double headingRadians = chassis.getPose(true).theta;
        double startingX = chassis.getPose().x;
        double startingY = chassis.getPose().y;
        double deltaX = distance * std::sin(headingRadians);
        double deltaY = distance * std::cos(headingRadians);
        double newX = startingX + deltaX;
        double newY = startingY + deltaY;
        if (distance > 0) {
            chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .maxSpeed=maxSpeed, .minSpeed=minspeed, .earlyExitRange=exit});
        }
        else if (distance < 0) {
            chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .maxSpeed=maxSpeed, .minSpeed=minspeed, .earlyExitRange=exit});
        }
    }

    void reset() {
        constexpr double field = 144.0;
        constexpr double halfField = field / 2.0;
        constexpr double offsetF = 10.0;
        constexpr double offsetR = -4.0;

        double heading = s_imu.get_heading();
        double theta = heading * M_PI / 180.0;

        double d_right = Sensor::d_right.get_distance() / 25.4;
        double d_left = Sensor::d_left.get_distance() / 25.4;

        double x = (d_left - halfField) - (offsetR * std::cos(theta)) - (offsetF * std::sin(theta));
        double y = (halfField - d_right) - (offsetF * std::cos(theta)) + (offsetR * std::sin(theta));

        chassis.setPose(x, y, heading);

        printf("Pose -> X: %.2f, Y: %.2f, Heading: %.2f\n", x, y, heading);
    }

    void reset2(int sign) {
        constexpr double offsetR = -13.0;
        double d_left = Sensor::d_left.get_distance() / 25.4;
        double x = chassis.getPose().x;
        double heading = chassis.getPose().theta;
        double y = sign * ((72.0 - d_left) + offsetR);
        chassis.setPose(x, y, heading);
    }

    void resetB1() {
        constexpr double field = 144.0;
        constexpr double halfField = field / 2.0;

        constexpr double offsetF = 3.0;  // forward from robot center
        constexpr double offsetR = 6.0;  // right from robot center

        // Distance sensors (inches)
        double d_back  = Sensor::d_right.get_distance() / 25.4;
        double d_right = Sensor::d_left.get_distance() / 25.4;

        // Heading is assumed to be 0 degrees (robot squared to walls)
        double heading = s_imu.get_heading();

        double x = (halfField - d_right) - offsetR;
        double y = (halfField - d_back)  - offsetF;

        chassis.setPose(x, y, heading);

        printf("Pose -> X: %.2f, Y: %.2f, Heading: %.2f\n", x, y, heading);
    }

    void resetB2() {
        constexpr double field = 144.0;
        constexpr double halfField = field / 2.0;

        constexpr double offsetF = -3.0; // sensor behind center
        constexpr double offsetR = -6.0; // sensor left of center

        // Distance sensors (inches)
        double d_back  = Sensor::d_right.get_distance() / 25.4;
        double d_right = Sensor::d_left.get_distance() / 25.4;

        // Assumed squared to walls
        double heading = s_imu.get_heading();

        double x = (-halfField + d_right) - offsetR;
        double y = (-halfField + d_back)  - offsetF;

        chassis.setPose(x, y, heading);

        printf("Pose -> X: %.2f, Y: %.2f, Heading: %.2f\n", x, y, heading);
    }

    int curve(int input, double t, bool activated) {
        if(!activated) return input;
        val = (std::exp(-t/10)) + std::exp((std::abs(input)-100)/10)*(1-std::exp(-t/10)) * input;
        return val;
    }

    void park(float lV, float rV, int timeout) {
        leftMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
        rightMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
        leftMotors.move(lV);
        rightMotors.move(rV);
        while(timeout > 0){
            timeout -= Misc::DELAY;
            // if(Sensor::o_crossed.get_hue() > 0 && Sensor::o_crossed.get_hue() < 12){
            //     break;
            // }
            pros::delay(Misc::DELAY);
        }
        leftMotors.brake();
        rightMotors.brake();
    }
}
