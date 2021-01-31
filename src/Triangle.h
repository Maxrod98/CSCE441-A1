#pragma once
#include <memory>
#include "Vertex.h"
#include "BoundedBox.h"
#include "Shape.h"

using namespace std;

class Triangle : public Shape {	
	shared_ptr<BoundedBox> boundedBox;
public:
	//static methods
	static double Triangle::getArea(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, shared_ptr<Vertex> v3);

	//constructors
	Triangle();
	Triangle(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, shared_ptr<Vertex> v3);
	Triangle(shared_ptr<vector<shared_ptr<Vertex>>> v);
	Triangle(shared_ptr<vector<shared_ptr<Vertex>>> v, shared_ptr<Color> c);
	Triangle(shared_ptr<vector<shared_ptr<Vertex>>> v, shared_ptr<vector<shared_ptr<Color>>> colors);
	shared_ptr<BoundedBox> getBoundedBox();

	//inherited
	shared_ptr<Vertex> Triangle::isInsideShape(shared_ptr<Vertex> v);
	double getTotalArea();
};