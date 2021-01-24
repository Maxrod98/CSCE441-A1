
#include <memory>
#include "ShapeDrawer.h"
#include "Triangle.h"
#include "Color.h"


using namespace std;

void ShapeDrawer::drawTriangle(shared_ptr<Triangle> t) {
	Triangle resizedT = Triangle(t->getVertices());
	resizedT.applyRatio(getOverallRatio());
	//these two translations must be the same for
	int translationY = (desiredHeight - boundedBox.getHeight()) / 2;
	int translationX = (desiredWidth - boundedBox.getWidth()) / 2;
	resizedT.applyTranslation(translationX, translationY , 0);

	
	for (int y = (resizedT.getBoundedBox()->getYMin()); y < (resizedT.getBoundedBox()->getYMax() ); ++y) {
		for (int x = (resizedT.getBoundedBox()->getXMin() ); x < (resizedT.getBoundedBox()->getXMax()); ++x) {

			shared_ptr<Vertex> colored = t->isInsideTriangle(make_shared<Vertex>(x, y, 0, 0, 0, 0));
			if (colored) {
				onDrawTriangle(colored);
			}
		}
	}
}

void ShapeDrawer::drawBoundBox(shared_ptr<BoundedBox> b) {
	for (int y = b->getYMin(); y < b->getYMax(); ++y) {
		for (int x = b->getXMin(); x < b->getXMax(); ++x) {
			onDrawBoundBox(make_shared<Vertex>(x, y, b->getColor()));
		}
	}
}

float ShapeDrawer::getRatioX() {
	return desiredWidth / boundedBox.getWidth();
}
float ShapeDrawer::getRatioY() {
	return desiredHeight / boundedBox.getHeight();
}

float ShapeDrawer::getOverallRatio() {
	return min(getRatioX(), getRatioY());
}