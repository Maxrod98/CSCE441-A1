#pragma once
#include <vector>
#include <memory>
#include "Vertex.h"

using namespace std;

class BoundedBox
{
	shared_ptr<Color> color;
	vector<shared_ptr<Vertex>> vertices;

public:
	BoundedBox();
	BoundedBox(vector<shared_ptr<Vertex>> vertices);
	BoundedBox(vector<shared_ptr<Vertex>> vertices, shared_ptr<Color> color);
	int getXMin();
	int getYMin();
	int getZMin();

	int getXMax();
	int getYMax();
	int getZMax();
	
	int getMin(vector<shared_ptr<Vertex>> vertices, int property);
	int getMax(vector<shared_ptr<Vertex>> vertices, int property);

	int getWidth();
	int getHeight();
	
	shared_ptr<Color> getColor();

};

