#include <cassert>

#include "Computing\ViewFactor.hpp"
#include "dto\SurfaceToLines.h"

namespace UnitTests
{
    void TestCrossing()
    {
        {
            Point start = {1, 0},
                  end = {1, 2},
                  fst = {0, 1},
                  snd = {2, 1};
            assert(ViewFactor::isCrossing(start, end, fst, snd));
            assert(ViewFactor::isCrossing(end, start, fst, snd));
            assert(ViewFactor::isCrossing(start, end, snd, fst));
            assert(ViewFactor::isCrossing(end, start, snd, fst));
            assert(ViewFactor::isCrossing(fst, snd, start, end));
            assert(ViewFactor::isCrossing(snd, fst, start, end));
            assert(ViewFactor::isCrossing(fst, snd, end, start));
            assert(ViewFactor::isCrossing(snd, fst, end, start));

            assert(!ViewFactor::isCrossing(start, fst, end, snd));
            assert(!ViewFactor::isCrossing(fst, start, end, snd));
            assert(!ViewFactor::isCrossing(start, fst, snd, end));
            assert(!ViewFactor::isCrossing(fst, start, snd, end));
            assert(!ViewFactor::isCrossing(end, snd, start, fst));
            assert(!ViewFactor::isCrossing(snd, end, start, fst));
            assert(!ViewFactor::isCrossing(end, snd, fst, start));
            assert(!ViewFactor::isCrossing(snd, end, fst, start));
        }
        {
            Point start = {1, 0},
                  end = {1, 2},
                  fst = {1, 1},
                  snd = {2, 1};
            assert(!ViewFactor::isCrossing(start, end, fst, snd));
            assert(!ViewFactor::isCrossing(start, fst, end, snd));
        }
        {
            Point start = {1, 1},
                  end = {1, 2},
                  fst = {1, 1},
                  snd = {2, 1};
            assert(!ViewFactor::isCrossing(start, end, fst, snd));
            assert(!ViewFactor::isCrossing(start, fst, end, snd));
        }
    }

    void TestVisibility()
    {
        CompSegment src = CompSegment(
            5, 0,
            0, 0, 0);
        CompSegment obj = CompSegment(
            0, 4,
            5, 4, 1);
        std::vector<CompSegment> barr = {
            CompSegment(
                1, 2,
                3, 3, 2)};
        assert(!ViewFactor::isVisible(src, obj, barr[0]));
        assert(!ViewFactor::isVisible(src, obj, barr));
        barr.clear();
        barr.push_back(
            CompSegment(
                3, 2,
                5, 3, 2));
        assert(ViewFactor::isVisible(src, obj, barr[0]));
        assert(ViewFactor::isVisible(src, obj, barr));
        barr[0].~CompSegment();
        barr.clear();
        barr.push_back(
            CompSegment(
                2.5, 2,
                2.5, 3, 2));
        assert(ViewFactor::isVisible(src, obj, barr[0]));
        assert(ViewFactor::isVisible(src, obj, barr));
    }

    void testSurfaceAdd()
    {
        int prevSurfNum = Data::surfNames.size();
        Surface surf = Surface({{0, 0}, {0, 1}}, "addSurface");
        assert(prevSurfNum == Data::surfNames.size() - 1);
        assert(Data::surfNames[Data::surfNames.size() - 1] == "addSurface");
        Data::clearAll();
    }
    void testSurfaceToLines()
    {
    }

    void testSurface()
    {
        testSurfaceAdd();
        testSurfaceToLines();
    }
}
