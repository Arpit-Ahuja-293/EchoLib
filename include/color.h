#pragma once

#include "main.h"
#include "config.h"
#include "taskhandler.h"

namespace Color {
    enum class colorVals { NONE, BLUE, RED };
    extern colorVals state;
    extern bool isDone;
    extern bool isC;
    extern bool extend_once;
    
    inline bool isRed(double h, double low, double max) { return h > low && h < max; }
    inline bool isBlue(double h, double low, double max) { return h > low && h < max; }
    inline bool withinProx(int input, double max) { return (input > max); }
    colorVals colorConvertor(colorVals input);
    void colorSort(colorVals input);
}
