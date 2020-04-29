#pragma once
#include "Point2D.hpp"
#include "Matrix.hpp"
#include <iostream>
#include <complex>
#include <cmath>



class Mathematics
{

  public:
    Mathematics();
    ~Mathematics();
    int IterateInMandelbrot(Point2D &point);
    int getMaxIter();

    void CalculateColor(Point2D &point, int iter);
    void SmoothColoring(Point2D &point, int iter, std::complex<double> z);
    Matrix ComputeInverseMatrixCoords(double matrix[][3], int zoom, double& x_coord, double& y_coord);
    
  private:
   int max_iteration;


};
