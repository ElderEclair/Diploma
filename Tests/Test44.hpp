#pragma once

#include <vector>
#include <fstream>

#include "Computing\Matrix.h"

#include "Tests/FileFiller.h"
#include "Tests/TestExecuter.h"

#include "Data.h"
#include "Parsing\XmlCodeToPropertyTree.hpp"
#include "dto\SurfaceToLines.h"

void Test44(double r_in, double r_out)
{

    // calculate theoretical answer
    Matrix theor_ans(2);
    double offset = 20 + r_out;
    {
        double R = r_out / r_in;
        double ans = 1 - 1 / R;
        theor_ans.setElement(1, 1, ans);
        theor_ans.setElement(1, 0, 1 - ans);
        theor_ans.setElement(0, 1, 1);
    }
    int numOfEdges = 10;
    while (numOfEdges < 100)
    {
        // Prepare Input .svg file
        std::string fstart = "Input_files/Test44_",
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
                      << "id=" << '"' << "inner circle" << '"' << '\n'
                      << "\t\t "
                      // Coords
                      << "points=" << '"';
            for (int j = 0; j <= numOfEdges; j++)
            {
                inputFile << offset + r_in * sin(PI * 2 * j / numOfEdges) << ',' << offset - r_in * cos(PI * 2 * j / numOfEdges) << ' ';
            }
            inputFile << '"' << '\n'
                      << "\t\t "
                      << "stroke=" << '"' << "black" << '"' << '\n'
                      << "\t\t "
                      << "fill=" << '"' << "none" << '"' << '\n'
                      << "\t "
                      << "/>" << '\n';
            inputFile << "\t "
                      << "<polyline" << '\n'
                      << "\t\t "
                      // id
                      << "id=" << '"' << "outter circle" << '"' << '\n'
                      << "\t\t "
                      // Coords
                      << "points=" << '"';
            for (int j = 0; j <= numOfEdges; j++)
            {
                inputFile << offset -  r_out * sin(PI * 2 * j / numOfEdges) << ',' << offset - r_out * cos(PI * 2 * j / numOfEdges) << ' ';
            }
            inputFile << '"' << '\n'
                      << "\t\t "
                      << "stroke=" << '"' << "black" << '"' << '\n'
                      << "\t\t "
                      << "fill=" << '"' << "none" << '"' << '\n'
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
            outputFile.open("Output_files/Test44.txt");
        }
        else
        {
            outputFile.open("Output_files/Test44.txt", std::ios::app);
        }
        outputFile << "\n===================================================\n"
                   << "Test 44_" << numOfEdges << '\n'
                   << "-------------------------------\n"
                   << "inner radius= " << r_in << ", outer radius= " << r_out << '\n'
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
