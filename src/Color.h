#pragma once
#include <exception>

using namespace std;

class Color
{
	int r;
	int g;
	int b;

public:
	const static Color RED;
	const static Color GREEN;
	const static Color BLUE;

	Color(){}

	Color(int r, int g, int b) {

	}

	Color(double c[3]) {
		if (sizeof(c) != 3) throw exception("Color is not complete");
		r = c[0];
		g = c[1];
		b = c[2];
	}

	int getR() {
		return r;
	}
	int getG() {
		return g;
	}
	int getB() {
		return b;
	}

	void setR(int r) {
		this->r = r;
	}

	void setG(int g) {
		this->g = g;
	}

	void setB(int b) {
		this->b = b;
	}

};

