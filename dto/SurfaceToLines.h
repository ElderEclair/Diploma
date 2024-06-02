#pragma once
#include <vector>

#include "Data.h"

#include "Segments\UserSegment.h"
#include "dto\Surface.h"
#include "Structs\Vect.h"

std::vector<UserSegment> surfaceToLines(const Surface &surface, bool toLoop = true)
{
    int numOfPoints = surface.getPointsNum();
    std::vector<UserSegment> res;
    int id = surface.getFigId();
    Data::surfArea[id] = 0.;
    for (int i = 0; i < numOfPoints - 1; i++)
    {
        Point p1 = surface.getPoint(i);
        Point p2 = surface.getPoint(i + 1);
        if (p1 == p2)
        {
            continue;
        }
        Data::surfArea[id] += p1.distanceTo(p2);
        res.push_back(
            UserSegment(
                p1,
                p2,
                surface.getFigId()));
    }
    if (surface.isLooped() || toLoop == false)
    {
        return res;
    }
    for (int i = numOfPoints - 1; i > 0; i--)
    {
        Point p1 = surface.getPoint(i);
        Point p2 = surface.getPoint(i - 1);
        if (p1 == p2)
        {
            continue;
        }
        Data::surfArea[id] += p1.distanceTo(p2);
        res.push_back(
            UserSegment(
                p1,
                p2,
                surface.getFigId()));
    }
    return res;
}