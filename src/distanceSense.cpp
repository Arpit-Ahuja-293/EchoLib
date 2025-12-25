#include "distanceSense.h"
#include "config.h"

double getRightDist() {
    return Sensor::d_right.get_distance() / 25.4;
}

double getLeftDist() {
    return Sensor::d_left.get_distance() / 25.4;
}

