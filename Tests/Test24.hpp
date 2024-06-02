#pragma once

#include <vector>
#include <fstream>

#include "Computing\Matrix.h"

#include "Tests/FileFiller.h"
#include "Tests/TestExecuter.h"

#include "Data.h"
#include "Parsing\XmlCodeToPropertyTree.hpp"
#include "dto\SurfaceToLines.h"

void Test24(double dx, double phi1, double phi2)
{
    // calculate theoretical answer
    double l1 = dx * 2;
    double l2 = dx * 2;
    for (int i = 0; i < 5; i++)
    {
        l1 *= 2;
        l2 *= 2;
        Matrix theor_ans(2);
        {
            double A2 = sqrt(l1 * l1 + l2 * l2 - 2 * l1 * l2 * cos(phi2 - phi1));
            double ans = 0.5 * (sin(phi2) - sin(phi1));
            theor_ans.setElement(0, 1, ans);
            theor_ans.setElement(1, 0, ans * dx / A2);
        }
        // Prepare Input .svg file
        std::string fstart = "Input_files/Test24_",
                    fend = ".svg";
        std::string fstr = fstart + std::to_string(i) + fend;
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
                      << "points=" << '"' << dx << ',' << 0 << ' ' << 0 << ',' << 0 << '"' << '\n'
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
                      << "points=" << '"' << l1 * sin(phi1) << ',' << l1 * cos(phi1) << ' ' << l2 * sin(phi2) << ',' << l2 * cos(phi2) << '"' << '\n'
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
        if (0 == i)
        {
            outputFile.open("Output_files/Test24.txt");
        }
        else
        {
            outputFile.open("Output_files/Test24.txt", std::ios::app);
        }
        outputFile << "\n===================================================\n"
                   << "Test 24_" << i << '\n'
                   << "-------------------------------\n"
                   << "dx= " << dx << '\n'
                   << "phi1= " << phi1 << ", phi2= " << phi2 << '\n'
                   << "l1= " << l1 << ", l2= " << l2 << '\n'
                   << "-------------------------------\n";
        outputFile << "Theoretical matrix:\n";
        theor_ans.display(outputFile);
        execIteration(theor_ans, outputFile, 1);
        outputFile << "\n===================================================\n";

        Data::clearAll();
        ViewFactor::matrix.clear();

        l1 *= 2;
        l2 *= 2;
    }
}
