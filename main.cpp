#include <iostream>
#include <stdexcept>
#include "matrix.hpp"

const std::string ADDITION = "--add";
const std::string MULTIPLICATION = "--mult";

const std::string STRING_EXCEPTION_ZERO_ARGUMENTS = "Number of arguments = 0.";
const std::string STRING_EXCEPTION_ODD_ARGUMENTS = "Number of arguments is odd.";
const std::string STRING_EXCEPTION_INVALID_OPERATION = "Invalid operation: ";
const std::string STRING_EXCEPTION_IN_FILE = "Exception in file: ";

void print_exception_with_file(const Exception &exception, char *file_name);

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << STRING_EXCEPTION_ZERO_ARGUMENTS << std::endl;
        print_usage();
        return 1;
    }
    if (argc % 2 == 1)
    {
        std::cout << STRING_EXCEPTION_ODD_ARGUMENTS << std::endl;
        print_usage();
        return 1;
    }

    char *init_file_name = argv[1];

    try
    {
        Matrix matrix = Matrix::read_from_file(init_file_name);

        for (int i = 2; i < argc; i += 2)
        {
            std::string name_operation = argv[i];
            char *file_name = argv[i + 1];
            try
            {
                if (name_operation == ADDITION)
                {
                    matrix = matrix + Matrix::read_from_file(file_name);
                } else if (name_operation == MULTIPLICATION)
                {
                    matrix = matrix * Matrix::read_from_file(file_name);
                } else
                {
                    std::cout << STRING_EXCEPTION_INVALID_OPERATION + name_operation << std::endl;
                    print_usage();
                    return 1;
                }
            }
            catch (Exception &exception_with_file)
            {
                print_exception_with_file(exception_with_file, file_name);
                return 1;
            }
        }
        matrix.print_matrix();

    } catch (Exception &exception_with_file)
    {
        print_exception_with_file(exception_with_file, init_file_name);
        return 1;
    }
    return 0;
}

void print_exception_with_file(const Exception &exception, char *file_name)
{
    std::cout << STRING_EXCEPTION_IN_FILE << "\"" << file_name << "\"" << std::endl;
    std::cout << exception.get_message() << std::endl;
}

