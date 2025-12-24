#define FMT_HEADER_ONLY
#include "fmt/core.h"

#include "equinox/pose.hpp"

equinox::Pose::Pose(float x, float y, float theta) {
    this->x = x;
    this->y = y;
    this->theta = theta;
}

equinox::Pose equinox::Pose::operator+(const equinox::Pose& other) const {
    return equinox::Pose(this->x + other.x, this->y + other.y, this->theta);
}

equinox::Pose equinox::Pose::operator-(const equinox::Pose& other) const {
    return equinox::Pose(this->x - other.x, this->y - other.y, this->theta);
}

float equinox::Pose::operator*(const equinox::Pose& other) const { return this->x * other.x + this->y * other.y; }

equinox::Pose equinox::Pose::operator*(const float& other) const {
    return equinox::Pose(this->x * other, this->y * other, this->theta);
}

equinox::Pose equinox::Pose::operator/(const float& other) const {
    return equinox::Pose(this->x / other, this->y / other, this->theta);
}

equinox::Pose equinox::Pose::lerp(equinox::Pose other, float t) const {
    return equinox::Pose(this->x + (other.x - this->x) * t, this->y + (other.y - this->y) * t, this->theta);
}

float equinox::Pose::distance(equinox::Pose other) const { return std::hypot(this->x - other.x, this->y - other.y); }

float equinox::Pose::angle(equinox::Pose other) const { return std::atan2(other.y - this->y, other.x - this->x); }

equinox::Pose equinox::Pose::rotate(float angle) const {
    return equinox::Pose(this->x * std::cos(angle) - this->y * std::sin(angle),
                        this->x * std::sin(angle) + this->y * std::cos(angle), this->theta);
}

std::string equinox::format_as(const equinox::Pose& pose) {
    // the double brackets become single brackets
    return fmt::format("equinox::Pose {{ x: {}, y: {}, theta: {} }}", pose.x, pose.y, pose.theta);
}
