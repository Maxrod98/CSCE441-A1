#pragma once
#include <memory>
#include <exception>
#include "Color.h"

using namespace std;

class Vertex
{

private:
	double x;
	double y;
	double z;
	shared_ptr<Color> color;
public:
	static const int X = 1;
	static const int Y = 2;
	static const int Z = 3;

	Vertex(double x, double y, int r, int g, int b);
	Vertex(double x, double y, double z, int r, int g, int b);
	Vertex(double x, double y, shared_ptr<Color> color);

	double getX();
	double getY();
	double getZ();
	shared_ptr<Color> getColor();

	void setX(double x);
	void setY(double y);
	void setZ(double Z);

	double getProperty(int property);
};

