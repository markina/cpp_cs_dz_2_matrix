#pragma once

const std::string USAGE = "USAGE: ./main file_name_with_initial_matrix [[--add | --mult] file_name_with_matrix]*";

class Matrix
{
private:
    double **m_values;
    int m_row;
    int m_column;
public:
    static Matrix read_from_file(const char *file_name);

    Matrix operator+(const Matrix &argument);

    Matrix operator*(const Matrix &argument);

    Matrix &operator=(Matrix other_matrix);

    void print_matrix() const;

    Matrix(int row, int column);

    Matrix(const Matrix &other_matrix);

    ~Matrix();
};

struct Exception
{
    virtual std::string get_message() const = 0;
};

struct ExceptionSizeOfAddition : Exception
{
    std::string get_message() const;
};

struct ExceptionSizeOfMultiplication : Exception
{
    std::string get_message() const;
};

struct ExceptionOpenFile : Exception
{
    std::string get_message() const;
};

void print_usage();
