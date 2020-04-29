#pragma once
#include "Point2D.hpp"
#include "Mathematics.hpp"
#include "Matrix.hpp"

class Render
{
    public:
        Render(Mathematics& math);
        ~Render();
        void ClearScreen();
        void setScale(double scale = 2);
        void setCenter(double, double);
        void getInverseValue(double & newX, double &newY);
        void PaintWithOpenmp();      
        Matrix getInverse();
        void updateMatrix(int zoom, double center_x, double center_y);
    
    private:
        double delta_x;
        double delta_y;
        double center_x;
        double center_y;
        double pas;
        double zoom;
        int numberOfClicks;
        Matrix m_Transf;
        Mathematics& math;

};  
