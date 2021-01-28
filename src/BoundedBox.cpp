#include "BoundedBox.h"
#include <algorithm>
#include <limits.h>



using namespace std;

BoundedBox::BoundedBox() {
}

BoundedBox::BoundedBox(vector<shared_ptr<Vertex>> vertices): Shape(vertices) {
}

BoundedBox::BoundedBox(vector<shared_ptr<Vertex>> vertices, shared_ptr<Color> _color): BoundedBox(vertices) {
	this->color = _color;
}

double BoundedBox::getXMin() {
	return getMin(v, Vertex::X);
}
double BoundedBox::getYMin() {
	return getMin(v, Vertex::Y);
}
double BoundedBox::getXMax() {
	return getMax(v, Vertex::X);
}
double BoundedBox::getYMax() {
	return getMax(v, Vertex::Y);
}

double BoundedBox::getZMax() {
	return getMax(v, Vertex::Z);
}

double BoundedBox::getZMin() {
	return getMin(v, Vertex::Z);
}

double BoundedBox::getMin(vector<shared_ptr<Vertex>> vertices, int property) {
	if (vertices.empty()) throw exception("No vertices foudn");

	double minNum = 10000;
	for (int i = 0; i < vertices.size(); i++) {
		minNum = min(minNum, vertices.at(i)->getProperty(property));
	}

	return minNum;
}

double BoundedBox::getMax(vector<shared_ptr<Vertex>> vertices, int property) {
	if (vertices.empty()) throw exception("No vertices foudn");

	double maxNum = -10000;
	for (int i = 0; i < vertices.size(); i++) {
		maxNum = max(maxNum, vertices.at(i)->getProperty(property));
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