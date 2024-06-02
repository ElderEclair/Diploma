#pragma once
#include <cmath>
#include <string>

#include "Segments\Segment.h"
#include "Structs\Point.h"

class UserSegment : public Segment
{
private:
    Point p1, p2;
    int figId;

public:
    UserSegment(
        double x1,
        double y1,
        double x2,
        double y2,
        int figId);
    UserSegment(
        Point &point1,
        Point &point2,
        int figId);
    ~UserSegment();
    double getX1() const;
    double getY1() const;
    double getX2() const;
    double getY2() const;
    double getDx() const;
    double getDy() const;
    void setX1(double value);
    void setY1(double value);
    void setX2(double value);
    void setY2(double value);
    double getSize() const override;
    void setAngle(double value);
    void setNorm(Vect value);
    int getFigId() const;
};

UserSegment::UserSegment(
    double x1,
    double y1,
    double x2,
    double y2,
    int figId
) :
    p1({x1, y1}),
    p2({x2, y2}),
    figId(figId)
{
    //p1 = {x1, y1};
    //p2 = {x2, y2};
    //this->figId = figId;
    norm.nx = getDy() / getSize();
    norm.ny = -getDx() / getSize();
}

UserSegment::UserSegment(
    Point &point1,
    Point &point2,
    int figId
) :
    p1(point1),
    p2(point2),
    figId(figId)
{
    //p1 = point1;
    //p2 = point2;
    //this->figId = figId;
    norm.nx = getDy() / getSize();
    norm.ny = -getDx() / getSize();
}

UserSegment::~UserSegment()
{
}

double UserSegment::getX1() const
{
    return p1.x;
}

double UserSegment::getY1() const
{
    return p1.y;
}

double UserSegment::getX2() const
{
    return p2.x;
}

double UserSegment::getY2() const
{
    return p2.y;
}

double UserSegment::getDx() const
{
    return p2.x - p1.x;
}

double UserSegment::getDy() const
{
    return p2.y - p1.y;
}

void UserSegment::setX1(double value)
{
    p1.x = value;
}

void UserSegment::setY1(double value)
{
    p1.y = value;
}

void UserSegment::setX2(double value)
{
    p2.x = value;
}

void UserSegment::setY2(double value)
{
    p2.y = value;
}

double UserSegment::getSize() const
{
    return sqrt(getDx() * getDx() + getDy() * getDy());
}

void UserSegment::setAngle(double value)
{
    norm.nx = cos(value);
    norm.ny = sin(value);
    double x = (p1.x + p2.x) / 2, y = (p1.y + p2.y) / 2;
    p1.x = x - norm.ny * getSize() / 2;
    p2.x = x + norm.ny * getSize() / 2;
    p1.y = y + norm.nx * getSize() / 2;
    p2.y = y - norm.nx * getSize() / 2;
}

void UserSegment::setNorm(Vect value)
{
    norm.nx = value.nx;
    norm.ny = value.ny;
    double x = (p1.x + p2.x) / 2, y = (p1.y + p2.y) / 2;
    p1.x = x - norm.ny * getSize() / 2;
    p2.x = x + norm.ny * getSize() / 2;
    p1.y = y + norm.nx * getSize() / 2;
    p2.y = y - norm.nx * getSize() / 2;
}

int UserSegment::getFigId() const
{
    return figId;
}
