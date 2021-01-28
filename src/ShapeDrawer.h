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

	void modifyVertices();

	double getOverallRatio();
	double getRatioX();
	double getRatioY();

	void scaleAndTranslate(shared_ptr<Shape> s);
	void drawTriangle(shared_ptr<Triangle> t);
	void drawBoundBox(shared_ptr<BoundedBox> b);
};