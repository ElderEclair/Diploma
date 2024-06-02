#pragma once
#include <iostream>
#include <math.h>

#include <omp.h>

#include "Segments\CompSegment.h"
#include "Computing\Matrix.h"
#include "dto\Surface.h"

constexpr double PI = 3.14159265;

namespace ViewFactor
{
    Matrix matrix(0);
    double computeElement(
        const CompSegment &src,
        const CompSegment &obj);
    void compute(
        const std::vector<CompSegment> &segments);
    void display(
        const std::vector<CompSegment> &segments,
        std::ostream &out);
    bool isVisible(
        const CompSegment &src,
        const CompSegment &obj,
        const std::vector<CompSegment> &segments);
    bool isVisible(
        const CompSegment &src,
        const CompSegment &obj,
        const CompSegment &barrier);
    bool isCrossing(
        const Point &start,
        const Point &end,
        const Point &fst,
        const Point &snd);
};

bool ViewFactor::isVisible(
    const CompSegment &src,
    const CompSegment &obj,
    const std::vector<CompSegment> &segments)
{
    double sx = obj.getX() - src.getX(),
           sy = obj.getY() - src.getY();
    double scalSrc = ((src.getNorm().nx * sx) + (src.getNorm().ny * sy)),
           scalObj = -((obj.getNorm().nx * sx) + (obj.getNorm().ny * sy));
    if (scalSrc <= 0 || scalObj <= 0)
    {
        return false;
    }
    for (int i = 0; i < segments.size(); i++)
    {
        if (segments[i] == src ||
            segments[i] == obj)
        {
            continue;
        }
        if (!isVisible(src, obj, segments[i]))
        {
            return false;
        }
    }
    return true;
}

bool ViewFactor::isVisible(
    const CompSegment &src,
    const CompSegment &obj,
    const CompSegment &barrier)
{
    double barX = barrier.getX();
    double barY = barrier.getY();
    double barHalfSz = barrier.getSize() / 2;
    double barNX = barrier.getNorm().nx;
    double barNY = barrier.getNorm().ny;
    Point bar1 = {barX + barHalfSz * barNY,
                  barY - barHalfSz * barNX};
    Point bar2 = {barX - barHalfSz * barNY,
                  barY + barHalfSz * barNX};
    if (isCrossing(src.getPoint(),
                   obj.getPoint(),
                   bar1,
                   bar2))
    {
        return 0;
    }
    return 1;
}

bool ViewFactor::isCrossing(
    const Point &start,
    const Point &end,
    const Point &fst,
    const Point &snd)
{
    Vect left, right, center;
    left = {fst.x - start.x,
            fst.y - start.y};
    right = {snd.x - start.x,
             snd.y - start.y};
    center = {end.x - start.x,
              end.y - start.y};
    if (center.mult(left) * center.mult(right) >= 0)
    {
        return false;
    }
    left = {end.x - fst.x,
            end.y - fst.y};
    right = {start.x - fst.x,
             start.y - fst.y};
    center = {snd.x - fst.x,
              snd.y - fst.y};
    if (center.mult(left) * center.mult(right) >= 0)
    {
        return false;
    }
    return true;
}

double ViewFactor::computeElement(
    const CompSegment &src,
    const CompSegment &obj)
{
    double sx = obj.getX() - src.getX(),
           sy = obj.getY() - src.getY(),
           s = sqrt(sx * sx + sy * sy);
    double cosSrc = ((src.getNorm().nx * sx) + (src.getNorm().ny * sy)) / s,
           cosObj = -((obj.getNorm().nx * sx) + (obj.getNorm().ny * sy)) / s;
    double res = cosObj * cosSrc * std::min(obj.getSize() / (2 * s), 1.) * src.getSize() / Data::surfArea[src.getFigId()];
    return res;
}

void ViewFactor::compute(
    const std::vector<CompSegment> &segments)
{
    matrix.resize(Data::surfNames.size());
    int numOfSegments = segments.size();
#pragma omp parallel
    {
        int i, j;
#pragma omp for collapse(2) private(i, j)
        for (i = 0; i < numOfSegments; i++)
        {
            int srcId = segments[i].getFigId();
            for (j = i + 1; j < numOfSegments; j++)
            {
                int objId = segments[j].getFigId();
                if (!isVisible(segments[i], segments[j], segments))
                {
                    continue;
                }
                double viewFactor = computeElement(segments[i], segments[j]);
                ViewFactor::matrix.addToElement(srcId, objId,
                                                viewFactor);
                ViewFactor::matrix.addToElement(objId, srcId,
                                                viewFactor * Data::surfArea[segments[i].getFigId()] / Data::surfArea[segments[j].getFigId()]);
            }
        }
    }
}

void ViewFactor::display(
    const std::vector<CompSegment> &segments, std::ostream &out)
{
    compute(segments);
    matrix.display(out);
}
