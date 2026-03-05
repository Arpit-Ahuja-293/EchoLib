#include "misc.h"
#include "config.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>
#include <functional>
#include <limits>
#include <algorithm>
#include <vector>

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

    void toggleTripleState(int num){
        if(num == 0){
            //hoard
            Piston::ballLock.set_value(true);
            Piston::middle.set_value(true);
        }
        else if(num == 1){
            //score long
            Piston::ballLock.set_value(true); 
            Piston::middle.set_value(false);
        }
        else if(num == 2){
            //score mid
            Piston::ballLock.set_value(false); 
            Piston::middle.set_value(true);
        }
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

    // Trimmed mean filter with 10 samples for distance sensors
    // Removes highest and lowest values, averages the remaining 8
    static double getTrimmedMeanDistance(pros::Distance& sensor, double mmToIn) {
        constexpr int numSamples = 10;
        constexpr int trimCount = 1; // Remove 1 highest and 1 lowest
        
        std::vector<double> samples;
        samples.reserve(numSamples);
        
        // Collect 10 samples
        for (int i = 0; i < numSamples; i++) {
            double reading = sensor.get_distance() * mmToIn;
            if (std::isfinite(reading)) {
                samples.push_back(reading);
            }
            pros::delay(5); // Small delay between samples
        }
        
        if (samples.empty()) return 0.0;
        if (samples.size() < 3) {
            // Not enough samples, return simple average
            double sum = 0.0;
            for (double val : samples) sum += val;
            return sum / samples.size();
        }
        
        // Sort samples
        std::sort(samples.begin(), samples.end());
        
        // Remove highest and lowest, average the rest
        double sum = 0.0;
        int count = 0;
        for (size_t i = trimCount; i < samples.size() - trimCount; i++) {
            sum += samples[i];
            count++;
        }
        
        return count > 0 ? sum / count : samples[samples.size() / 2];
    }

    static bool poseWithinRadius(double x, double y, double refX, double refY, double radiusIn) {
        if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(refX) || !std::isfinite(refY)) return false;
        const double dx = x - refX;
        const double dy = y - refY;
        return (dx * dx + dy * dy) <= (radiusIn * radiusIn);
    }

    static void applyPoseFallback(double& x, double& y, double estimateX, double estimateY, const PoseSampleParams& params) {
        const double refX = std::isfinite(params.refX) ? params.refX : estimateX;
        const double refY = std::isfinite(params.refY) ? params.refY : estimateY;
        const double radiusIn = std::isfinite(params.radiusIn) ? params.radiusIn : 0.0;
        if (radiusIn <= 0.0 || !poseWithinRadius(x, y, refX, refY, radiusIn)) {
            x = refX;
            y = refY;
        }
    }

    void resetWalls(bool useLeft, bool useRight, bool useFront, PoseSampleParams sampleParams) {
        constexpr double field = 144.0;
        constexpr double halfField = field / 2.0;
        constexpr double WALL_0_X = halfField;
        constexpr double WALL_1_Y = halfField;
        constexpr double WALL_2_X = -halfField;
        constexpr double WALL_3_Y = -halfField;
        constexpr double ANGLE_TOLERANCE = 15.0 * (M_PI / 180.0);
        constexpr double pi = M_PI;
        constexpr double mmToIn = 1.0 / 25.4;

        constexpr double leftOffsetR = -7.1;
        constexpr double rightOffsetR = 7.1;
        constexpr double frontOffsetF = 9.0;
        constexpr double frontOffsetR = 0.0;

        enum class Axis { NONE, X, Y };
        struct Result {
            Axis axis;
            double axisPosition;
        };

        equinox::Pose m_offset(0.0, 0.0, 0.0);
        double realReading = 0.0;

        auto getReading = [&](equinox::Pose pose, Result& result, bool force) {
            // determine sensor pose
            double sensorAngle = pose.theta + m_offset.theta;
            double sensorOffsetX = m_offset.x * std::cos(pose.theta) - m_offset.y * std::sin(pose.theta);
            double sensorOffsetY = m_offset.x * std::sin(pose.theta) + m_offset.y * std::cos(pose.theta);
            double sensorX = pose.x + sensorOffsetX;
            double sensorY = pose.y + sensorOffsetY;

            // determine predicted reading
            double predictedReading;
            double angleError;
            int wall;

            if (angleError = std::abs(std::remainder(0 - sensorAngle, 2 * pi)); angleError < ANGLE_TOLERANCE) {
                predictedReading = (WALL_0_X - sensorX) / std::cos(angleError);
                wall = 0;
            } else if (angleError = std::abs(std::remainder(0.5 * pi - sensorAngle, 2 * pi)); angleError < ANGLE_TOLERANCE) {
                predictedReading = (WALL_1_Y - sensorY) / std::cos(angleError);
                wall = 1;
            } else if (angleError = std::abs(std::remainder(pi - sensorAngle, 2 * pi)); angleError < ANGLE_TOLERANCE) {
                predictedReading = (sensorX - WALL_2_X) / std::cos(angleError);
                wall = 2;
            } else if (angleError = std::abs(std::remainder(1.5 * pi - sensorAngle, 2 * pi)); angleError < ANGLE_TOLERANCE) {
                predictedReading = (sensorY - WALL_3_Y) / std::cos(angleError);
                wall = 3;
            } else {
                wall = -1;
            }

            // determine the new position on the axis based on distance sensor readings
            if (wall == 0) {
                result.axis = Axis::X;
                result.axisPosition = (WALL_0_X - realReading * std::cos(angleError)) - sensorOffsetX;
            } else if (wall == 1) {
                result.axis = Axis::Y;
                result.axisPosition = (WALL_1_Y - realReading * std::cos(angleError)) - sensorOffsetY;
            } else if (wall == 2) {
                result.axis = Axis::X;
                result.axisPosition = (WALL_2_X + realReading * std::cos(angleError)) - sensorOffsetX;
            } else if (wall == 3) {
                result.axis = Axis::Y;
                result.axisPosition = (WALL_3_Y + realReading * std::cos(angleError)) - sensorOffsetY;
            }
        };

        equinox::Pose pose = chassis.getPose(true, true);
        double heading = chassis.getPose().theta;
        const double estimatedX = pose.x;
        const double estimatedY = pose.y;

        Result leftRes = {Axis::NONE, 0.0};
        Result rightRes = {Axis::NONE, 0.0};
        Result frontRes = {Axis::NONE, 0.0};

        if (useLeft) {
            m_offset = equinox::Pose(0.0, -leftOffsetR, M_PI_2);
            realReading = getTrimmedMeanDistance(Sensor::d_left, mmToIn);
            getReading(pose, leftRes, false);
        }
        if (useRight) {
            m_offset = equinox::Pose(0.0, -rightOffsetR, -M_PI_2);
            realReading = getTrimmedMeanDistance(Sensor::d_right, mmToIn);
            getReading(pose, rightRes, false);
        }
        if (useFront) {
            m_offset = equinox::Pose(frontOffsetF, -frontOffsetR, 0.0);
            // Note: To use front sensor, uncomment d_front in config.cpp and config.h, then uncomment the lines below
            // If you don't have a front sensor, set useFront=false when calling resetWalls
            #if 0  // Change to #if 1 after uncommenting d_front in config files
            realReading = getTrimmedMeanDistance(Sensor::d_front, mmToIn);
            getReading(pose, frontRes, false);
            #endif
        }

        double x = estimatedX;
        double y = estimatedY;
        double xSum = 0.0;
        double ySum = 0.0;
        int xCount = 0;
        int yCount = 0;

        auto accumulate = [&](const Result& res) {
            if (!std::isfinite(res.axisPosition)) return;
            if (res.axis == Axis::X) {
                xSum += res.axisPosition;
                xCount++;
            } else if (res.axis == Axis::Y) {
                ySum += res.axisPosition;
                yCount++;
            }
        };

        if (useLeft) accumulate(leftRes);
        if (useRight) accumulate(rightRes);
        if (useFront) accumulate(frontRes);

        if (xCount > 0) x = xSum / static_cast<double>(xCount);
        if (yCount > 0) y = ySum / static_cast<double>(yCount);

        applyPoseFallback(x, y, estimatedX, estimatedY, sampleParams);

        chassis.setPose(x, y, heading);

        printf("Pose -> X: %.2f, Y: %.2f, Heading: %.2f\n", x, y, heading);
    }

    void runFloorOpticalSeq(std::function<bool()> isBlue, std::function<bool()> isTile, float driftLV, float driftRV) {
        // 1) Wait until we see BLUE (first blue park zone edge)
        while (!isBlue()) pros::delay(DELAY);
        // 2) Drift while we're ON blue (cross the park zone)
        while (isBlue()) {
            cdrift(driftLV, driftRV);
            pros::delay(DELAY);
        }
        // 3) Keep moving until we see TILE (fully left the blue zone), then stop
        while (!isTile()) {
            cdrift(driftLV, driftRV);
            pros::delay(DELAY);
        }
        cbrake();
    }

    bool optical_is_floor_red(pros::Optical& o) {
        double h = o.get_hue();
        if (h < 0 || h > 360) return false;  // PROS_ERR_F or invalid
        return (h >= FLOOR_OPTICAL_RED_HUE_MIN && h <= FLOOR_OPTICAL_RED_HUE_MAX &&
                o.get_proximity() > FLOOR_OPTICAL_MIN_PROXIMITY);
    }

    bool optical_is_floor_blue(pros::Optical& o) {
        double h = o.get_hue();
        if (h < 0 || h > 360) return false;  // PROS_ERR_F or invalid
        return (h >= FLOOR_OPTICAL_BLUE_HUE_MIN && h <= FLOOR_OPTICAL_BLUE_HUE_MAX &&
                o.get_proximity() > FLOOR_OPTICAL_MIN_PROXIMITY);
    }

    bool optical_is_floor_tile(pros::Optical& o) {
        double h = o.get_hue();
        if (h < 0 || h > 360) return false;
        return (h >= FLOOR_OPTICAL_TILE_HUE_MIN && h <= FLOOR_OPTICAL_TILE_HUE_MAX &&
                o.get_proximity() > FLOOR_OPTICAL_MIN_PROXIMITY);
    }
}
