#include "Shape.h"

Shape::Shape() {

}
Shape::Shape(vector<shared_ptr<Vertex>> v): v(v) {
}

void Shape::applyRatio(double ratio) {
	for (int i = 0; i < v.size(); i++) {
		v.at(i)->setX(v.at(i)->getX() * ratio); 
		v.at(i)->setY(v.at(i)->getY() * ratio); 
		v.at(i)->setZ(v.at(i)->getZ() * ratio);
	}
}
void Shape::applyTranslation(double overX, double overY, double overZ) {
	for (int i = 0; i < v.size(); i++) {
		v.at(i)->setX(v.at(i)->getX() + overX);
		v.at(i)->setY(v.at(i)->getY() + overY);
		v.at(i)->setZ(v.at(i)->getZ() + overZ);
	}
	
}
vector<shared_ptr<Vertex>> Shape::getVertices() {
	return v;
}
