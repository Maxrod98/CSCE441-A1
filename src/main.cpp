#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"
#include "Triangle.h"
#include "ShapeDrawer.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

shared_ptr<Image> image;

class MyDrawer : public ShapeDrawer {
public:
	MyDrawer(int width ,int height, BoundedBox box) : ShapeDrawer(width, height, box) {

	}

	void onDrawTriangle(shared_ptr<Vertex> v) {
		image->setPixel(v->getX(), v->getY(), v->getColor()->getR(), v->getColor()->getG(), v->getColor()->getB());
	}
};

double RANDOM_COLORS[7][3] = {
	{0.0000,    0.4470,    0.7410},
	{0.8500,    0.3250,    0.0980},
	{0.9290,    0.6940,    0.1250},
	{0.4940,    0.1840,    0.5560},
	{0.4660,    0.6740,    0.1880},
	{0.3010,    0.7450,    0.9330},
	{0.6350,    0.0780,    0.1840},
};

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Usage: A1 meshfile" << endl;
		return 0;
	}
	string meshName(argv[1]);
	string outputName(argv[2]);
	int imageWidth(atoi(argv[3]));
	int imageHeight(atoi(argv[4]));
	int taskNum(atoi(argv[5]));

	// Load geometry
	vector<float> posBuf; // list of vertex positions
	vector<float> norBuf; // list of vertex normals
	vector<float> texBuf; // list of vertex texture coords
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
					if(!attrib.normals.empty()) {
						norBuf.push_back(attrib.normals[3*idx.normal_index+0]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+1]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+2]);
					}
					if(!attrib.texcoords.empty()) {
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
					}
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
	cout << "Number of vertices: " << posBuf.size()/3 << endl;
	
	image = make_shared<Image>(imageWidth, imageHeight);
	
	auto vertices = make_shared<vector<shared_ptr<Vertex>>>();
	for (int i = 0; i < posBuf.size(); i++) {
		int mod = i % 3;
		switch (mod)
		{
		case (0):
			//make_shared<Color>(RANDOM_COLORS[(i % 3) % 7])
			vertices->push_back(make_shared<Vertex>(posBuf.at(i), 0, 0, 0, 0, 0 ));

			break;
		case (1):
			vertices->at(vertices->size() - 1)->setY(posBuf.at(i));

			break;
		case (2):
			vertices->at(vertices->size() - 1)->setZ(posBuf.at(i));

			break;
			
		default:
			break;
		}
		
	}

	MyDrawer td = MyDrawer(imageWidth, imageHeight, BoundedBox(*vertices));
	td.drawTriangle(make_shared<Triangle>(*vertices));

	image->writeToFile(outputName);

	return 0;
}
