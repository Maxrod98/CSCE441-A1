#pragma once
#include <vector>
#include <memory>
#include "Vertex.h"
#include "Shape.h"

using namespace std;

class BoundedBox: public Shape
{
	shared_ptr<Color> color;

public:
	BoundedBox();
	BoundedBox(vector<shared_ptr<Vertex>> vertices);
	BoundedBox(vector<shared_ptr<Vertex>> vertices, shared_ptr<Color> color);
	double getXMin();
	double getYMin();
	double getZMin();

	double getXMax();
	double getYMax();
	double getZMax();
	
	double getMin(vector<shared_ptr<Vertex>> vertices, int property);
	double getMax(vector<shared_ptr<Vertex>> vertices, int property);

	double getWidth();
	double getHeight();
	
	shared_ptr<Color> getColor();

	//inherited methods
	shared_ptr<Vertex> isInsideShape(shared_ptr<Vertex> v);
	double getTotalArea();

};

