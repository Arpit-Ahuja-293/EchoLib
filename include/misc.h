#pragma once

#include "main.h"
#include "equinox/api.hpp"
#include <vector>
#include <limits>
#include <functional>

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

    /** Distance reset using front and right sensors with trimmed mean.
     *  Updates chassis X from right sensor (when confident) and Y from front sensor (when confident).
     *  rightWallX: wall X coord the right sensor faces (e.g. -66.5 for left side)
     *  frontWallY: wall Y coord the front sensor faces (e.g. 123.73) */
    void distanceResetFrontRight(double rightWallX = -66.5, double frontWallY = 123.73);

    /** Distance reset using back and left sensors (raw readings, no trimmed mean).
     *  Updates chassis X from left sensor (when confident) and Y from back sensor (when confident).
     *  leftWallX: wall X coord the left sensor faces
     *  backWallY: wall Y coord the back sensor faces */
    void distanceResetBackLeft(double leftWallX = 0.0, double backWallY = 0.0);

    /** Distance reset using back and right sensors (raw readings, no trimmed mean).
     *  Updates chassis X from right sensor (when confident) and Y from back sensor (when confident).
     *  rightWallX: wall X coord the right sensor faces
     *  backWallY: wall Y coord the back sensor faces */
    void distanceResetBackRight(double rightWallX = 0.0, double backWallY = 0.0);
    void distanceResetBackRightTwo(double rightWallX = 0.0, double backWallY = 0.0);
    int curve(int input, double t = 5, bool activated = true);
    void park(float lV, float rV, int timeout);

    void runFloorOpticalSeq(std::function<bool()> isBlue, std::function<bool()> isTile, float driftLV = 50, float driftRV = 50);
    void runFloorOpticalSeqPark(std::function<bool()> isRed, std::function<bool()> isTile, float driftLV = 50, float driftRV = 50);

    // --- Floor optical hue helpers (VEX field: red element vs tile) ---
    // Hue ranges match common VEX floor colors; min proximity avoids noise.
    constexpr float FLOOR_OPTICAL_RED_HUE_MIN = 0.0f;
    constexpr float FLOOR_OPTICAL_RED_HUE_MAX = 20.0f;
    constexpr float FLOOR_OPTICAL_BLUE_HUE_MIN = 180.0f;
    constexpr float FLOOR_OPTICAL_BLUE_HUE_MAX = 230.0f;
    constexpr float FLOOR_OPTICAL_TILE_HUE_MIN = 40.0f;
    constexpr float FLOOR_OPTICAL_TILE_HUE_MAX = 70.0f;
    constexpr int FLOOR_OPTICAL_MIN_PROXIMITY = 50;

    /** True if optical hue is in red range and proximity is high enough (floor red element). */
    bool optical_is_floor_red(pros::Optical& o);
    /** True if optical hue is in blue range and proximity is high enough (floor blue park zone). */
    bool optical_is_floor_blue(pros::Optical& o);
    /** True if optical hue is in tile range and proximity is high enough (field tile). */
    bool optical_is_floor_tile(pros::Optical& o);
}
