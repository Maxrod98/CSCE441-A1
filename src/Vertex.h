#pragma once
#include <memory>
#include "Color.h"

using namespace std;

class Vertex
{

private:
	int x;
	int y;
	int z;
	shared_ptr<Color> color;
public:
	static const int X = 1;
	static const int Y = 2;
	static const int Z = 3;

	Vertex(int x, int y, int r, int g, int b);
	Vertex(int x, int y, int z, int r, int g, int b);
	Vertex(int x, int y, shared_ptr<Color> color);

	int getX();
	int getY();
	int getZ();
	shared_ptr<Color> getColor();

	void setX(int x);
	void setY(int y);
	void setZ(int Z);

	int getProperty(int property);
};

