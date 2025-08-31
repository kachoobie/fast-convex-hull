#include "../include/convexhull.h"
#include <iostream>

ConvexHull::ConvexHull()
{
}

void ConvexHull::addPoint(float x, float y)
{
    Point newPoint(x, y);
    this->pointSet.push_back(newPoint);
}

void ConvexHull::dump()
{
    this->pointSet.clear();
    this->convexHull.clear();
}

void ConvexHull::generateConvexHull()
{
    if (this->pointSet.size() < 3)
    {
        this->convexHull = this->pointSet;
        return;
    }

    this->sortPointSet();

    std::vector<Point> upperHull = this->findUpperHull();
    std::vector<Point> lowerHull = this->findLowerHull();

    this->convexHull = upperHull;

    for (int i = 1; i < lowerHull.size() - 1; ++i) {
        this->convexHull.push_back(lowerHull.at(i));
    }
}

bool ConvexHull::compareXCoors(Point p1, Point p2)
{
    return p1.x < p2.x;
}

bool ConvexHull::compareYCoors(Point p1, Point p2)
{
    return p1.y < p2.y;
}

void ConvexHull::sortPointSet()
{
    std::stable_sort(this->pointSet.begin(), this->pointSet.end(), this->compareYCoors);
    std::stable_sort(this->pointSet.begin(), this->pointSet.end(), this->compareXCoors);
}

bool ConvexHull::turnsRight(Point start, Point middle, Point end)
{
    float crossProduct = (middle.x - start.x)*(end.y - start.y) - (middle.y - start.y)*(end.x - start.x);
    float epsilon = -1e-9;
    return crossProduct < epsilon;
}

std::vector<Point> ConvexHull::findUpperHull()
{
    std::vector<Point> upperHull;
    upperHull.push_back(this->pointSet.at(0));
    upperHull.push_back(this->pointSet.at(1));

    for (int i = 2; i < this->pointSet.size(); ++i) {
        Point end = this->pointSet.at(i);
        while (upperHull.size() > 1) {
            Point start = upperHull.at(upperHull.size() - 2);
            Point middle = upperHull.at(upperHull.size() - 1);

            if (this->turnsRight(start, middle, end)) {
                upperHull.push_back(end);
                break;
            } else {
                upperHull.pop_back();
            }
        }
        if (upperHull.size() == 1) {
            upperHull.push_back(end);
        }
    }

    return upperHull;
}

std::vector<Point> ConvexHull::findLowerHull()
{
    std::vector<Point> lowerHull;
    int lastIndex = this->pointSet.size() - 1;
    lowerHull.push_back(this->pointSet.at(lastIndex));
    lowerHull.push_back(this->pointSet.at(lastIndex - 1));

    for (int i = lastIndex - 2; i >= 0; --i) {
        Point end = this->pointSet.at(i);
        while (lowerHull.size() > 1) {
            Point start = lowerHull.at(lowerHull.size() - 2);
            Point middle = lowerHull.at(lowerHull.size() - 1);

            if (this->turnsRight(start, middle, end)) {
                lowerHull.push_back(end);
                break;
            } else {
                lowerHull.pop_back();
            }
        }
        if (lowerHull.size() == 1) {
            lowerHull.push_back(end);
        }
    }

    return lowerHull;
}