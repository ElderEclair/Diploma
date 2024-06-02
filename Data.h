#pragma once
#include <map>
#include <vector>
#include <string>

#include "Segments/CompSegment.h"
#include "Segments/UserSegment.h"

namespace Data
{
    std::vector<UserSegment> lines;
    std::vector<CompSegment> segments;
    std::vector<std::string> surfNames;
    std::map<int, double> surfArea;

    // Clears all data for new calculations
    void clearAll()
    {
        lines.clear();
        segments.clear();
        surfNames.clear();
        surfArea.clear();
    }
}
