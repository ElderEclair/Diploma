#pragma once
#include <iostream>
#include <fstream>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include <boost\foreach.hpp>
#include "Structs\Point.h"

#include "dto\Surface.h"
namespace pt = boost::property_tree;

namespace Parser
{
    std::vector<Point> parseCoords(std::string coords);
    void recursiveParsing(pt::ptree tree,
                          std::vector<Surface> &surfaces,
                          std::string tab = "");
    void parseXmlFile(char *xmlFile, std::vector<Surface> &surfaces);
}

std::vector<Point> Parser::parseCoords(std::string coords)
{
    std::vector<Point> res;
    std::string num = "";
    int i = 0;
    double x = 0;
    char chr;
    double sign = 1.;
    while (coords[i])
    {
        chr = coords[i];
        if (chr == ',')
        {
            x = stoi(num);
            num = "";
        }
        else if (chr == '-')
        {
            sign = -1.;
        }
        else if (chr == ' ')
        {
            res.push_back({x, sign * stod(num)});
            num = "";
            sign = 1.;
        }
        else
        {
            num += chr;
        }
        i++;
    }
    if (!num.empty())
    {
        res.push_back({x, stod(num)});
    }
    return res;
}

void Parser::recursiveParsing(pt::ptree tree,
                              std::vector<Surface> &surfaces,
                              std::string tab)
{
    BOOST_FOREACH (auto &v, tree)
    {
        // std::cout << tab << v.first << ':';
        if (v.first == "polyline")
        {
            std::string userId = v.second.get<std::string>("<xmlattr>.id");
            std::string coords = v.second.get<std::string>("<xmlattr>.points");
            std::vector<Point> points = parseCoords(coords);
            surfaces.push_back(Surface(points, userId));
        }
        recursiveParsing(v.second, surfaces, tab + "    ");
    }
}

void Parser::parseXmlFile(char *xmlFile, std::vector<Surface> &surfaces)
{
    pt::ptree tree;
    tree.clear();
    pt::read_xml(xmlFile, tree);
    recursiveParsing(tree, surfaces);
}
