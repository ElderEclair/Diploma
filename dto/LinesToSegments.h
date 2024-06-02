#pragma once
#include <vector>
#include <algorithm>

#include "Segments\UserSegment.h"
#include "Segments\CompSegment.h"

double findMinSizeOfLine(const std::vector<UserSegment> &lines, int numOfSubsegments);

std::vector<CompSegment> linesToSegments(const std::vector<UserSegment> &lines, int numOfSubsegments = 1)
{
    std::vector<CompSegment> res;
    const int NUMBER_OF_LINES = lines.size();
    double minSize = findMinSizeOfLine(lines, numOfSubsegments);
    for (int j = 0; j < NUMBER_OF_LINES; j++)
    {
        double num = ceil(lines[j].getSize() / minSize);
        Vect norm = lines[j].getNorm();
        double x0 = lines[j].getX1(),
               y0 = lines[j].getY1(),
               dXn = lines[j].getDx() / num,
               dYn = lines[j].getDy() / num;
        for (double i = 0; i < num; i++)
        {
            res.push_back(
                CompSegment(
                    x0 + dXn * (double)i,
                    y0 + dYn * (double)i,
                    x0 + dXn * (double)(i + 1),
                    y0 + dYn * (double)(i + 1),
                    lines[j].getFigId()));
            res[res.size() - 1].setNorm(norm);
        }
    }
    return res;
}

double findMinSizeOfLine(const std::vector<UserSegment> &lines, int numOfSubsegments)
{
    const int NUMBER_OF_LINES = lines.size();
    double minSize = lines[0].getSize();
    for (int i = 0; i < NUMBER_OF_LINES; i++)
    {
        minSize = std::min(minSize, lines[i].getSize());
    }
    minSize /= numOfSubsegments;
    return minSize;
}
