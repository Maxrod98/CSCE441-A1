#include "Triangle.h"
#include <algorithm>
#include <memory>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

Triangle::Triangle() {
}

Triangle::Triangle(shared_ptr<vector<shared_ptr<Vertex>>> v, shared_ptr<Color> c) : Triangle(v) {
	for (int i = 0; i < v->size(); i++) {
		v->at(i)->getColor()->set(c->getR(), c->getG(), c->getB());
	}
}

Triangle::Triangle(shared_ptr<vector<shared_ptr<Vertex>>> v, shared_ptr<vector<shared_ptr<Color>>> colors): Triangle(v) {
	for (int i = 0; i < v->size(); i++) {
		v->at(i)->getColor()->set(colors->at(i)->getR(), colors->at(i)->getG(), colors->at(i)->getB());
	}
}

Triangle::Triangle(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, shared_ptr<Vertex> v3) {
	v = make_shared<vector<shared_ptr<Vertex>>>();
	v->push_back(v1); v->push_back(v2); v->push_back(v3);

	boundedBox = make_shared<BoundedBox>(v);
}

Triangle::Triangle(shared_ptr<vector<shared_ptr<Vertex>>> v): Shape(v) {
	if (v->size() != 3) throw exception("Triangle Constructor: Triangle does not have 3 v.");
	
	boundedBox = make_shared<BoundedBox>(v);
}

shared_ptr<Vertex> Triangle::isInsideShape(shared_ptr<Vertex> p) {
	double totalArea = getTotalArea();
	double a = getArea(p, v->at(1), v->at(2)) / totalArea;
	double b = getArea(p, v->at(2), v->at(0)) / totalArea;
	double c = getArea(p, v->at(0), v->at(1)) / totalArea;

	if (a > 1 || a < 0) return nullptr;
	if (b > 1 || b < 0) return nullptr;
	if (c > 1 || c < 0) return nullptr;

	double zVal = (a * v->at(0)->getZ() + b * v->at(1)->getZ() + c * v->at(2)->getZ()) / 3;

	shared_ptr<Vertex> newVertex = make_shared<Vertex>(p->getX(), p->getY(), zVal ,
		a * (int)v->at(0)->getColor()->getR() + b *(int)v->at(1)->getColor()->getR()  + c *(int)v->at(2)->getColor()->getR(),
			a * (int)v->at(0)->getColor()->getG() + b * (int)v->at(1)->getColor()->getG() + c * (int)v->at(2)->getColor()->getG(),
			a * (int)v->at(0)->getColor()->getB() + b *(int)v->at(1)->getColor()->getB() + c *(int)v->at(2)->getColor()->getB());
	return newVertex;
}


double Triangle::getTotalArea() {
	return getArea(v->at(0), v->at(1), v->at(2));
}

double Triangle::getArea(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, shared_ptr<Vertex> v3) {
	return 0.5 *
		((v2->getX() - v1->getX()) * (v3->getY() - v1->getY())
			- (v3->getX() - v1->getX()) * (v2->getY() - v1->getY()));
}


shared_ptr<BoundedBox> Triangle::getBoundedBox() {
	return boundedBox;
}
