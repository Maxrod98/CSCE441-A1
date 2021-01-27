#pragma once
#include <memory>
#include <vector>
#include "Vertex.h"

class Shape
{
protected:
	Shape();
	Shape(vector<shared_ptr<Vertex>> v);
	vector<shared_ptr<Vertex>> v = vector<shared_ptr<Vertex>>();

public:
	virtual shared_ptr<Vertex> isInsideShape(shared_ptr<Vertex> v) = 0;
	virtual double getTotalArea() = 0;
	void applyRatio(double ratio);
	void applyTranslation(double overX, double overY, double overZ);
	vector<shared_ptr<Vertex>> getVertices();
};

//TODO: make sure your shapes inherit from here
