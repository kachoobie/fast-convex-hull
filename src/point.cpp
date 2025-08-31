#include "../include/point.h"

Point::Point(float xcoor, float ycoor)
{
    x = xcoor;
    y = ycoor;
}

bool Point::isEqual(Point other)
{
    float epsilon = 1.e-9;
    return std::abs(this->x - other.x) < epsilon && std::abs(this->y - other.y) < epsilon;
}

std::string Point::toString()
{
    std::string xString = std::to_string(this->x);
    std::string yString = std::to_string(this->y);
    std::string out = std::format("Point({}, {})", xString, yString);
    return out;
}