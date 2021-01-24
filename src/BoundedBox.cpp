#include "BoundedBox.h"
#include <algorithm>

BoundedBox::BoundedBox() {
}

BoundedBox::BoundedBox(vector<shared_ptr<Vertex>> vertices): vertices(vertices) {
}

BoundedBox::BoundedBox(vector<shared_ptr<Vertex>> vertices, shared_ptr<Color> _color): BoundedBox(vertices) {
	this->color = _color;
}

int BoundedBox::getXMin() {
	return getMin(vertices, Vertex::X);
}
int BoundedBox::getYMin() {
	return getMin(vertices, Vertex::Y);
}
int BoundedBox::getXMax() {
	return getMax(vertices, Vertex::X);
}
int BoundedBox::getYMax() {
	return getMax(vertices, Vertex::Y);
}

int BoundedBox::getZMax() {
	return getMax(vertices, Vertex::Z);
}

int BoundedBox::getZMin() {
	return getMin(vertices, Vertex::Z);
}

int BoundedBox::getMin(vector<shared_ptr<Vertex>> vertices, int property) {
	if (vertices.empty()) return 0;

	int minNum = INT_MAX;
	for (int i = 0; i < vertices.size(); i++) {
		minNum = min(minNum, vertices.at(i)->getProperty(property));
	}

	return minNum;
}

int BoundedBox::getMax(vector<shared_ptr<Vertex>> vertices, int property) {
	if (vertices.empty()) return 0;

	int maxNum = INT_MIN;
	for (int i = 0; i < vertices.size(); i++) {
		maxNum = max(maxNum, vertices.at(i)->getProperty(property));
	}

	return maxNum;
}

int BoundedBox::getWidth() {
	return  getXMax() - getXMin();
}

int BoundedBox::getHeight() {
	return getYMax() - getYMin();
}

shared_ptr<Color> BoundedBox::getColor() {
	return color;
}