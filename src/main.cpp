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

	void onDrawBoundBox(shared_ptr<Vertex> v) {
		image->setPixel(v->getX(), v->getY(), v->getColor()->getR(), v->getColor()->getG(), v->getColor()->getB());
	}
};



int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Usage: A1 meshfile" << endl;
		return 0;
	}

	//command line arguments:
	string meshName (argv[1]);
	string outputName (argv[2]);
	int imageWidth (atoi(argv[3]));
	int imageHeight (atoi(argv[4]));
	int taskNum (atoi(argv[5]));

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

	//getting the vertices separately
	auto vertices = ShapeDrawer::convertToVertices(posBuf);
	auto normals = ShapeDrawer::convertToVertices(norBuf);

	//converting to triplets to simplify our work when making triangles
	auto triplets = ShapeDrawer::convertToTriplets(vertices);
	auto normalTriplets = ShapeDrawer::convertToTriplets(normals);

	//create container for vertices, then scale and translate them appropiately
	auto boundedBox = make_shared<BoundedBox>(vertices);
	boundedBox->scaleAndTranslate(imageWidth, imageHeight);

	//note that ZBufferDrawer inherits from ShapeDrawer
	ZBufferDrawer zDrawer = ZBufferDrawer(imageWidth, imageHeight, boundedBox);

	switch (taskNum) {
		//Task 1: Drawing Bounding Boxes
		case (1): 
		{
			for (int i = 0; i < triplets.size(); i++) {
				//single color per box
				auto col = Color::getRandomColor(i % 7);
				auto bounded = make_shared<BoundedBox>(triplets.at(i), col);
				zDrawer.drawBoundBox(bounded);
			}
		}
	break;
		//Task 2: Drawing Triangles
		case (2):
		{
			for (int i = 0; i < triplets.size(); i++) {
				//single color per triangle
				auto col = Color::getRandomColor(i % 7);
				auto bounded = make_shared<Triangle>(triplets.at(i), col);
				zDrawer.drawTriangle(bounded);
			}
		}
	break;
		//Task 3: Interpolating Per - Vertex Colors
		case(3):
		{
			int curCol = 0;
			for (int i = 0; i < triplets.size(); i++) {
				//each vertex will have its own color, obtained in this for loop
				auto colors = make_shared<vector<shared_ptr<Color>>>();
				for (int j = 0; j < 3; j++) {
					colors->push_back(Color::getRandomColor(curCol % 7));
					curCol++;
				}
				auto bounded = make_shared<Triangle>(triplets.at(i), colors);
				zDrawer.drawTriangle(bounded);
			}
		}
	break;
		//Task 4: Vertical Color
		case(4):
		{
			double yMin = (double)boundedBox->getYMin();
			double height = (double)boundedBox->getHeight();

			for (int i = 0; i < triplets.size(); i++) {
				auto colors = make_shared<vector<shared_ptr<Color>>>();
				//for each vertex in the triplet, we obtain the desired color
				//which we calculate by normalizing the yValue
				for (int j = 0; j < 3; j++) {
					double yPos = triplets.at(i)->at(j)->getY();
					double yRelative = yPos - yMin;
					double ratioY =  (height - yRelative)/ height;
					colors->push_back(make_shared<Color>(255 * (1 - ratioY), 0, 255 * ratioY));
				}

				auto triangle = make_shared<Triangle>(triplets.at(i), colors);
				zDrawer.drawTriangle(triangle);
			}
		}
	break;

	//Task 5: Z-Buffering
	case (5): 
		{
			double minZ = boundedBox->getZMin();
			double depth = boundedBox->getDepth();

			for (int i = 0; i < triplets.size(); i++) {
				auto colors = make_shared<vector<shared_ptr<Color>>>();
				//we get the desired red color by normalizing the value of the zVal
				for (int j = 0; j < 3; j++) {
					double zVal = triplets.at(i)->at(j)->getZ();
					double normalizedZVal = (zVal - minZ) / depth;
					colors->push_back(make_shared<Color>(normalizedZVal * 255, 0, 0));
				}

				auto bounded = make_shared<Triangle>(triplets.at(i), colors);
				zDrawer.drawTriangle(bounded);
			}
		}
	break;
	//Task 6: Normal Coloring
	case (6):
		{
			for (int i = 0; i < triplets.size(); i++) {
				auto colors = make_shared<vector<shared_ptr<Color>>>();
				//for each single vertex, the desired color is = 255 * (0.5 * coordinate + 0.5)
				for (int j = 0; j < 3; j++) {
					double x = normalTriplets.at(i)->at(j)->getX();
					double y = normalTriplets.at(i)->at(j)->getY();
					double z = normalTriplets.at(i)->at(j)->getZ();
				
					double xT = 255 * (0.5 * x + 0.5);
					double yT = 255 * (0.5 * y + 0.5);
					double zT = 255 * (0.5 * z + 0.5);

					colors->push_back(make_shared<Color>(xT, yT , zT));
				}

				auto tri = make_shared<Triangle>(triplets.at(i), colors);
				zDrawer.drawTriangle(tri);
			}
		}
	break;
	//Task 7: Simple Lighting
	case(7):
		{
			for (int i = 0; i < triplets.size(); i++) {
				auto colors = make_shared<vector<shared_ptr<Color>>>();
				//for each single vertex, we get the desired color by max(l * n, 0)
				for (int j = 0; j < 3; j++) {
					double x = normalTriplets.at(i)->at(j)->getX();
					double y = normalTriplets.at(i)->at(j)->getY();
					double z = normalTriplets.at(i)->at(j)->getZ();
				
					double denominator = (1 / (sqrt(3)));

					double xT = 255 * x * denominator;
					double yT = 255 * y * denominator;
					double zT = 255 * z * denominator;

					double dotProduct = max(xT + yT + zT, 0.0);

					//TODO: use normals as colors
					colors->push_back(make_shared<Color>(dotProduct, dotProduct, dotProduct));
				}

				auto tri = make_shared<Triangle>(triplets.at(i), colors);
				zDrawer.drawTriangle(tri);
			}
		}

	break;
	
	default:
			cout << "No task found!" << endl;
	break;
	}

	image->writeToFile(outputName);

	return 0;
}
