#include <iostream>
#include <math.h>
#include "Point2D.hpp"
#include "EngineGlut.h"


Point2D::Point2D()
{
    this->x = this->y = 0;
    this->r = this->g = this->b = 0.0f;
}

Point2D::Point2D(float x, float y, float r, float g, float b)
{
    this->x = x;
    this->y = y;
    this->r = r;
    this->g = g;
    this->b = b;
}

Point2D::~Point2D()
{
}

void Point2D::draw()
{
    EngineGlut engine;
    engine.drawPoint(this->x, this->y, this->r, this->g, this->b);
}
void Point2D::draw(Matrix matrix)
{
    EngineGlut engine;
    float x_draw = (this->x * matrix.accessMember(0,0)) + (this->y * matrix.accessMember(1, 0)) + matrix.accessMember(2,0);
    float y_draw = (this->x * matrix.accessMember(0,1)) + (this->y * matrix.accessMember(1, 1)) + matrix.accessMember(2,1);
    // float x_draw = this->x * matrix[0][0] + this->y * matrix[1][0] + matrix[2][0];
    // float y_draw = this->x * matrix[0][1] + this->y * matrix[1][1] + matrix[2][1];
    engine.drawPoint(x_draw, y_draw, this->r, this->g, this->b);
    for (int i=1; i<0; i++)
    {
        engine.drawPoint(x_draw+i, y_draw, this->r, this->g, this->b);
        engine.drawPoint(x_draw, y_draw+i, this->r, this->g, this->b);
    }
}
void Point2D::set_x(float x)
{
    this->x = x;
}

float Point2D::get_x()
{
    return this->x;
}

void Point2D::set_y(float y)
{
    this->y = y;
}

float Point2D::get_y()
{
    return this->y;
}

void Point2D::setColor(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}
