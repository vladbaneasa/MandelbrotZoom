#pragma once

class Matrix
{
    private:
        double __matrix[3][3];

    public:
        Matrix();
        Matrix(double matrix[3][3]);
        Matrix createInverse();
        double& accessMember(int i, int j);
        void setMember(int i, int j, double value);
};
