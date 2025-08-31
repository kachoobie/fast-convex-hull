#include <vector>
#include <algorithm>
#include "point.h"

class ConvexHull
{
    public:
        std::vector<Point> convexHull;
        std::vector<Point> pointSet;
        ConvexHull();
        void addPoint(float x, float y);
        void dump();
        void generateConvexHull();

    private:
        bool static compareXCoors(Point p1, Point p2);
        bool static compareYCoors(Point p1, Point p2);
        void sortPointSet();
        bool turnsRight(Point start, Point middle, Point end);
};