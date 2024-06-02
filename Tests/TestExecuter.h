#pragma once

#include <iostream>
#include <chrono>

#include "Data.h"
#include "Computing\Matrix.h"

#include "dto/LinesToSegments.h"
#include "Computing\ViewFactor.hpp"

void calcRelErr(Matrix &err, Matrix &theorAns);
void execIteration(Matrix &theorAns, std::ostream &out, int subSegms);

void execTest(Matrix &theorAns, std::ostream &out)
{
    int subSegms = 1;
    do
    {
        execIteration(theorAns, out, subSegms);
        // Prepare for new iteration
        subSegms *= 2;
        Data::segments = linesToSegments(Data::lines, subSegms);
    } while (Data::segments.size() <= 1000);
}

void execIteration(Matrix &theorAns, std::ostream &out, int subSegms)
{
    if (Data::segments.size() == 0)
    {
        Data::segments = linesToSegments(Data::lines, subSegms);
    }
    auto lines = &Data::lines;
    auto segments = &Data::segments;
    Matrix err(theorAns.getSize());
    // Iterate
    out << "\n-------------------------------\n"
        << "Num of computing segments:\t" << Data::segments.size() << "\n";
    auto start = std::chrono::system_clock::now();
    ViewFactor::compute(Data::segments);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    out << "elapsed time:\t" << elapsed_seconds.count() << "\ts\n";
    out << "\nCalculated matrix:\n";
    ViewFactor::matrix.display(out);

    // Compare results
    calcRelErr(err, theorAns);
    out << "\nRelative Error:\n\t\t\t\t\t\t" << Data::segments.size() << '\t' << elapsed_seconds.count() << "\t\t";
    err.displayForExcel(out);
    out << "-------------------------------\n";
    Data::segments.clear();
    ViewFactor::matrix.nullify();
}

void calcRelErr(Matrix &err, Matrix &theorAns)
{
    int size = err.getSize();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            double prEl = theorAns.getElement(i, j);
            if (prEl == 0)
            {
                err.setElement(i, j, 0);
                continue;
            }
            err.setElement(i, j,
                           std::abs(prEl - ViewFactor::matrix.getElement(i, j)) / prEl);
        }
    }
}
