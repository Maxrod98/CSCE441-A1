#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"
#include "Triangle.h"
#include "ShapeDrawer.h"
#include "BoundedBox.h"
#include "ZBuffer.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

shared_ptr<Image> image;

class SimpleDrawer : public ShapeDrawer {
public:
	SimpleDrawer(int width, int height, shared_ptr<BoundedBox> box) : ShapeDrawer(width, height, box) {
	}

	void onDrawTriangle(shared_ptr<Vertex> v) {
		image->setPixel(v->getX(), v->getY(), v->getColor()->getR(), v->getColor()->getG(), v->getColor()->getB());
	}

	void onDrawBoundBox(shared_ptr<Vertex> v) {
		image->setPixel(v->getX(), v->getY(), v->getColor()->getR(), v->getColor()->getG(), v->getColor()->getB());
	}
};

class ZBufferDrawer : public ShapeDrawer {
public:
	shared_ptr<ZBuffer> zbuffer;

	ZBufferDrawer(int width, int height, shared_ptr<BoundedBox> box) : ShapeDrawer(width, height, box) {
		zbuffer = make_shared<ZBuffer>(width, height);
	}

	void onDrawTriangle(shared_ptr<Vertex> v) {
		if (zbuffer->getAt(v->getX(), v->getY()) < v->getZ()) {
			image->setPixel(v->getX(), v->getY(), v->getColor()->getR(), v->getColor()->getG(), v->getColor()->getB());
			zbuffer->setAt(v->getX(), v->getY(), v->getZ());
		}
	}
};


