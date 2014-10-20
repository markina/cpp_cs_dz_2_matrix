#include <fstream>
#include <stdexcept>
#include "matrix.hpp"
#include <iostream>
#include <cstring>

Matrix Matrix::read_from_file(const char *file_name)
{
    std::ifstream in(file_name);
    if (in.fail())
    {
        throw ExceptionOpenFile();
    }
    int m_row, m_column;
    in >> m_row >> m_column;
    Matrix matrix(m_row, m_column);
    for (int i = 0; i < m_row; ++i)
    {
        for (int j = 0; j < m_column; ++j)
        {
            in >> matrix.m_values[i][j];
        }
    }
    return matrix;
}

Matrix Matrix::operator+(const Matrix &argument)
{
    if (m_row != argument.m_row || m_column != argument.m_column)
    {
        throw ExceptionSizeOfAddition();
    }

    Matrix result = Matrix(m_row, m_column);
    for (int i = 0; i < m_row; ++i)
    {
        for (int j = 0; j < m_column; ++j)
        {
            result.m_values[i][j] = m_values[i][j] + argument.m_values[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &argument)
{
    if (m_column != argument.m_row)
    {
        throw ExceptionSizeOfMultiplication();
    }

    Matrix result = Matrix(m_row, argument.m_column);
    for (int i = 0; i < m_row; ++i)
    {
        for (int j = 0; j < argument.m_column; ++j)
        {
            result.m_values[i][j] = 0;
            for (int k = 0; k < m_column; ++k)
            {
                result.m_values[i][j] += m_values[i][k] * argument.m_values[k][j];
            }
        }
    }
    return result;
}

void Matrix::print_matrix() const
{
    std::cout << m_row << " " << m_column << std::endl;
    for (int i = 0; i < m_row; ++i)
    {
        for (int j = 0; j < m_column; ++j)
        {
            std::cout << m_values[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix &Matrix::operator=(Matrix other_matrix)
{
    std::swap(m_row, other_matrix.m_row);
    std::swap(m_column, other_matrix.m_column);
    std::swap(m_values, other_matrix.m_values);
    return *this;
}

Matrix::Matrix(int row, int column) : m_row(row), m_column(column)
{
    m_values = new double *[m_row];
    for (int i = 0; i < m_row; ++i)
    {
        m_values[i] = new double[m_column];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < m_row; ++i)
    {
        delete[] m_values[i];
    }
    delete[] m_values;
}

Matrix::Matrix(const Matrix &other_matrix) : m_row(other_matrix.m_row), m_column(other_matrix.m_column)
{
    m_values = new double *[m_row];
    for (int i = 0; i < m_row; ++i)
    {
        m_values[i] = new double[m_column];
        for (int j = 0; j < m_column; ++j)
        {
            m_values[i][j] = other_matrix.m_values[i][j];
        }
    }
}

void print_usage()
{
    std::cout << USAGE << std::endl;
}


std::string ExceptionSizeOfAddition::get_message() const
{
    return "Invalid size matrix in addition in file. The number of columns and rows on first matrix is not the same as the number of columns and rows of second matrix.";
}

std::string ExceptionSizeOfMultiplication::get_message() const
{
    return "Invalid size matrix in multiplication in file. The number of columns on first matrix is not the same as the number of rows of second matrix.";
}

std::string ExceptionOpenFile::get_message() const
{
    return "File not found in directory";
}


