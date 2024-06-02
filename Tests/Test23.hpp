#pragma once

#include <vector>
#include <fstream>

#include "Computing\Matrix.h"

#include "Tests/FileFiller.h"
#include "Tests/TestExecuter.h"

#include "Data.h"
#include "Parsing\XmlCodeToPropertyTree.hpp"
#include "dto\SurfaceToLines.h"

void Test23(double x_in, double l_in, double dx, double phi)
{
    double L = 1;
    while (L <= 1024)
    {
        double x = x_in * L,
               l = l_in * L;
        // calculate theoretical answer
        Matrix theor_ans(2);
        {
            double X = x / l,
                   dX = dx / l,
                   cosphi = cos(phi);
            double znam = 1 + X * X - 2 * X * cosphi;
            double ans = 0.5 +
                         (cosphi - X) /
                             (2 * sqrt(znam));
            theor_ans.setElement(0, 1, ans);
            theor_ans.setElement(1, 0, ans * dX);
        }
        // Prepare Input .svg file
        {
            std::ofstream inputFile("Input_files/Test23.svg");
            startSvgFile(inputFile);
            inputFile << "\t "
                      << "<polyline" << '\n'
                      << "\t\t "
                      // id
                      << "id=" << '"' << "dA1" << '"' << '\n'
                      << "\t\t "
                      // Coords
                      << "points=" << '"' << x + dx / 2 << ',' << 0 << ' ' << x - dx / 2 << ',' << 0 << '"' << '\n'
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
                      << "points=" << '"' << 0 << ',' << 0 << ' ' << l * cos(phi) << ',' << l * sin(phi) << '"' << '\n'
                      << "\t\t "
                      << "stroke=" << '"' << "black" << '"' << '\n'
                      << "\t "
                      << "/>" << '\n';
            endSvgFile(inputFile);
        }
        // calculate practical result
        {
            std::vector<Surface> surfs;
            Parser::parseXmlFile("Input_files/Test23.svg", surfs);
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
            outputFile.open("Output_files/Test23.txt");
        }
        else
        {
            outputFile.open("Output_files/Test23.txt", std::ios::app);
        }
        outputFile << "\n===================================================\n"
                   << "Test 23\n"
                   << "-------------------------------\n"
                   << "x = " << x << ", l= " << l << '\n'
                   << "dx= " << dx << '\n'
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
