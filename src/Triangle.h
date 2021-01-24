#pragma once
#include <memory>
#include "Vertex.h"
#include "BoundedBox.h"

using namespace std;

class Triangle {
	vector<shared_ptr<Vertex>> v;

	shared_ptr<BoundedBox> boundedBox;
public:
	//static methods
	static float Triangle::getArea(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, shared_ptr<Vertex> v3);

	//constructors
	Triangle();
	Triangle(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, shared_ptr<Vertex> v3);
	Triangle(vector<shared_ptr<Vertex>> v);

	//methods
	shared_ptr<Vertex> Triangle::isInsideTriangle(shared_ptr<Vertex> v);
	float getTotalArea();
	shared_ptr<BoundedBox> getBoundedBox();

	void applyRatio(float ratio);
	void applyTranslation(int overX, int overY, int overZ);

	vector<shared_ptr<Vertex>> Triangle::getVertices();
};