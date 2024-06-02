#pragma once

#include <vector>
#include <fstream>

#include "Computing\Matrix.h"

#include "Tests/FileFiller.h"
#include "Tests/TestExecuter.h"

#include "Data.h"
#include "Parsing\XmlCodeToPropertyTree.hpp"
#include "dto\SurfaceToLines.h"

void Test36(double r1, double r2, double s)
{

    // calculate theoretical answer
    Matrix theor_ans(2);
    double offset = std::max(r1, r2) * 2 + s + 20;
    {
        double R = r2 / r1,
               S = s / r1,
               C = 1 + R + S;
        double ans = 1 / (2 * PI) *
                     (PI +
                      sqrt(C * C - (R + 1) * (R + 1)) -
                      sqrt(C * C - (R - 1) * (R - 1)) +
                      (R - 1) * acos((R - 1) / C) -
                      (R + 1) * acos((R + 1) / C));
        theor_ans.setElement(0, 1, ans);
        theor_ans.setElement(1, 0, ans / R);
    }
    int numOfEdges = 10;
    while (numOfEdges < 100)
    {
        // Prepare Input .svg file
        std::string fstart = "Input_files/Test36_",
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
                inputFile << offset - s / 2 - r1 + r1 * sin(PI * 2 * j / numOfEdges) << ',' << offset - r1 * cos(PI * 2 * j / numOfEdges) << ' ';
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
                inputFile << offset + s / 2 + r2 + r2 * sin(PI * 2 * j / numOfEdges) << ',' << offset - r2 * cos(PI * 2 * j / numOfEdges) << ' ';
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
            outputFile.open("Output_files/Test36.txt");
        }
        else
        {
            outputFile.open("Output_files/Test36.txt", std::ios::app);
        }
        outputFile << "\n===================================================\n"
                   << "Test 36_" << numOfEdges << '\n'
                   << "-------------------------------\n"
                   << "r1= " << r1 << ", r2= " << r2 << '\n'
                   << "ss= " << s << '\n'
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
