#ifndef POINT2D_H
#define POINT2D_H

#include "Matrix.hpp"

class Point2D
{
    public:
        Point2D();
        Point2D(float x, float y, float = 0.0f, float = 0.0f, float = 0.0f);
        ~Point2D();

        void draw();
        void draw(Matrix matrix);

        void set_x(float x);
        float get_x();

        void set_y(float y);
        float get_y();

        void setColor(float r, float g, float b);


    private:
        float x;
        float y;
        float r, g, b;


};

#endif // POINT2D_H
