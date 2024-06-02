#pragma once

#include <vector>
#include <fstream>

#include "Computing\Matrix.h"

#include "Tests/FileFiller.h"
#include "Tests/TestExecuter.h"

#include "Data.h"
#include "Parsing\XmlCodeToPropertyTree.hpp"
#include "dto\SurfaceToLines.h"

void Test29(double phi, int L = 100)
{
    const int usrL = L;
    while (L < 200000)
    {
        // calculate theoretical answer
        Matrix theor_ans(2);
        double dx = 5,
               h = 200,
               r = 10;
        {
            double ans = 0.5 * (1 + cos(phi));
            theor_ans.setElement(0, 1, ans);
            theor_ans.setElement(1, 0, ans * dx / L);
        }
        // Prepare Input .svg file
        std::string fstart = "Input_files/Test29_",
                    fend = ".svg";
        std::string fstr = fstart + std::to_string(L) + fend;
        char *filename = &fstr[0];
        {
            std::ofstream inputFile(filename);
            startSvgFile(inputFile);
            double ang1 = phi - asin(dx / (2 * r)),
                   ang2 = phi + asin(dx / (2 * r));
            inputFile << "\t "
                      << "<polyline" << '\n'
                      << "\t\t "
                      // id
                      << "id=" << '"' << "dA1" << '"' << '\n'
                      << "\t\t "
                      // Coords
                      << "points=" << '"' << L / 2 + r * sin(ang1) << ',' << h - r * cos(ang1) << ' ' << L / 2 + r * sin(ang2) << ',' << h - r * cos(ang2) << '"' << '\n'
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
                      << "points=" << '"' << L << ',' << 0 << ' ' << 0 << ',' << 0 << '"' << '\n'
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
        if (usrL == L)
        {
            outputFile.open("Output_files/Test29.txt");
        }
        else
        {
            outputFile.open("Output_files/Test29.txt", std::ios::app);
        }
        outputFile << "\n===================================================\n"
                   << "Test 29_" << L << '\n'
                   << "-------------------------------\n"
                   << "phi = " << phi << '\n'
                   << "dx= " << dx << ", r= " << r << ", h= " << h << '\n'
                   << "-------------------------------\n";
        if (usrL == L)
        {
            outputFile << "Theoretical matrix:\n";
            theor_ans.display(outputFile);
        }
        execTest(theor_ans, outputFile);
        outputFile << "\n===================================================\n";

        Data::clearAll();
        ViewFactor::matrix.clear();
        // Prepare for next iteration
        L *= 2;
    }
}
