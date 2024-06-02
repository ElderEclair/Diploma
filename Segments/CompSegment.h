#pragma once
#include <cmath>

#include "Segments\Segment.h"
#include "Structs\Point.h"

class CompSegment : public Segment
{
private:
    double size;
    Point point;
    int figId = NAN;

public:
    CompSegment(double x1,
                double y1,
                double x2,
                double y2,
                int figId);
    ~CompSegment();
    double getX() const;
    double getY() const;
    Point getPoint() const;
    double getSize() const override;
    int getFigId() const;
    void setFigId(int value);
    bool operator==(const CompSegment &other) const;
};

CompSegment::CompSegment(double x1,
                         double y1,
                         double x2,
                         double y2,
                         int figId)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    size = sqrt(dx * dx + dy * dy);
    point = {(x2 + x1) / 2,
             (y2 + y1) / 2};
    norm.nx = dy / size;
    norm.ny = -dx / size;
    this->figId = figId;
}

CompSegment::~CompSegment()
{
}

double CompSegment::getX() const
{
    return point.x;
}

double CompSegment::getY() const
{
    return point.y;
}

Point CompSegment::getPoint() const
{
    return point;
}

double CompSegment::getSize() const
{
    return size;
}

int CompSegment::getFigId() const
{
    return figId;
}

void CompSegment::setFigId(int value)
{
    figId = value;
}

bool CompSegment::operator==(const CompSegment &other) const
{
    return point == other.getPoint() &&
           norm == other.getNorm() &&
           figId == other.getFigId();
}
