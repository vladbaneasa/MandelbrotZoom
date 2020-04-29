#include "GlutDrawing.h"
#include "GlutData.h"

#ifndef LINUX_PLATFORM
#ifndef MAC_PLATFORM
#include <windows.h>
#endif
#endif

#include <stdlib.h>

#ifdef MAC_PLATFORM
//use native GLUT and openGL from mac
#include <GLUT/glut.h>
#include <OpenGL/glu.h>

#else
#include <GL/freeglut.h>
#include <GL/glu.h>
#endif

#include "Debug.h"
#include <pthread.h>

#include "FileHandler.hpp"

FileHandler *FileHandler::instance = nullptr;

FileHandler *file_man = file_man->getInstance("buffer.dat");

void drawGlut()
{

	glClear(GL_COLOR_BUFFER_BIT); // Clear display window

	//Draw Points
	glBegin(GL_POINTS);
	pthread_mutex_lock(&lock);
	std::list<__Point2D> pointList = GlutData::getInstance()->getPoints();
	pthread_mutex_unlock(&lock);

	std::list<__Point2D>::iterator itr;

	for (itr = pointList.end(); itr != pointList.begin(); --itr)
	{
		glColor3f(itr->R, itr->G, itr->B);
		glVertex2i(itr->X, itr->Y);
	}
	glEnd();

	//Draw Lines
	glBegin(GL_LINES);
	pthread_mutex_lock(&lock);
	pointList = GlutData::getInstance()->getLines();
	pthread_mutex_unlock(&lock);

	for (itr = pointList.begin(); itr != pointList.end(); itr++)
		glVertex2i(itr->X, itr->Y);
	glEnd();

	//Draw Triangles
	glBegin(GL_TRIANGLES);
	pthread_mutex_lock(&lock);
	pointList = GlutData::getInstance()->getTriangles();
	pthread_mutex_unlock(&lock);

	for (itr = pointList.begin(); itr != pointList.end(); itr++)
	{
		glColor3f(itr->R, itr->G, itr->B);
		glVertex2i(itr->X, itr->Y);
	}
	glEnd();

	// Process all OpenGL routines as quickly as possible
	glFlush();
	glutSwapBuffers();
}

void mouseEvent(int button, int state, int x, int y)
{

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON)
	{
		// when the button is released
		if (state == GLUT_UP)
		{
			
			x = x - 400;
			y = 300 - y;			 

	//		watch(x);
//			watch(y);

			pthread_mutex_lock(&lock);
			file_man = file_man->getInstance("buffer.dat");
			file_man->WriteCoords(x, y);
			if (FileHandler::getNotification() == false)
				FileHandler::Notify();
			else
				std::cout << "error" << std::endl;
			pthread_mutex_unlock(&lock);
		}
	}
}

void *startGluthThread(void *ptr)
{
	// Set display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Set top - left display window position.
	glutInitWindowPosition(100, 100);

	// Set display window width and height
	glutInitWindowSize(WIN_MAX_X, WIN_MAX_Y);

	// Create display window with the given title
	glutCreateWindow("Mandelbrot");

	// Execute initialization procedure
	//init();

	// Set display window color to as glClearColor(R,G,B,Alpha)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set projection parameters.
	glMatrixMode(GL_PROJECTION);

	// Set 2D Transformation as gluOrtho2D(Min Width, Max Width, Min Height, Max Height)
	gluOrtho2D(0.0, 800, 0.0, 600);

	glutMouseFunc(mouseEvent);

	// Send graphics to display window
	glutDisplayFunc(drawGlut);

	glutIdleFunc(drawGlut);

	// Display everything and wait.
	glutMainLoop();
	pthread_exit(NULL);
}

void initGlutDrawing(int argc, char **argv)
{
	// Initialize GLUT
	glutInit(&argc, argv);
	pthread_t thread1;
	int iret1;
	iret1 = pthread_create(&thread1, NULL, startGluthThread, NULL);
}
