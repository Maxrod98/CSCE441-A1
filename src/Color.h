#pragma once
#include <exception>
#include <memory>

using namespace std;

class Color
{
	unsigned short r;
	unsigned short g;
	unsigned short b;

	static double RANDOM_COLORS[7][3];

public:
	const static shared_ptr<Color> RED;
	const static shared_ptr<Color> GREEN;
	const static shared_ptr<Color> BLUE;

	Color(shared_ptr<Color> c) : r(c->getR()), g(c->getG()), b(c->getB()) { //deep copy constructor
	}

	Color(){}

	Color(unsigned short r, unsigned int g, unsigned short b): r(r), g(g), b(b) {

	}

	Color(double c[3]) {
		if (sizeof(c) != 3) throw exception("Color is not complete");
		r = c[0];
		g = c[1];
		b = c[2];
	}

	unsigned short getR() {
		return r;
	}
	unsigned short getG() {
		return g;
	}
	unsigned short getB() {
		return b;
	}

	void setR(short r) {
		this->r = r;
	}

	void setG(short g) {
		this->g = g;
	}

	void setB(short b) {
		this->b = b;
	}

	Color set(short r, short g, short b) {
		this->r = r;
		this->g = g;
		this->b = b;
		return *this;
	}

	bool operator==(shared_ptr<Color> other) {
		return (getR() == other->getR() && getG() == other->getB() && getB() == other->getG());
	}

	static shared_ptr<Color> getRandomColor(int pos)
	{
		return make_shared<Color>(RANDOM_COLORS[pos][0] * 255, RANDOM_COLORS[pos][1] * 255, RANDOM_COLORS[pos][2] * 255);
	}
};

