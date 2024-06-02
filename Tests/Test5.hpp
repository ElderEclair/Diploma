#pragma once

#include <vector>
#include <fstream>

#include "Computing\Matrix.h"

#include "Tests/FileFiller.h"
#include "Tests/TestExecuter.h"

#include "Data.h"
#include "Parsing\XmlCodeToPropertyTree.hpp"
#include "dto\SurfaceToLines.h"

void Test5(double x_in, double y_in, double dx, double dy, double phi)
{
    // calculate theoretical answer
    double L = 1;
    while (L <= 1024)
    {
        double x = x_in * L,
               y = y_in * L;
        Matrix theor_ans(2);
        {
            double Y = y / x,
                   dY = dy / dx,
                   sinphi = sin(phi),
                   cosphi = cos(phi);
            double znam = 1 + Y * Y - 2 * Y * cos(phi);
            double ans = Y * sinphi * sinphi * (dy / x) /
                         (2 * sqrt(znam * znam * znam));
            theor_ans.setElement(0, 1, ans);
            theor_ans.setElement(1, 0, ans / dY / Y);
        }
        // Prepare Input .svg file
        {
            std::ofstream inputFile("Input_files/Test5.svg");
            startSvgFile(inputFile);
            inputFile << "\t "
                      << "<polyline" << '\n'
                      << "\t\t "
                      << "id=" << '"' << "dA1" << '"' << '\n'
                      << "\t\t "
                      << "points=" << '"' << x + dx / 2 << ',' << 0 << ' ' << x - dx / 2 << ',' << 0 << '"' << '\n'
                      << "\t\t "
                      << "stroke=" << '"' << "black" << '"' << '\n'
                      << "\t "
                      << "/>" << '\n';
            inputFile << "\t "
                      << "<polyline" << '\n'
                      << "\t\t "
                      << "id=" << '"' << "dA2" << '"' << '\n'
                      << "\t\t "
                      << "points=" << '"' << (y - dy / 2) * cos(phi) << ',' << (y - dy / 2) * sin(phi) << ' ' << (y + dy / 2) * cos(phi) << ',' << (y + dy / 2) * sin(phi) << '"' << '\n'
                      << "\t\t "
                      << "stroke=" << '"' << "black" << '"' << '\n'
                      << "\t "
                      << "/>" << '\n';
            endSvgFile(inputFile);
        }
        // calculate practical result
        {
            std::vector<Surface> surfs;
            Parser::parseXmlFile("Input_files/Test5.svg", surfs);
            std::vector<UserSegment> tempsegm;
            for (int i = 0; i < surfs.size(); i++)
            {
                tempsegm = surfaceToLines(surfs[i], false);
                Data::lines.insert(Data::lines.end(), tempsegm.begin(), tempsegm.end());
            }
        }
        std::ofstream outputFile;
        if (1 == L)
        {
            outputFile.open("Output_files/Test5.txt");
        }
        else
        {
            outputFile.open("Output_files/Test5.txt", std::ios::app);
        }
        outputFile << "\n===================================================\n"
                   << "Test 5\n"
                   << "-------------------------------\n"
                   << "x = " << x << ", y= " << y << '\n'
                   << "dx= " << dx << " dy= " << dy << '\n'
                   << "phi= " << phi << '\n'
                   << "-------------------------------\n";
            outputFile << "Theoretical matrix:\n";
            theor_ans.display(outputFile);
        execIteration(theor_ans, outputFile, 1);
        outputFile << "\n===================================================\n";

        Data::clearAll();
        ViewFactor::matrix.clear();
        L = L * 2.;
    }
}
