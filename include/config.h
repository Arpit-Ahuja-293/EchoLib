#pragma once

#include "main.h"
#include "pros/adi.hpp"
#include "pros/rtos.hpp"
#include "equinox/api.hpp"

extern pros::Controller controller;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

namespace Motor{
    extern pros::Motor intakeF;
    extern pros::Motor intakeM;
} // namespace Motor

extern pros::MotorGroup intake; // MotorGroup for bottom and middle intake motors

namespace Sensor{
    extern pros::Distance d_right;
    extern pros::Distance d_left;
    extern pros::Distance d_front; 
    extern pros::Distance d_back;
    // extern pros::Distance d_filled;
    // extern pros::Optical o_colorSort;
    extern pros::Optical o_crossed;
    extern pros::adi::DigitalIn autonSwitch;
} // namspace Sensor

namespace Piston{
    extern pros::adi::DigitalOut loader;
    extern pros::adi::DigitalOut hook;
    extern pros::adi::DigitalOut middle;
    extern pros::adi::DigitalOut ballLock;
    extern pros::adi::DigitalOut park;
    extern pros::adi::DigitalOut pistonFunnels;
} // namespace Piston

class CustomIMU : public pros::IMU {
    public:
        CustomIMU(int port, double scalar);
        virtual double get_rotation() const override;

    private:
        const int m_port;
        const double m_scalar;
};

// extern pros::Imu imu;
extern CustomIMU s_imu;
extern pros::Rotation horizontalEnc;
extern pros::Rotation verticalEnc;

// extern equinox::TrackingWheel horizontal;
// extern equinox::TrackingWheel vertical;
// extern equinox::Drivetrain drivetrain;
// extern equinox::ControllerSettings linearController;
// extern equinox::ControllerSettings angularController;
// extern equinox::OdomSensors sensors;
// extern equinox::ExpoDriveCurve throttleCurve;
// extern equinox::ExpoDriveCurve steerCurve;
extern equinox::Chassis chassis;
