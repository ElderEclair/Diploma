#pragma once
#include <vector>
#include <stdexcept>

#include "Structs\Point.h"

#include "Data.h"

class Surface
{
private:
    std::vector<Point> data;
    int figId;
    std::string userId;

public:
    //Surface() = default;
    Surface(const std::vector<Point>& data, std::string userId);
    ~Surface();
    int getFigId() const;
    int getPointsNum() const;
    Point getPoint(int i) const;
    bool isLooped() const;
    /*static int getNumOfSurfs(){
        return Data::surfNames.size();
    }*/
};


Surface::Surface(const std::vector<Point>& points, std::string userId)
{
    for(Point point : points){
        data.push_back(point);
    }
    this->userId = userId;
    Data::surfNames.push_back(userId);
    figId = Data::surfNames.size()-1;
}

Surface::~Surface()
{
}

int Surface::getFigId() const
{
    return figId;
}

int Surface::getPointsNum() const
{
    return data.size();
}

Point Surface::getPoint(int i) const
{
    if(i < data.size())
    {
        return data[i];
    }
    throw std::runtime_error("B Surface точек меньше чем было запрошено");
}

bool Surface::isLooped() const
{
    int size = data.size();
    return data[0].isNear(data[size-1]);
}
