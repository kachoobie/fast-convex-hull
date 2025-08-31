#include <cmath>
#include <string>
#include <format>

#ifndef point
#define point

class Point
{
    public:
        float x, y;

        Point(float xcoor, float ycoor);
        bool isEqual(Point other);
        std::string toString();
};

#endif // point