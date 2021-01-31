
#include <memory>
#include <iostream>

#include "ShapeDrawer.h"
#include "Triangle.h"
#include "Color.h"


using namespace std;

ShapeDrawer::ShapeDrawer(int desiredWidth, int desiredHeight, shared_ptr<BoundedBox> boundedBox) : desiredWidth(desiredWidth), desiredHeight(desiredHeight), boundedBox(boundedBox) {

}

shared_ptr<vector<shared_ptr<Vertex>>> ShapeDrawer::convertToVertices(vector<float>& buf) {
	auto vertices = make_shared<vector<shared_ptr<Vertex>>>();

	for (int i = 0; i < buf.size(); i++) {
		int mod = (i % 3);
		switch (mod)
		{
		case (0):
			vertices->push_back(make_shared<Vertex>(buf.at(i), 0, 0, 0, 0, 0));
			break;
		case (1):
			vertices->at(vertices->size() - 1)->setY(buf.at(i));
			break;
		case (2):
			vertices->at(vertices->size() - 1)->setZ(buf.at(i));
			break;
		default:
			break;
		}
	}

	return vertices;
}

vector<shared_ptr<vector<shared_ptr<Vertex>>>> ShapeDrawer::convertToTriplets(shared_ptr<vector<shared_ptr<Vertex>>> vertices) {
	vector<shared_ptr<vector<shared_ptr<Vertex>>>> triplets = vector<shared_ptr<vector<shared_ptr<Vertex>>>>();
	
	for (int i = 0; i < vertices->size(); i++) {
		short mod = i % 3;
		switch (mod)
		{
		case (0): {
			auto cur = make_shared<vector<shared_ptr<Vertex>>>();
			cur->push_back(vertices->at(i));
			triplets.push_back(cur);
			break;
		}
		case (1):
		case (2):
			triplets.at(triplets.size() - 1)->push_back(vertices->at(i));
			break;
		default:
			break;
		}
	}
	return triplets;
}


void ShapeDrawer::drawTriangle(shared_ptr<Triangle> t) {
	for (int y = (t->getBoundedBox()->getYMin()); y < (t->getBoundedBox()->getYMax() ); y++) {
		for (int x = (t->getBoundedBox()->getXMin() ); x < (t->getBoundedBox()->getXMax()); x++) {
			shared_ptr<Vertex> isInside = t->isInsideShape(make_shared<Vertex>(x, y, 0, 0, 0, 0));
			if (isInside) {
				onDrawTriangle(isInside);
			}
		}
	}
}

void ShapeDrawer::drawBoundBox(shared_ptr<BoundedBox> b) {

	for (int y = b->getYMin(); y < b->getYMax(); y++) {
		for (int x = b->getXMin(); x < b->getXMax(); x++) {
			onDrawBoundBox(make_shared<Vertex>(x, y, b->getColor()));
		}
	}
}

