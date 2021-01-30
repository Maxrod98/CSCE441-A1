#include "BoundedBox.h"
#include <algorithm>
#include <limits.h>



using namespace std;

BoundedBox::BoundedBox() {
}

BoundedBox::BoundedBox(shared_ptr<vector<shared_ptr<Vertex>>> vertices): Shape(vertices) {
}

BoundedBox::BoundedBox(shared_ptr<vector<shared_ptr<Vertex>>> vertices, shared_ptr<Color> _color): BoundedBox(vertices) {
	this->color = _color;
}

double BoundedBox::getXMin() {
	return getMin(Vertex::X);
}
double BoundedBox::getYMin() {
	return getMin(Vertex::Y);
}
double BoundedBox::getXMax() {
	return getMax(Vertex::X);
}
double BoundedBox::getYMax() {
	return getMax(Vertex::Y);
}

double BoundedBox::getZMax() {
	return getMax(Vertex::Z);
}

double BoundedBox::getZMin() {
	return getMin(Vertex::Z);
}

double BoundedBox::getMin( int property) {
	if (v->empty()) throw exception("No vertices foudn");

	double minNum = DBL_MAX;
	for (int i = 0; i < v->size(); i++) {
		minNum = min(minNum, v->at(i)->getProperty(property));
	}

	return minNum;
}

double BoundedBox::getMax(int property) {
	if (v->empty()) throw exception("No vertices foudn");

	double maxNum = DBL_MIN;
	for (int i = 0; i < v->size(); i++) {
		maxNum = max(maxNum, v->at(i)->getProperty(property));
	}

	return maxNum;
}

double BoundedBox::getWidth() {
	return  getXMax() - getXMin();
}

double BoundedBox::getHeight() {
	return getYMax() - getYMin();
}

shared_ptr<Color> BoundedBox::getColor() {
	return color;
}

shared_ptr<Vertex> BoundedBox::isInsideShape(shared_ptr<Vertex> v) {
		return v;
}
double BoundedBox::getTotalArea() {
	return getWidth() * getHeight();
}