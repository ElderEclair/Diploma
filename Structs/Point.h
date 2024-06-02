#pragma once

struct Point
{
    double x, y;
    bool operator==(const Point &other) const;
    double distanceTo(const Point &p) const;
    bool isNear(const Point &p) const;
};

bool Point::operator==(const Point &other) const
{
    return (x == other.x) &&
           (y == other.y);
}

double Point::distanceTo(const Point &p) const
{
    return sqrt(
        (x - p.x) * (x - p.x) +
        (y - p.y) * (y - p.y));
}

bool Point::isNear(const Point &p) const
{
    return distanceTo(p) < 1e-12;
}
