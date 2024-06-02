#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <chrono>

#include "Parsing\XmlCodeToPropertyTree.hpp"

#include "dto\Surface.h"
#include "Segments\UserSegment.h"
#include "Segments\CompSegment.h"
#include "Structs\Vect.h"

#include "Data.h"

#include "Computing/ViewFactor.hpp"
#include "dto/LinesToSegments.h"
#include "dto/SurfaceToLines.h"

#include "Tests\UnitTests.hpp"

#include "Tests\IncludeTests.h"

int main()
{
    UnitTests::testSurface();
    UnitTests::TestCrossing();
    UnitTests::TestVisibility();

    //Test5(5, 5, 1, 2, PI/3);
    //Test23(5, 5, 1, PI/3);
    //Test24(5, PI/6, PI/3);
    Test25(10, 100, 80);
    /*Test29(PI/3); 
    Test32(30, 40);
    Test33(30, 50);
    Test34(30, PI/3);
    Test35(30, 20);
    Test36(30, 40, 20);
    Test37(40, 10, 30, 5);
    Test44(20, 40);
    */
    //Test29(PI/3);

    return 0;
    // std::vector<Surface> surfaces;
    // parseXmlFile("test.svg", surfaces);
    std::vector<Point> points1 = {
        {0, 0},
        {0, 3},
        {3, 3},
        {3, 0},
        {0, 0}};
    std::vector<Point> points2 = {
        {1, 1},
        {2, 1},
        {2, 2},
        {1, 2},
        {1, 1}};
    Surface surface1{points1, "Outside"};
    Surface surface2{points2, "Inside"};


    std::vector<UserSegment> tempsegm = surfaceToLines(surface1);
    Data::lines.insert(Data::lines.end(), tempsegm.begin(), tempsegm.end());
    tempsegm = surfaceToLines(surface2);
    Data::lines.insert(Data::lines.end(), tempsegm.begin(), tempsegm.end());
    Data::segments = linesToSegments(Data::lines);

    std::cout << Data::segments.size() << '\n';
    for (int i = 0; i < Data::surfArea.size(); i++)
    {
        std::cout << Data::surfArea[i] << ' ';
    }
    std::cout << '\n';
    auto start = std::chrono::system_clock::now();
    ViewFactor::display(Data::segments, std::cout);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
