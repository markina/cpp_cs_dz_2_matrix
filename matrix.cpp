#include <fstream>
#include <stdexcept>
#include "matrix.hpp"

Matrix Matrix::read_from_file(const char *file_name)
{
    std::ifstream in(file_name);
    if (in.fail())
    {
        throw ExceptionOpenFile();
    }
    int N, M;
    in >> N >> M;
    Matrix matrix(N, M);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            in >> matrix.values[i][j];
        }
    }
    return matrix;
}

Matrix Matrix::operator+(const Matrix &argument)
{
    if (N != argument.N || M != argument.M)
    {
        throw ExceptionSizeOfAddition();
    }

    Matrix result = Matrix(N, M);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            result.values[i][j] = values[i][j] + argument.values[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &argument)
{
    if (M != argument.N)
    {
        throw ExceptionSizeOfMultiplication();
    }

    Matrix result = Matrix(N, argument.M);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < argument.M; ++j)
        {
            result.values[i][j] = 0;
            for (int k = 0; k < M; ++k)
            {
                result.values[i][j] += values[i][k] * argument.values[k][j];
            }
        }
    }
    return result;
}

void Matrix::print_matrix() const
{
    std::cout << N << " " << M << std::endl;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            std::cout << values[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix &Matrix::operator=(Matrix other_matrix)
{
    std::swap(N, other_matrix.N);
    std::swap(M, other_matrix.M);
    std::swap(values, other_matrix.values);
    return *this;
}

Matrix::Matrix(int N, int M) : N(N), M(M)
{
    values = new double *[N];
    for (int i = 0; i < N; i++)
    {
        values[i] = new double[M];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < N; ++i)
    {
        delete[] values[i];
    }
    delete[] values;
}

Matrix::Matrix(const Matrix &other_matrix) : N(other_matrix.N), M(other_matrix.M)
{
    values = new double *[N];
    for (int i = 0; i < N; ++i)
    {
        values[i] = new double[M];
        for (int j = 0; j < M; ++j)
        {
            values[i][j] = other_matrix.values[i][j];
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


