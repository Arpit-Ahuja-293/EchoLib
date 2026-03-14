#include "main.h"
#include "equinox/api.hpp"
#include "pros/rtos.hpp"
#include "pros/distance.hpp"
// #include "pros/optical.hpp"
 // <--------------------------------------------------------------- Setup ------------------------------------------------------------------>
// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup leftMotors({-14, -2, -12}, pros::MotorGearset::blue); // LEFT_FRONT_DRIVE_PORT = -9, LEFT_MIDDLE_DRIVE_PORT = -8, LEFT_BACK_DRIVE_PORT = -7
pros::MotorGroup rightMotors({18, 20, 16}, pros::MotorGearset::blue); // RIGHT_FRONT_DRIVE_PORT = 2, RIGHT_MIDDLE_DRIVE_PORT = 5, RIGHT_BACK_DRIVE_PORT = 4

namespace Motor{
  pros::Motor intakeF(15, pros::MotorGearset::blue); // BOTTOM_INTAKE_PORT = -12
  pros::Motor intakeM(-17, pros::MotorGearset::blue); // MIDDLE_INTAKE_PORT = 20
} // namespace Motor

// Intake MotorGroup (bottom + middle)
pros::MotorGroup intake({15, -17}, pros::MotorGearset::blue); // BOTTOM_INTAKE_PORT and MIDDLE_INTAKE_PORT

namespace Sensor{
  pros::Distance d_right(7); // rightDistancePort = 14
  pros::Distance d_left(5); // leftDistancePort = 17
  pros::Distance d_front(9); 
  pros::Distance d_back(21);
  // pros::Optical o_colorSort(7); // opticalSensor = 7
  pros::Optical o_crossed(4); // Optical sensor in use (floor/crossed). WARNING: Port conflicts with d_left. Update to correct port if second optical sensor exists
  pros::adi::DigitalIn autonSwitch('g'); // AUTON_SELECTOR = 'e'
} // namspace Sensor

namespace Piston{
  pros::adi::DigitalOut loader('a'); // matchloadDoinker = 'f'
  pros::adi::DigitalOut hook('b'); // wingPiston = 'd' (descore piston)
  pros::adi::DigitalOut middle('c'); // middleGoalPiston = 'e'
  pros::adi::DigitalOut ballLock('d'); // ballLockPiston = 'g'
  pros::adi::DigitalOut park('f'); // parkPiston = 'h'
  pros::adi::DigitalOut pistonFunnels('e'); // pistonFunnels = 'f'
} // namespace Piston

// <------------------------------------------------------------- Odom Sensors ------------------------------------------------------------->
class CustomIMU : public pros::IMU {
  public:
    CustomIMU(int port, double scalar)
      : pros::IMU(port),
        m_port(port),
        m_scalar(scalar) {}
    virtual double get_rotation() const {
      return pros::c::imu_get_rotation(m_port) * m_scalar;
    }
  private:
    const int m_port;
    const double m_scalar;
};

// CustomIMU s_imu(9, 1.00528659218); // checked
CustomIMU s_imu(19, 1.01152008991); // IMU_PORT = 19
// CustomIMU s_imu(7, 1.0); // checked

pros::Rotation horizontalEnc(-8); // horizontalOdomRotational = -8
pros::Rotation verticalEnc(-13); // vertOdomRotational = 9

equinox::TrackingWheel vertical_tracking_wheel(&verticalEnc, 2.0 , -0.08); // Single - calibrated for accurate odometry
equinox::TrackingWheel horizontal_tracking_wheel(&horizontalEnc, 2.0 , -2.75); // Double Stacked - calibrated for accurate odometry

// <---------------------------------------------------------------- Config ---------------------------------------------------------------->
equinox::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.25, // CHASSIS_TRACK_WIDTH = 11.25 inch track width
                              equinox::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // CHASSIS_RPM = 450
                              8 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

equinox::ControllerSettings linearController (5.37, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              23.93, // derivative gain (kD)
                                              3.0, // anti windup
                                              1.0, // small error range, in inches
                                              90, // small error range timeout, in milliseconds
                                              3.0, // large error range, in inches
                                              400, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

equinox::ControllerSettings angularController(2.468, // proportional gain (kP)
                                              0.1, // integral gain (kI)
                                              19.87, // derivative gain (kD) 
                                              3.0, // anti windup
                                              0.0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0.0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

equinox::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            nullptr, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &s_imu // inertial sensor
);

// input curve for throttle input during driver control
equinox::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     0, // minimum output where drivetrain will move out of 127
                                     1 // expo curve gain
);

// input curve for steer input during driver control
equinox::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  0, // minimum output where drivetrain will move out of 127
                                  1.05 // expo curve gain
);

// create the chassis
equinox::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);