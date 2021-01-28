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
	Triangle(vector<shared_ptr<Vertex>> v);
	Triangle(shared_ptr<Triangle> t); //copy constructor
	shared_ptr<BoundedBox> getBoundedBox();

	//inherited
	shared_ptr<Vertex> Triangle::isInsideShape(shared_ptr<Vertex> v);
	double getTotalArea();
};