#pragma once
#include "Triangle.h"

class  ShapeDrawer {
	int desiredWidth, desiredHeight;
	BoundedBox boundedBox;
	
	virtual void onDrawTriangle(shared_ptr<Vertex> v) {}
	virtual void onDrawBoundBox(shared_ptr<Vertex> v) {}
public:
	ShapeDrawer() {}
	ShapeDrawer(int desiredWidth, int desiredHeight, BoundedBox boundedBox) : desiredWidth(desiredWidth), desiredHeight(desiredWidth), boundedBox(boundedBox) {
		
		
	}

	float getOverallRatio();
	float getRatioX();
	float getRatioY();

	

	void drawTriangle(shared_ptr<Triangle> t);
	void drawBoundBox(shared_ptr<BoundedBox> b);
};