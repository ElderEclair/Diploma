#pragma once

#include <vector>
#include <fstream>

#include "Computing\Matrix.h"

#include "Tests/FileFiller.h"
#include "Tests/TestExecuter.h"

#include "Data.h"
#include "Parsing\XmlCodeToPropertyTree.hpp"
#include "dto\SurfaceToLines.h"

void Test35(double r, double s)
{

    // calculate theoretical answer
    Matrix theor_ans(2);
    double offset = r * 2 + s + 20;
    {
        double X = 1 + s / (2 * r);
        double ans = 1 / PI * (asin(1 / X) + sqrt(X * X - 1) - X);
        theor_ans.setElement(0, 1, ans);
        theor_ans.setElement(1, 0, ans);
    }
    int numOfEdges = 10;
    while (numOfEdges < 100)
    {
        // Prepare Input .svg file
        std::string fstart = "Input_files/Test35_",
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
                      << "id=" << '"' << "left circle" << '"' << '\n'
                      << "\t\t "
                      // Coords
                      << "points=" << '"';
            for (int j = 0; j <= numOfEdges; j++)
            {
                inputFile << offset - s / 2 - r + r * sin(PI * 2 * j / numOfEdges) << ',' << offset - r * cos(PI * 2 * j / numOfEdges) << ' ';
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
                      << "id=" << '"' << "right circle" << '"' << '\n'
                      << "\t\t "
                      // Coords
                      << "points=" << '"';
            for (int j = 0; j <= numOfEdges; j++)
            {
                inputFile << offset + s / 2 + r + r * sin(PI * 2 * j / numOfEdges) << ',' << offset - r * cos(PI * 2 * j / numOfEdges) << ' ';
            }
            inputFile << '"' << '\n'
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
            outputFile.open("Output_files/Test35.txt");
        }
        else
        {
            outputFile.open("Output_files/Test35.txt", std::ios::app);
        }
        outputFile << "\n===================================================\n"
                   << "Test 35_" << numOfEdges << '\n'
                   << "-------------------------------\n"
                   << "r= " << r << ", s= " << s << '\n'
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
