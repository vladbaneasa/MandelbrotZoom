#include "Matrix.hpp"
#include "Mathematics.hpp"
#include "Debug.h"


Matrix::Matrix()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (i == j)
                __matrix[i][j] = 1;
            else
                __matrix[i][j] = 0;
            
}

Matrix::Matrix(double matrix[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            this->__matrix[i][j] = matrix[i][j];
}


Matrix Matrix::createInverse()
{
    Matrix inverse;
    return inverse;
}

double& Matrix::accessMember(int i, int j)
{
    return this->__matrix[i][j];
}

void Matrix::setMember(int i, int j, double value)
{
    this->__matrix[i][j] = value;   
}
