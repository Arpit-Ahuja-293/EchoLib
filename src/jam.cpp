#include "jam.h"
#include "config.h"

namespace Jam {
    int counter = 0;
    int counter1 = 0;
    bool stuck = false;

    void antiJam() {
        if(TaskHandler::antiJam){
            counter+=Misc::DELAY;
            if(Motor::intakeF.get_actual_velocity() == 0 && counter > 300) stuck = true;
            if (stuck == true) {
                // TaskHandler::colorSort = false;
                Motor::intakeF.move(-127);
                pros::delay(100);
                Motor::intakeF.move(127);
                stuck = false;
                counter = 0;  
            }
        }
        if(TaskHandler::antiJam2){
            counter+=Misc::DELAY;
            if(Motor::intakeU.get_actual_velocity() == 0 && counter > 300) stuck = true;
            if (stuck == true) {
                // TaskHandler::colorSort = false;
                Motor::intakeU.move(-127);
                pros::delay(100);
                Motor::intakeU.move(127);
                stuck = false;
                counter = 0;  
            }
        }
    }
}
