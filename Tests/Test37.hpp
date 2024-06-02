#pragma once

#include <vector>
#include <fstream>

#include "Computing\Matrix.h"

#include "Tests/FileFiller.h"
#include "Tests/TestExecuter.h"

#include "Data.h"
#include "Parsing\XmlCodeToPropertyTree.hpp"
#include "dto\SurfaceToLines.h"

void Test37(double a, double r, double b1, double b2)
{

    // calculate theoretical answer
    Matrix theor_ans(2);
    double offset = 20 + std::max(r, b1);
    {
        double B1 = b1 / a,
               B2 = b2 / a;
        double ans = 1 / (2 * PI) *
                     (atan(B1) - atan(B2));
        theor_ans.setElement(0, 1, ans);
        theor_ans.setElement(1, 0, ans * (2 * PI * r) / (b1 - b2));
    }
    int numOfEdges = 10;
    while (numOfEdges < 100)
    {
        // Prepare Input .svg file
        std::string fstart = "Input_files/Test37_",
                    fend = ".svg";
        std::string fstr = fstart + std::to_string(numOfEdges) + fend;
        char *filename = &fstr[0];
        {
            std::ofstream inputFile(filename);
            startSvgFile(inputFile);
            inputFile << "\t "
                      << "<polyline" << '\n'
                      << "\t\t "
                      // id
                      << "id=" << '"' << "circle" << '"' << '\n'
                      << "\t\t "
                      // Coords
                      << "points=" << '"';
            for (int j = 0; j <= numOfEdges; j++)
            {
                inputFile << offset + r * sin(PI * 2 * j / numOfEdges) << ',' << offset + a - r * cos(PI * 2 * j / numOfEdges) << ' ';
            }
            inputFile << '"' << '\n'
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
                      << "points=" << '"' << offset - b2 << ',' << offset + 0 << ' ' << offset - b1 << ',' << offset + 0 << '"' << '\n'
                      << "\t\t "
                      << "stroke=" << '"' << "black" << '"' << '\n'
                      << "\t "
                      << "/>" << '\n';
            endSvgFile(inputFile);
        }
        // calculate practical result
        {
            std::vector<Surface> surfs;
            Parser::parseXmlFile(filename, surfs);
            std::vector<UserSegment> tempsegm;
            for (int i = 0; i < surfs.size(); i++)
            {
                tempsegm = surfaceToLines(surfs[i], false);
                Data::lines.insert(Data::lines.end(), tempsegm.begin(), tempsegm.end());
            }
        }
        std::ofstream outputFile;
        if (10 == numOfEdges)
        {
            outputFile.open("Output_files/Test37.txt");
        }
        else
        {
            outputFile.open("Output_files/Test37.txt", std::ios::app);
        }
        outputFile << "\n===================================================\n"
                   << "Test 37_" << numOfEdges << '\n'
                   << "-------------------------------\n"
                   << "r = " << r << ", a= " << a << '\n'
                   << "b1= " << b1 << ", b2= " << b2 << '\n'
                   << "num of segments in circle= " << numOfEdges << '\n'
                   << "-------------------------------\n";
        if (10 == numOfEdges)
        {
            outputFile << "Theoretical matrix:\n";
            theor_ans.display(outputFile);
        }
        execTest(theor_ans, outputFile);
        outputFile << "\n===================================================\n";

        Data::clearAll();
        ViewFactor::matrix.clear();
        // Prepare for next iteration
        numOfEdges = numOfEdges * 2;
    }
}
