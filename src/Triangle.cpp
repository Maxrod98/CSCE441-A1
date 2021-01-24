#include "Triangle.h"
#include <algorithm>
#include <memory>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

Triangle::Triangle() {
}

Triangle::Triangle(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, shared_ptr<Vertex> v3) {
	v = vector<shared_ptr<Vertex>>();
	v.push_back(v1); v.push_back(v2); v.push_back(v3);

	boundedBox = make_shared<BoundedBox>(v);
}

Triangle::Triangle(vector<shared_ptr<Vertex>> v): v(v) {
	if (v.size() != 3) throw exception("Triangle Constructor: Triangle does not have 3 v.");
	
	boundedBox = make_shared<BoundedBox>(v);
}

shared_ptr<Vertex> Triangle::isInsideTriangle(shared_ptr<Vertex> p) {
	float totalArea = getTotalArea();
	float a = getArea(p, v.at(1), v.at(2)) / totalArea;
	float b = getArea(p, v.at(2), v.at(0)) / totalArea;
	float c = getArea(p, v.at(0), v.at(1)) / totalArea;

	if (a > 1 || a < 0) return nullptr;
	if (b > 1 || b < 0) return nullptr;
	if (c > 1 || c < 0) return nullptr;

	shared_ptr<Vertex> newVertex = make_shared<Vertex>(p->getX(), p->getY(), p->getZ(), a * v.at(0)->getColor()->getR(), b * v.at(1)->getColor()->getG(), c * v.at(2)->getColor()->getB());
	return newVertex;
}

float Triangle::getTotalArea() {
	return getArea(v.at(0), v.at(1), v.at(2));
}

float Triangle::getArea(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, shared_ptr<Vertex> v3) {
	return 0.5 *
		(((long)v2->getX() - v1->getX()) * ((long)v3->getY() - v1->getY())
			- ((long)v3->getX() - v1->getX()) * ((long)v2->getY() - v1->getY()));
}


shared_ptr<BoundedBox> Triangle::getBoundedBox() {
	return boundedBox;
}

void Triangle::applyRatio(float ratio) {

	for (int i = 0; i < v.size(); i++) {
		v.at(i)->setX(v.at(i)->getX() * ratio); 
		v.at(i)->setY(v.at(i)->getY() * ratio); 
		v.at(i)->setZ(v.at(i)->getZ() * ratio);
	}
}

void Triangle::applyTranslation(int overX, int overY, int overZ) {
	for (int i = 0; i < v.size(); i++) {
		v.at(i)->setX(v.at(i)->getX() + overX);
		v.at(i)->setY(v.at(i)->getY() + overY);
		v.at(i)->setZ(v.at(i)->getZ() + overZ);
	}
}

vector<shared_ptr<Vertex>> Triangle::getVertices() {
	return v;
}