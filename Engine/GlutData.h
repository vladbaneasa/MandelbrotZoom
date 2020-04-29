#ifndef GLUT_DATA
#define GLUT_DATA
#include <list>

#include <pthread.h>
extern pthread_mutex_t lock;


struct __Point2D
{
    int X;
    int Y;
    float R ,G ,B;

    __Point2D()
    {
		this->R = 1.0f;
		this->G = 1.0f;
		this->B = 1.0f;
    }
};

class GlutData
{
    public:
	static GlutData* getInstance();

	void addPoint(int x, int y, float = 1.0f, float = 1.0f, float = 1.0f);
	std::list<__Point2D>& getPoints(); 

	void addLine(int x1, int y1, int x2, int y2);
	std::list<__Point2D>& getLines(); 

	void addTriangle(int x1, int y1, int x2, int y2, int x3, int y3, float = 1.0f, float = 1.0f, float = 1.0f);

	std::list<__Point2D>& getTriangles(); 

	void removeAll();
    private:

	GlutData();
	std::list<__Point2D> points;
	std::list<__Point2D> lines;
	std::list<__Point2D> triangles;
	static GlutData *instance;
};

#endif
