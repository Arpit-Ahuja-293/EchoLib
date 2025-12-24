#include "jam.h"
#include "config.h"

namespace Jam {
    int counter = 0;
    int counter1 = 0;
    bool stuck = false;

    /**
     * @brief AntiJam function that detects jams using efficiency and reverses intake
     * Checks every 300ms if bottom intake efficiency is <= 0.1 (10%)
     * If jammed, reverses intake and top intake for 300ms, then resumes forward
     */
    void antiJam() {
        static uint32_t lastCheckTime = pros::millis();
        
        if(TaskHandler::antiJam) {
            // Check every 300ms
            if(pros::millis() - lastCheckTime >= 300){
                // Check if bottom intake efficiency is <= 10% (0.1 when divided by 100)
                if(Motor::intakeF.get_efficiency()/100 <= 0.1){
                    // Reverse intake and top intake to unjam
                    ::intake.move(-127);
                    Motor::intakeU.move(127);
                    pros::delay(300);
                    // Resume forward motion
                    ::intake.move(127);
                    Motor::intakeU.move(-127);
                    lastCheckTime = pros::millis();
                } else {
                    lastCheckTime = pros::millis();
                }
            }
        }
    }
}
