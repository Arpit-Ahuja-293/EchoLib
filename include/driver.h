#pragma once

#include "main.h"
#include "config.h"
#include "misc.h"
#include "taskhandler.h"

namespace Driver {
    extern bool b_loader;
    extern bool b_clamp;
    extern bool b_aligner;
    extern bool b_hook;
    extern bool b_driver;
    extern bool b_middle;
    extern int saberC;
    extern double curveVal;
    
    void joystick();
    void intake();
    void piston();
    void moveIntake();
    void ballLockFunction();
    void matchloadDoinkerControl();
    void trapdoorDoinkerControl();
    void descoreMechanism();
}
