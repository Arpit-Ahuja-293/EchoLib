#include "screen.h"
#include "config.h"

namespace Screen {
    void update() {
        controller.clear();  
        pros::delay(500);
        // controller.set_text(0, 0, "1: " + std::to_string(Sensor::o_colorSort.get_proximity()));
        // controller.set_text(0, 0, "1: " + std::to_string(Motor::intakeU.get_torque()));
        // controller.set_text(0, 0, "Mode: " + std::to_string(Motor::lbL.get_brake_mode()));
        // controller.set_text(0, 0, "Mode: " + Motor::lbL.get_brake_mode());
        // controller.set_text(0, 0, "Pos: " + std::to_string(Motor::lbR.get_position()));
        // controller.set_text(0, 0, "Pos: " + std::to_string(Sensor::d_filled.get_distance()));
        controller.set_text(0, 0, "State: " + TaskHandler::intakeSpin ? "Normal" : "Slow");

        // controller.set_text(0, 0, "Dist: " + std::to_string(Sensor::d_colorSort.get_distance()));
        // printf("%d\n",Sensor::d_colorSort.get_distance());
        // controller.set_text(0, 0, "Run Time: " + std::to_string(pros::millis() / 1000) + "s");
        // controller.set_text(0, 0, "X: " + std::to_string(chassis.getPose().x) + "\nY: " + std::to_string(chassis.getPose().y));
        // controller.set_text(1, 0, "Test Text 1");
        // controller.set_text(2, 0, "Test Text 2");
        pros::delay(500);
    }
}
