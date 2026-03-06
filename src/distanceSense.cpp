#include "distanceSense.h"
#include "config.h"

double getFrontDist() {
    return Sensor::d_front.get_distance() / 25.4;
}

double getBackDist() {
    return Sensor::d_back.get_distance() / 25.4;
}

double getRightDist() {
    return Sensor::d_right.get_distance() / 25.4;
}

double getLeftDist() {
    return Sensor::d_left.get_distance() / 25.4;
}

