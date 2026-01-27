#include "jam.h"
#include "config.h"

void intakeUnjam(){
    uint32_t lastCheckTime = pros::millis();
        while (true) {
            // prints intake funcs
            if(pros::millis() - lastCheckTime >= 300){
                if(::intake.get_efficiency()/100 <= 0.1){
                    ::intake.move(127);
                    pros::delay(300);
                    ::intake.brake();
                    lastCheckTime = pros::millis();
            } else{
                lastCheckTime = pros::millis();
            }
            // delay to save resources
            pros::delay(25);
        }
    }
}
