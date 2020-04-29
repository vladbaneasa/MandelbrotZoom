#include "Mathematics.hpp"
#include "Point2D.hpp"
#include "Debug.h"

Mathematics::Mathematics()
{
    max_iteration = 770;
}

Mathematics::~Mathematics()
{
}

void Mathematics::SmoothColoring(Point2D &point, int iter, std::complex<double> z)
{
    // log_zn = log( x*x + y*y ) / 2
    // nu = log( log_zn / log(2) ) / log(2)
    // double log_zn = (log(z.real() * z.real() + z.imag() * z.imag()) / 2);
    // double func = log(log_zn / log(2)) / log(2);
    // int color_var = iter + 1 - func;

    // //nsmooth := n + 1 - Math.log(Math.log(zn.abs()))/Math.log(2)
    // double r = (iter + (color_var + 9) - log(log(abs(z))) / log(2)) / 256.0f;
    // double g = (iter + (color_var + 15) - log(log(abs(z))) / log(2)) / 256.0f;
    // double b = (iter + (color_var + 8.5f) - log(log(abs(z))) / log(2)) / 256.0f;

    // point.setColor(r, g, b);

//   if ( iteration < max_iteration ) {
//     // sqrt of inner term removed using log simplification rules.
//     log_zn = log( x*x + y*y ) / 2
//     nu = log( log_zn / log(2) ) / log(2)
//     // Rearranging the potential function.
//     // Dividing log_zn by log(2) instead of log(N = 1<<8)
//     // because we want the entire palette to range from the
//     // center to radius 2, NOT our bailout radius.
//     iteration = iteration + 1 - nu
//   }
//   color1 = palette[floor(iteration)]
//   color2 = palette[floor(iteration) + 1]
//   // iteration % 1 = fractional part of iteration.
//   color = linear_interpolate(color1, color2, iteration % 1)
//   plot(Px, Py, color)
//}

}

void Mathematics::CalculateColor(Point2D &point, int iter)
{

    //Bernstein Polynomials
    // int t = 5000 / iter;
    // double r = ((int)(9 * (1 - t) * t * t * t * 255)) / 256.0f;
    // double g = ((int)(15 * (1 - t) * (1 - t) * t * t * 255)) / 256.0f;
    // double b = ((int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255)) / 256.0f;

    //HSV Coloring
    // rotate the hue
    double h = (iter > 255) ? iter - 255 : iter;
    float r, g, b;

    h = (h / 256.0f) * 6;  // maps h to the range [0, 6)
    int i = std::floor(h); // i represent the setor of the colour wheel
    h -= i;                // maps h to range [0, 1)

    switch (i)
    {
    case 0: // full red, no blue, increase green
        r = 255 / 256.0f;
        b = 0;
        g = (h * 255) / 256.0f;
        break;
    case 1: // full green, no blue, decrease red
        g = 255 / 256.0f;
        b = 0;
        r = ((1 - h) * 255) / 256.0f;
        break;
    case 2: // full greeen, no red, increase blue
        g = 255 / 256.0f;
        r = 0;
        b = (h * 255) / 256.0f;
        break;
    case 3: // full blue, no red, decrease green
        b = 255 / 256.0f;
        r = 0;
        g = ((1 - h) * 255) / 256.0f;
        break;
    case 4: // full blue, no green, increase red
        b = 255 / 256.0f;
        g = 0;
        r = (h * 255) / 256.0f;
        break;
    case 5: // full red, no green, decrease blue
        r = 255 / 256.0f;
        g = 0;
        b = ((1 - h) * 255) / 256.0f;
        break;
    default:
        r = g = b = 0; /*255 / 256.0f*/
        break;
    }

    point.setColor(r, g, b);
}

int Mathematics::IterateInMandelbrot(Point2D &point)
{
    std::complex<double> z(0.0);
    std::complex<double> f(0, 0);
    std::complex<double> c(point.get_x(), point.get_y());

    int iteration = 0;

    std::complex<double> orbit_reference = z;
    int orbit_counter = 16;

    while ((iteration <= max_iteration) && (abs(z) < 2.0))
    {
        f = (z * z) + c;
        z = f;

        iteration++;

        if (orbit_reference == z)
        {
            iteration = max_iteration;
            break;
        }

        if (orbit_counter == iteration)
        {
            orbit_reference = z;

            orbit_counter += 8;
        }
    }

    //SmoothColoring(iteration, z);

    return iteration;
}

int Mathematics::getMaxIter()
{
    return max_iteration;
}

Matrix Mathematics::ComputeInverseMatrixCoords(double matrix[3][3], int zoom, double &x_coord, double &y_coord)
{

    unsigned long long det = zoom * zoom;
    watch(det);
    matrix[0][0] = (float)(1.0f / det) * zoom;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[1][0] = 0;
    matrix[1][1] = (float)(1.0f / det) * zoom;
    matrix[1][2] = 0;
    matrix[2][0] = (float)(1.0f / det) * (-1) * (x_coord * zoom);
    matrix[2][1] = (float)(1.0f / det) * (-1) * (y_coord * zoom);
    matrix[2][2] = (float)(1.0f / det) * zoom * zoom;

    double newX = (x_coord * matrix[0][0]) + (y_coord * matrix[1][0]) + matrix[2][0];
    double newY = (x_coord * matrix[0][1]) + (y_coord * matrix[1][1]) + matrix[2][1];

    x_coord = newX;
    y_coord = newY;

    Matrix invers_matrix(matrix);

    return invers_matrix;
}

// TransformationMatrix Mathematics::MatrixTransformation(int zoom, float center_x, float center_y)
// {
//     TransformationMatrix Matrix;
//     Matrix.init();

//     Matrix.__transf_matrix[0][0] = Matrix.__transf_matrix[1][1] = zoom;
//     Matrix.__transf_matrix[2][0] = -center_x * zoom;
//     Matrix.__transf_matrix[2][1] = -center_y * zoom;

//     return Matrix;
// }

// void Mathematics::InverseMatrixTransformation(TransformationMatrix& Matrix, int zoom, float x, float y)
// {

//     unsigned long long det = zoom * zoom;
//     watch(det);

//     Matrix.__transf_matrix[0][0] = (float)(1.0f/det) * (zoom - y);
//     Matrix.__transf_matrix[0][1] = 0;
//     Matrix.__transf_matrix[0][2] = 0;
//     Matrix.__transf_matrix[1][0] = 0;
//     Matrix.__transf_matrix[1][1] = (float)(1.0f/det) * zoom;
//     Matrix.__transf_matrix[1][2] = 0;
//     Matrix.__transf_matrix[2][0] = (float)(1.0f/det) * (-1) * x * zoom;
//     Matrix.__transf_matrix[2][1] = (float)(1.0f/det) * (-1) * y * zoom;
//     Matrix.__transf_matrix[2][2] = (double)(1.0f/det) * zoom * zoom;

//     watch(Matrix.__transf_matrix[0][0]);
//     watch(Matrix.__transf_matrix[0][1]);
//     watch(Matrix.__transf_matrix[0][2]);
//     watch(Matrix.__transf_matrix[1][0]);
//     watch(Matrix.__transf_matrix[1][1]);
//     watch(Matrix.__transf_matrix[1][2]);
//     watch(Matrix.__transf_matrix[2][0]);
//     watch(Matrix.__transf_matrix[2][1]);
//     watch(Matrix.__transf_matrix[2][2]);

// }
