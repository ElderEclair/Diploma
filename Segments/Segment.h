#pragma once
#include <cmath>

#include "Structs\Vect.h"
class Segment
{
public:
    virtual double getSize() const = 0;
    double getAngle() const;
    void setAngle(double value);
    Vect getNorm() const;
    void setNorm(Vect value);
    virtual ~Segment() = default;

protected:
    Vect norm = {NAN, NAN};
};


double Segment::getAngle() const
{
    return atan(-norm.nx / norm.ny);
}

Vect Segment::getNorm() const
{
    return norm;
}

void Segment::setAngle(double value)
{
    norm.nx = cos(value);
    norm.ny = sin(value);
}

void Segment::setNorm(Vect value)
{
    norm.nx = value.nx;
    norm.ny = value.ny;
}

