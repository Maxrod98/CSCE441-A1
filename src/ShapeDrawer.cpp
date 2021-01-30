
#include <memory>
#include <iostream>

#include "ShapeDrawer.h"
#include "Triangle.h"
#include "Color.h"


using namespace std;

ShapeDrawer::ShapeDrawer(int desiredWidth, int desiredHeight, shared_ptr<BoundedBox> boundedBox) : desiredWidth(desiredWidth), desiredHeight(desiredWidth), boundedBox(boundedBox) {

}

void ShapeDrawer::modifyVertices() {
	boundedBox->normalize(boundedBox->getXMin(), boundedBox->getYMin());
	double ratio = getOverallRatio();
	boundedBox->applyRatio(ratio);

	if (boundedBox->getYMax() > 512) {
		cout << "error" << endl;
	}

	double translationY = ((double)desiredHeight - boundedBox->getHeight()) / 2.0;
	double translationX = ((double)desiredWidth - boundedBox->getWidth()) / 2.0;
	boundedBox->applyTranslation(translationX, translationY, 0);
}



void ShapeDrawer::drawTriangle(shared_ptr<Triangle> t) {
	for (int y = (t->getBoundedBox()->getYMin()); y < (t->getBoundedBox()->getYMax() ); y++) {
		for (int x = (t->getBoundedBox()->getXMin() ); x < (t->getBoundedBox()->getXMax()); x++) {
			shared_ptr<Vertex> isInside = t->isInsideShape(make_shared<Vertex>(x, y, 0, 0, 0, 0));
			if (isInside) {
				onDrawTriangle(isInside);
			}
		}
	}
}

void ShapeDrawer::drawBoundBox(shared_ptr<BoundedBox> b) {

	for (int y = b->getYMin(); y < b->getYMax(); y++) {
		for (int x = b->getXMin(); x < b->getXMax(); x++) {
			onDrawBoundBox(make_shared<Vertex>(x, y, b->getColor()));
		}
	}
}

double ShapeDrawer::getRatioX() {
	return (double) desiredWidth / boundedBox->getWidth();
}
double ShapeDrawer::getRatioY() {
	return (double) desiredHeight / boundedBox->getHeight();
}

double ShapeDrawer::getOverallRatio() {
	return min(getRatioX(), getRatioY());
}