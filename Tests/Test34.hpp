#pragma once

#include <vector>
#include <fstream>

#include "Computing\Matrix.h"

#include "Tests/FileFiller.h"
#include "Tests/TestExecuter.h"

#include "Data.h"
#include "Parsing\XmlCodeToPropertyTree.hpp"
#include "dto\SurfaceToLines.h"

void Test34(double w, double alpha)
{
    // calculate theoretical answer
    Matrix theor_ans(2);
    double offset = 20;
    {
        double ans = 1 - sin(alpha / 2);
        theor_ans.setElement(0, 1, ans);
        theor_ans.setElement(1, 0, ans);
    }
    // Prepare Input .svg file
    {
        std::ofstream inputFile("Input_files/Test34.svg");
        startSvgFile(inputFile);
        inputFile << "\t "
                  << "<polyline" << '\n'
                  << "\t\t "
                  // id
                  << "id=" << '"' << "A1" << '"' << '\n'
                  << "\t\t "
                  // Coords
                  << "points=" << '"' << offset + w << ',' << offset << ' ' << offset << ',' << offset << '"' << '\n'
                  << "\t\t "
                  << "stroke=" << '"' << "black" << '"' << '\n'
                  << "\t "
                  << "/>" << '\n';
        inputFile << "\t "
                  << "<polyline" << '\n'
                  << "\t\t "
                  // id
                  << "id=" << '"' << "A2" << '"' << '\n'
                  << "\t\t "
                  // Coords
                  << "points=" << '"' << offset << ',' << offset << ' ' << offset + w * cos(alpha) << ',' << offset + w * sin(alpha) << '"' << '\n'
                  << "\t\t "
                  << "stroke=" << '"' << "black" << '"' << '\n'
                  << "\t "
                  << "/>" << '\n';
        endSvgFile(inputFile);
    }
    // calculate practical result
    {
        std::vector<Surface> surfs;
        Parser::parseXmlFile("Input_files/Test34.svg", surfs);
        std::vector<UserSegment> tempsegm;
        for (int i = 0; i < surfs.size(); i++)
        {
            tempsegm = surfaceToLines(surfs[i], false);
            Data::lines.insert(Data::lines.end(), tempsegm.begin(), tempsegm.end());
        }
    }
    std::ofstream outputFile("Output_files/Test34.txt");
    outputFile << "\n===================================================\n"
               << "Test 34\n"
               << "-------------------------------\n"
               << "w = " << w << ", alpha= " << alpha << '\n'
               << "-------------------------------\n";
    outputFile << "Theoretical matrix:\n";
    theor_ans.display(outputFile);
    execTest(theor_ans, outputFile);
    outputFile << "\n===================================================\n";

    Data::clearAll();
    ViewFactor::matrix.clear();
}
