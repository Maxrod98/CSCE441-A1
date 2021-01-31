#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "Vertex.h"

class Shape
{
protected:
	Shape();
	Shape(shared_ptr<vector<shared_ptr<Vertex>>> v);
	shared_ptr<vector<shared_ptr<Vertex>>> v = shared_ptr<vector<shared_ptr<Vertex>>>();

public:
	virtual shared_ptr<Vertex> isInsideShape(shared_ptr<Vertex> v) = 0;
	virtual double getTotalArea() = 0;
	void applyRatio(double ratio);
	void applyTranslation(double overX, double overY, double overZ);
	shared_ptr<vector<shared_ptr<Vertex>>> getVertices();
	void normalize(double minX, double minY);

};

