#include "EngineGlut.h"
#include "GlutData.h"
#include "GlutDrawing.h"


void initEngineGlut(int argc, char **argv)
{
	initGlutDrawing(argc, argv);
}


EngineGlut::EngineGlut()
{
	//by default (0,0) is corner down left - to get to center we add WIN_MAX_X/2 and WIN_MAX_Y/2
}

void EngineGlut::drawPoint(int x, int y, float r, float g, float b)
{
	x += WIN_MAX_X/2;
	y += WIN_MAX_Y/2;

	pthread_mutex_lock(&lock);

	GlutData::getInstance()->addPoint(x,y,r,g,b);

	pthread_mutex_unlock(&lock);
}

void EngineGlut::drawLine(int x1, int y1, int x2, int y2)
{
	x1 += WIN_MAX_X/2;
	y1 += WIN_MAX_Y/2;
	x2 += WIN_MAX_X/2;
	y2 += WIN_MAX_Y/2;

	pthread_mutex_lock(&lock);
	
	GlutData::getInstance()->addLine(x1,y1, x2, y2);

	pthread_mutex_unlock(&lock);
}

void EngineGlut::drawSurface(int x1, int y1, int x2, int y2, int x3, int y3)
{
	x1 += WIN_MAX_X/2;
	y1 += WIN_MAX_Y/2;
	x2 += WIN_MAX_X/2;
	y2 += WIN_MAX_Y/2;
	x3 += WIN_MAX_X/2;
	y3 += WIN_MAX_Y/2;

	pthread_mutex_lock(&lock);

	GlutData::getInstance()->addTriangle(x1,y1, x2, y2, x3, y3);

	pthread_mutex_unlock(&lock);
}
void EngineGlut::drawSurface(int x1, int y1, int x2, int y2, int x3, int y3, float r, float g, float b)
{
	x1 += WIN_MAX_X/2;
	y1 += WIN_MAX_Y/2;
	x2 += WIN_MAX_X/2;
	y2 += WIN_MAX_Y/2;
	x3 += WIN_MAX_X/2;
	y3 += WIN_MAX_Y/2;

	pthread_mutex_lock(&lock);

	GlutData::getInstance()->addTriangle(x1, y1, x2, y2, x3, y3, r, g, b);

	pthread_mutex_unlock(&lock);
}

void EngineGlut::drawClear()
{
	pthread_mutex_lock(&lock);

	GlutData::getInstance()->removeAll();

	pthread_mutex_unlock(&lock);
}

