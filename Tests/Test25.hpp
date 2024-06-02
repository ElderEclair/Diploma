#pragma once

#include <vector>
#include <fstream>

#include "Computing\Matrix.h"

#include "Tests/FileFiller.h"
#include "Tests/TestExecuter.h"

#include "Data.h"
#include "Parsing\XmlCodeToPropertyTree.hpp"
#include "dto\SurfaceToLines.h"

void Test25(double r_in, double a_in, double b_in)
{
    double L = 5;
    for (int i = 0; i < 6; i++)
    {
        double r = r_in * L,
               a = a_in * L,
               b = b_in * L;
        int numOfEdges = 20;
        // calculate theoretical answer
        Matrix theor_ans(2);
        double dx = 1, offset = 20;
        {
            double A = a / r,
                   B = b / r;
            double ans = A / (A * A + B * B);
            theor_ans.setElement(0, 1, ans);
            theor_ans.setElement(1, 0, ans * dx / (2 * PI * r));
        }
        // Prepare Input .svg file
        std::string fstart = "Input_files/Test25_",
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
                      << "id=" << '"' << "dA1" << '"' << '\n'
                      << "\t\t "
                      // Coords
                      << "points=" << '"' << offset + dx / 2 << ',' << offset + 0 << ' ' << offset - dx / 2 << ',' << offset << '"' << '\n'
                      << "\t\t "
                      << "stroke=" << '"' << "black" << '"' << '\n'
                      << "\t "
                      << "/>" << '\n';
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
                inputFile << offset + b + r * sin(PI * 2 * j / numOfEdges) << ',' << offset + b - r * cos(PI * 2 * j / numOfEdges) << ' ';
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
        if (5 == L)
        {
            outputFile.open("Output_files/Test25.txt");
        }
        else
        {
            outputFile.open("Output_files/Test25.txt", std::ios::app);
        }
        outputFile << "\n===================================================\n"
                   << "Test 25_" << numOfEdges << '\n'
                   << "-------------------------------\n"
                   << "a = " << a << ", b= " << b << '\n'
                   << "r= " << r << '\n'
                   << "num of segments in circle= " << numOfEdges << '\n'
                   << "-------------------------------\n";
        outputFile << "Theoretical matrix:\n";
        theor_ans.display(outputFile);
        execIteration(theor_ans, outputFile, 1);
        outputFile << "\n===================================================\n";

        Data::clearAll();
        ViewFactor::matrix.clear();
        // Prepare for next iteration
        L *= 2;
    }
}
