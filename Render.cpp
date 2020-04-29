#include "Render.hpp"
#include "Debug.h"
#include "Mathematics.hpp"
#include "EngineGlut.h"
#include <omp.h>

Render::Render(Mathematics& math): math(math)
{
    
    delta_x = 1.75;
    delta_y = 1;
    center_x = -0.75;
    center_y = 0;
    pas = 0.0049;
    zoom = 200;
    /*
    delta_x = 1.3;
    delta_y = 1;
    center_x = -0.5;
    center_y = 0;
    pas = 0.00498;
    zoom = 200;
    */
    numberOfClicks = 0;
}

Render::~Render()
{
}
void Render::setScale(double stepToscale)
{
    double scale = pow (2.0, stepToscale);
    numberOfClicks+= stepToscale;
    zoom = zoom * scale;
    delta_x = delta_x / scale;
    delta_y = delta_y / scale;
    pas = pas / scale;
    
    //Dispersie
    int testSmooth = 12;    
    if (numberOfClicks >= testSmooth)
    {
      pas = pas /2;//- pas/ 5;
      testSmooth++;
    }
}

void Render::setCenter(double newX, double newY)
{
    center_x = newX;//0.356308;//newX;
    center_y = newY;//0.648;//newY;
}
void Render::getInverseValue(double & newX, double &newY)
{
    newX = (newX - m_Transf.accessMember(2,0)) / m_Transf.accessMember(0,0);
    newY = (newY - m_Transf.accessMember(2,1)) / m_Transf.accessMember(0,0);
}

Matrix Render::getInverse()
{
    return m_Transf.createInverse();
}

void Render::updateMatrix(int zoom, double center_x, double center_y)
{
    // m_Transf[0][0] = Matrix.__transf_matrix[1][1] = zoom;
    // m_Transf[2][0] = -center_x * zoom;
    // m_Transf[2][1] = -center_y * zoom;
    m_Transf.setMember(0,0,zoom);
    m_Transf.setMember(1,1,zoom);
    m_Transf.setMember(2,0, (-center_x * zoom));
    m_Transf.setMember(2,1, (-center_y * zoom));
}

void Render::PaintWithOpenmp()
{
    int max_iter;
    double i;
    
    watch(center_x);
    watch(delta_x);
    watch(pas);
    watch(zoom);
    watch(numberOfClicks);

    max_iter = math.getMaxIter();
    updateMatrix(zoom, center_x, center_y);
    for (i = center_x - delta_x /*-2.5f*/; i < center_x + delta_x /*1.0f*/; i += pas)
    {
        long count;
        double initial = center_y - delta_y;
        long nrPoints = 2.0*delta_y / pas +2;
#pragma omp parallel for num_threads(8)
        for (count = 0; count < nrPoints ; count++)
        {
            double j = count*pas+initial;
            Point2D point;
            point.set_x(i);
            point.set_y(j);

            int escape_iter = math.IterateInMandelbrot(point);

            
            if (escape_iter == max_iter)
            {
                point.setColor(0, 0, 0);
            }
            else
            {
                math.CalculateColor(point, escape_iter);
            }
            point.draw(m_Transf);
        }
    }
}
    
void Render::ClearScreen()
{
    EngineGlut e;
    e.drawClear();
}
