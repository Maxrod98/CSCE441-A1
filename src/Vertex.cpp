#include "Vertex.h"

Vertex::Vertex( int x, int y, int r, int g, int b): color(make_shared<Color>(r, g, b)), x(x), y(y) {

}

Vertex::Vertex(int x, int y, int z, int r, int g, int b) : color(make_shared<Color>(r,g, b)), x(x), y(y), z(z) {

}

Vertex::Vertex(int x, int y, shared_ptr<Color> color) : x(x), y(y), color(color) {

}

int Vertex::getX() {
	return x;
}
int Vertex::getY() {
	return y;
}
int Vertex::getZ() {
	return z;
}

shared_ptr<Color> Vertex::getColor() {
	return color;
}

void Vertex::setX(int x) {
	this->x = x;
}
void Vertex::setY(int y) {
	this->y = y;
}
void Vertex::setZ(int z) {
	this->z = z;
}


int Vertex::getProperty(int property) {
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
		return 0;
		break;
	}
}