#pragma once

#include "autons.h"
#include "main.h"
#include "config.h"
#include "misc.h"

// Forward declarations
extern equinox::Chassis chassis;

namespace Auton {
    extern int state;
    
    namespace Test {
        void main();
    }
    
    namespace Template {
        void left();
        void right();
        void solo();
        void leftseven();
        void rightFourRush();
        void rushAWP();
        void safeAWP();
        void leftMiddle();
        void rightSevenRush();
        void rightRush();
    }
    
    namespace Qual {
        void leftB();
        void rightB();
        void soloB();
        void leftR();
        void rightR();
        void soloR();
    }
    
    namespace Elim {
        void left();
        void right();
        void solo();
    }
    
    namespace Skills {
        void main();
    }
}

// Auton selection
using AutonFunc = void(*)();
extern int autonState;
extern std::vector<std::pair<std::string, AutonFunc>> autonRoutines;
extern void autonSwitch();
