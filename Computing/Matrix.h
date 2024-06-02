#pragma once
#include <vector>
#include <stdexcept>

class Matrix
{
private:
    std::vector<std::vector<double>> matrix;
    int xSize, ySize;

public:
    Matrix(int xSize, int ySize);
    Matrix(int size);
    ~Matrix();
    double getElement(int x, int y) const;
    void setElement(int x, int y, double value);
    void addToElement(int x, int y, double value);
    int getSize() const;
    void resize(int value);
    void nullify();
    void clear();
    void display(std::ostream &outputStream);
    void displayForExcel(std::ostream &outputStream);
};

Matrix::Matrix(int xSize, int ySize)
{
    matrix.resize(xSize);
    for (int i = 0; i < xSize; i++)
    {
        matrix[i].resize(ySize, 0);
    }
    this->xSize = xSize;
    this->ySize = ySize;
}

Matrix::Matrix(int size)
{
    matrix.resize(size);
    for (int i = 0; i < size; i++)
    {
        matrix[i].resize(size, 0);
    }
    xSize = ySize = size;
}

Matrix::~Matrix()
{
}

double Matrix::getElement(int x, int y) const
{
    return matrix[x][y];
}

void Matrix::setElement(int x, int y, double value)
{
    matrix[x][y] = value;
}

void Matrix::addToElement(int x, int y, double value)
{
    if (x > xSize || y > ySize)
    {
        throw std::runtime_error("Выход за пределы матрицы!");
    }
    matrix[x][y] += value;
}

int Matrix::getSize() const
{
    if (xSize != ySize)
    {
        throw std::runtime_error("Матрица не квадратная!");
    }
    return xSize;
}

void Matrix::resize(int value)
{
    matrix.resize(value);
    for (int i = 0; i < value; i++)
    {
        if (i >= xSize)
        {
            matrix[i].resize(value, 0);
        }
        else
        {
            matrix[i].resize(value);
        }
    }
    xSize = ySize = value;
}

void Matrix::nullify()
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            matrix[i][j] = 0.;
        }
    }
}

void Matrix::clear()
{
    matrix.clear();
}

void Matrix::display(std::ostream &outputStream)
{
    outputStream << std::fixed;

    int size = Data::surfNames.size();

    // Find length of longest name
    int maxLength = 7;
    for (int i = 0; i < size; i++)
    {
        maxLength = std::max(maxLength, (int)Data::surfNames[i].size());
    }
    // Headers
    outputStream << "\tobj:";
    for (int i = 0; i <= maxLength / 8; i++)
    {
        outputStream << '\t';
    }
    for (int i = 0; i < size; i++)
    {
        int length = Data::surfNames[i].size();
        if (length > 13)
        {
            for (int j = 0; j < 12; j++)
            {
                outputStream << Data::surfNames[i][j];
            }
            outputStream << "..\t";
            continue;
        }
        if (length < 8)
        {
            outputStream << Data::surfNames[i] << "\t\t";
            continue;
        }
        outputStream << Data::surfNames[i] << '\t';
    }
    outputStream << "\nsrc\n''\n";
    // Matrix
    for (int i = 0; i < size; i++)
    {
        outputStream << Data::surfNames[i];
        outputStream << '\t';
        for (int j = 0; j <= maxLength / 8 - Data::surfNames[i].size() / 8; j++)
        {
            outputStream << '\t';
        }
        double sum = 0.;
        for (int j = 0; j < size; j++)
        {
            outputStream << matrix[i][j] << '\t';
            //sum += matrix[i][j];
        }
        //outputStream << "\tsum=" << sum ;
        outputStream << '\n';
    }
}

void Matrix::displayForExcel(std::ostream &outputStream)
{
    outputStream << std::fixed;

    int size = Data::surfNames.size();
    for (int i = 0; i < size; i++)
    {
        outputStream << '\t';
        for (int j = 0; j < size; j++)
        {
            outputStream << matrix[i][j] << '\t';
        }
    }
    outputStream << '\n';
}
