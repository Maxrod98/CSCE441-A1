#pragma once

#include "Triangle.h"
#include <algorithm>

class  ShapeDrawer {
	int desiredWidth, desiredHeight;
	shared_ptr<BoundedBox> boundedBox = make_shared<BoundedBox>();
	
	virtual void onDrawTriangle(shared_ptr<Vertex> v) {}
	virtual void onDrawBoundBox(shared_ptr<Vertex> v) {}
public:
	ShapeDrawer() {}
	ShapeDrawer(int desiredWidth, int desiredHeight, shared_ptr<BoundedBox> boundedBox);

	void drawTriangle(shared_ptr<Triangle> t);
	void drawBoundBox(shared_ptr<BoundedBox> b);

	static shared_ptr<vector<shared_ptr<Vertex>>> ShapeDrawer::convertToVertices(vector<float> & buf);
	static vector<shared_ptr<vector<shared_ptr<Vertex>>>> ShapeDrawer::convertToTriplets(shared_ptr<vector<shared_ptr<Vertex>>> vertices);

};