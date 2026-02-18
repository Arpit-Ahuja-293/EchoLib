#pragma once

#include "main.h"
#include "equinox/api.hpp"
#include <vector>
#include <limits>

// Forward declarations
extern equinox::Chassis chassis;
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

namespace Misc {
    constexpr int DELAY = 10;
    extern pros::motor_brake_mode_e_t brakeState;
    extern pros::motor_brake_mode_e_t brakeStateI;
    extern int val;
    extern bool turningRed;

    void led();
    void togglePiston(pros::adi::DigitalOut &piston, bool &state);
    void toggleTripleState(int num);
    void cdrift(float lV, float rV, int timeout, bool cst = true);
    void cdrift(float lV, float rV);
    void cbrake(bool cst = true);
    void chain(std::vector<std::pair<float, float>>& waypoints, int angular = 450, int lateral = 2300);
    void linear(double dist, int timeout, equinox::MoveToPointParams p = {}, bool async = true);
    void driveFor(float distance, float maxSpeed, int timeout, float minspeed = 0, float exit = 0);
    void reset();
    void reset2(int sign);
    void resetB1();
    void resetB2();
    int curve(int input, double t = 5, bool activated = true);
    void park(float lV, float rV, int timeout);

    // Pose sampling parameters for resetWalls
    struct PoseSampleParams {
        double refX = std::numeric_limits<double>::quiet_NaN();
        double refY = std::numeric_limits<double>::quiet_NaN();
        double radiusIn = 8.0;
    };

    void resetWalls(bool useLeft = true, bool useRight = true, bool useFront = true, PoseSampleParams sampleParams = PoseSampleParams{});
}