int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Usage: A1 meshfile" << endl;
		return 0;
	}
	string meshName(argv[1]);
	string outputName(argv[2]);
	int imageWidth(atoi(argv[3]));
	int imageHeight(atoi(argv[4]));
	int taskNum =  atoi(argv[5]) ;

	// Load geometry
	vector<float> posBuf; // list of vertex positions
	vector<float> norBuf; // list of vertex normals
	vector<float> texBuf; // list of vertex texture coords
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if (!rc) {
		cerr << errStr << endl;
	}
	else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
					if (!attrib.normals.empty()) {
						norBuf.push_back(attrib.normals[3 * idx.normal_index + 0]);
						norBuf.push_back(attrib.normals[3 * idx.normal_index + 1]);
						norBuf.push_back(attrib.normals[3 * idx.normal_index + 2]);
					}
					if (!attrib.texcoords.empty()) {
						texBuf.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
						texBuf.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
					}
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
	cout << "Number of vertices: " << posBuf.size() / 3 << endl;

	image = make_shared<Image>(imageWidth, imageHeight);

	auto vertices = make_shared<vector<shared_ptr<Vertex>>>();
	auto normals = make_shared<vector<shared_ptr<Vertex>>>();

	for (int i = 0; i < posBuf.size(); i++) {

		int mod = (i % 3);
		switch (mod)
		{
		case (0):
			vertices->push_back(make_shared<Vertex>(posBuf.at(i), 0, 0, 0, 0, 0));
			normals->push_back(make_shared<Vertex>(norBuf.at(i), 0, 0, 0, 0, 0));
			break;
		case (1):
			vertices->at(vertices->size() - 1)->setY(posBuf.at(i));
			normals->at(normals->size() - 1)->setY(norBuf.at(i));
			break;
		case (2):
			vertices->at(vertices->size() - 1)->setZ(posBuf.at(i));
			normals->at(normals->size() - 1)->setZ(norBuf.at(i));

			break;

		default:
			break;
		}
	}

	vector<shared_ptr<vector<shared_ptr<Vertex>>>> triplets = vector<shared_ptr<vector<shared_ptr<Vertex>>>>();
	vector<shared_ptr<vector<shared_ptr<Vertex>>>> normalTriplets = vector<shared_ptr<vector<shared_ptr<Vertex>>>>();

	for (int i = 0; i < vertices->size(); i++) {
		short mod = i % 3;

		switch (mod)
		{
		case (0): {
			auto cur = make_shared<vector<shared_ptr<Vertex>>>();
			cur->push_back(vertices->at(i));
			triplets.push_back(cur);

			auto norCur = make_shared<vector<shared_ptr<Vertex>>>();
			norCur->push_back(normals->at(i));
			normalTriplets.push_back(norCur);

			break;
		}
		case (1):
		case (2):
			triplets.at(triplets.size() - 1)->push_back(vertices->at(i));

			normalTriplets.at(normalTriplets.size() - 1)->push_back(normals->at(i));
			break;
		default:
			break;
		}
	}

	auto boundedBox = make_shared<BoundedBox>(vertices);

	SimpleDrawer simpleDrawer = SimpleDrawer(imageWidth, imageHeight, boundedBox);
	simpleDrawer.modifyVertices(); //modifies them by reference, so we only have to do this once

	ZBufferDrawer zDrawer = ZBufferDrawer(imageWidth, imageHeight, boundedBox);


	switch (taskNum) {
	case (1): {
		cout << "Task 1" << endl;
		for (int i = 0; i < triplets.size(); i++) {
			auto col = Color::getRandomColor(i % 7);
			auto bounded = make_shared<BoundedBox>(triplets.at(i), col);
			simpleDrawer.drawBoundBox(bounded);
		}
		break;
	}
	case (2):
	{
		cout << "Task 2" << endl;

		for (int i = 0; i < triplets.size(); i++) {
			auto col = Color::getRandomColor(i % 7);
			auto bounded = make_shared<Triangle>(triplets.at(i), col);
			simpleDrawer.drawTriangle(bounded);
		}

		break;
	}

	case(3):
	{
		cout << "Task 3" << endl;
		int curCol = 0;

		for (int i = 0; i < triplets.size(); i++) {
			auto colors = make_shared<vector<shared_ptr<Color>>>();
			for (int j = 0; j < 3; j++) {
				colors->push_back(Color::getRandomColor(curCol % 7));
				curCol++;
			}

			auto bounded = make_shared<Triangle>(triplets.at(i), colors);
			simpleDrawer.drawTriangle(bounded);
		}

		break;
	}

	case(4):
	{
		cout << "Task 4" << endl;

		double yMin = (double)boundedBox->getYMin();
		double height = (double)boundedBox->getHeight();

		for (int i = 0; i < triplets.size(); i++) {
			auto colors = make_shared<vector<shared_ptr<Color>>>();

			for (int j = 0; j < 3; j++) {
				double yPos = triplets.at(i)->at(j)->getY();
				double yRelative = yPos - yMin;
				double ratioY =  (height - yRelative)/ height;

				colors->push_back(make_shared<Color>(255 * (1 - ratioY), 0, 255 * ratioY));
			}

			auto triangle = make_shared<Triangle>(triplets.at(i), colors);
			simpleDrawer.drawTriangle(triangle);
		}

		break;
	}

	case (5): 
	{
		cout << "Task 5" << endl;

		double minZ = boundedBox->getZMin();
		double depth = boundedBox->getDepth();

		for (int i = 0; i < triplets.size(); i++) {
			auto colors = make_shared<vector<shared_ptr<Color>>>();
			for (int j = 0; j < 3; j++) {
				double zVal = triplets.at(i)->at(j)->getZ();
				double normalizedZVal = (zVal - minZ) / depth;
				colors->push_back(make_shared<Color>(normalizedZVal * 255, 0, 0));
			}

			auto bounded = make_shared<Triangle>(triplets.at(i), colors);
			zDrawer.drawTriangle(bounded);
		}
	}

	case (6):
	{
		cout << "Task 6" << endl;

		for (int i = 0; i < triplets.size(); i++) {
			auto colors = make_shared<vector<shared_ptr<Color>>>();
			for (int j = 0; j < 3; j++) {
				double x = normalTriplets.at(i)->at(j)->getX();
				double y = normalTriplets.at(i)->at(j)->getY();
				double z = normalTriplets.at(i)->at(j)->getZ();
				
				double xT = 255 * (0.5 * x + 0.5);
				double yT = 255 * (0.5 * y + 0.5);
				double zT = 255 * (0.5 * z + 0.5);

				//TODO: use normals as colors
				colors->push_back(make_shared<Color>(xT, yT , zT));
			}

			auto tri = make_shared<Triangle>(triplets.at(i), colors);
			zDrawer.drawTriangle(tri);
		}
	}
	break;
	
	case(7):
	{
		cout << "Task 7" << endl;

		for (int i = 0; i < triplets.size(); i++) {
			auto colors = make_shared<vector<shared_ptr<Color>>>();
			for (int j = 0; j < 3; j++) {
				double x = normalTriplets.at(i)->at(j)->getX();
				double y = normalTriplets.at(i)->at(j)->getY();
				double z = normalTriplets.at(i)->at(j)->getZ();
				
				double denominator = (1 / (sqrt(3)));

				double xT = 255 * x * denominator;
				double yT = 255 * y * denominator;
				double zT = 255 * z * denominator;

				double sum = max(xT + yT + zT, 0.0);

				//TODO: use normals as colors
				colors->push_back(make_shared<Color>(sum, sum, sum));
			}

			auto tri = make_shared<Triangle>(triplets.at(i), colors);
			zDrawer.drawTriangle(tri);
		}
	}

	}

	image->writeToFile(outputName);

	return 0;
}
