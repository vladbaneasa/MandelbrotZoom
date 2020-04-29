#include "Debug.h"
#include "EngineGlut.h"
#include "Point2D.hpp"
#include "Mathematics.hpp"
#include "Render.hpp"
#include "Matrix.hpp"
#include "FileHandler.hpp"
#include <pthread.h>

FileHandler *file_man = file_man->getInstance("buffer.dat");
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv)
{
    initEngineGlut(argc, argv);

    //Dummy vars
    double x_coord, y_coord;


    Mathematics math;
    Render render(math);
    Matrix inverse_matrix;

    //Draw the fractal first
    render.PaintWithOpenmp();

    //Infinite loop to get coords from file and apply Render->Paint
    while (true)
    {
        if (FileHandler::getNotification() == true)
        {
            pthread_mutex_lock(&lock);
            //Get instance
            FileHandler *file_man = file_man->getInstance("buffer.dat");
            //Read from file
            file_man->ReadCoords(&x_coord, &y_coord);
           // watch(x_coord);
           // watch(y_coord);
            pthread_mutex_unlock(&lock);


            render.getInverseValue (x_coord, y_coord);

            render.setCenter(x_coord, y_coord);

            render.setScale(1.0);

            render.ClearScreen();
            render.PaintWithOpenmp();

            pthread_mutex_lock(&lock);
            FileHandler::Notify();
            pthread_mutex_unlock(&lock);
        }
    }

    delete file_man;

    std::cin.ignore();
    return 0;
}
 
