#include <stdlib.h>
#include <iostream>
#include "GlutData.h"

#include <pthread.h>

GlutData* GlutData::instance = NULL;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

GlutData::GlutData()
{
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		std::cout<<"ERROR init MUTEX";
		exit(1);
	}
}

GlutData* GlutData::getInstance()
{
    if (GlutData::instance==NULL)
	GlutData::instance = new GlutData();

    return GlutData::instance;
}

void GlutData::addPoint(int x, int y, float r, float g, float b)
{
    __Point2D point;
    point.X = x;
    point.Y = y;
    point.R = r;
    point.G = g;
    point.B = b;

    this->points.push_back(point);
}

std::list<__Point2D>& GlutData::getPoints() 
{
    return (this->points);
}

void GlutData::addLine(int x1, int y1, int x2, int y2)
{
    __Point2D point;
    point.X = x1;
    point.Y = y1;
    this->lines.push_back(point);
    point.X = x2;
    point.Y = y2;
    this->lines.push_back(point);
}

std::list<__Point2D>& GlutData::getLines()
{
    return (this->lines);
}

void GlutData::addTriangle(int x1, int y1, int x2, int y2, int x3, int y3, float r, float g, float b)
{
    __Point2D point;
    point.X = x1;
    point.Y = y1;
    this->triangles.push_back(point);
    point.X = x2;
    point.Y = y2;
    this->triangles.push_back(point);
    point.X = x3;
    point.Y = y3;
    this->triangles.push_back(point);
}

std::list<__Point2D>& GlutData::getTriangles() 
{
    return (this->triangles);
}

void GlutData::removeAll()
{
    this->points.clear();
    this->lines.clear();
    this->triangles.clear();
}
