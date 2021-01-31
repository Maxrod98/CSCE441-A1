#include "Vertex.h"

Vertex::Vertex( double x, double y, int r, int g, int b): color(make_shared<Color>(r, g, b)), x(x), y(y), z(0.0) {

}

Vertex::Vertex(double x, double y, double z, int r, int g, int b) : color(make_shared<Color>(r,g,b)), x(x), y(y), z(z) {

}

Vertex::Vertex(double x, double y, shared_ptr<Color> color) : x(x), y(y), z(0.0), color(color) {

}

double Vertex::getX() {
	return x;
}
double Vertex::getY() {
	return y;
}
double Vertex::getZ() {
	return z;
}

shared_ptr<Color> Vertex::getColor() {
	return color;
}

void Vertex::setX(double x) {
	this->x = x;
}
void Vertex::setY(double y) {
	this->y = y;
}
void Vertex::setZ(double z) {
	this->z = z;
}


double Vertex::getProperty(int property) {
	switch (property)
	{
	case (X):
		return x;
		break;
	case (Y):
		return y;
		break;
	case (Z):
		return z;
		break;
	default:
		throw exception("No property found");
		return -990;
		break;
	}
}