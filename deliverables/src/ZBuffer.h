#pragma once
#include <memory>
#include <vector>
#include <exception>
#include <iostream>
#include <climits>

using namespace std;

class ZBuffer
{
private:
	int width;
	int height;
	shared_ptr<vector<shared_ptr<vector<double>>>> zbuffer = make_shared<vector<shared_ptr<vector<double>>>>();

public:
	ZBuffer() {}
	ZBuffer(int width, int height) : width(width), height(height) {
		for (int i = 0; i < width; i++) {
			zbuffer->push_back(make_shared<vector<double>>());
			for (int j = 0; j < height; j++) {
				zbuffer->at(zbuffer->size() - 1)->push_back(-1000000);
			}
		}
	}

	void assertBuffer(int x, int y) {
		if (x > width || x < 0) {
			cout << "ZBufferException: The x is: " << x << " while the width is: " << width << endl;
			throw new exception("Out of bounds");
		}
		if (y > height || y < 0) {
			cout << "ZBufferException: The y is: " << y << " while the height is: " << height << endl;
			throw new exception("Out of bounds");
		}
	}

	double getAt(int x, int y) {
		assertBuffer(x, y);

		return zbuffer->at(x)->at(y);
	}
	void setAt(int x, int y, double val) {
		assertBuffer(x, y);

		zbuffer->at(x)->at(y) = val;
	}


};

