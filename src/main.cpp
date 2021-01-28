#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"
#include "Triangle.h"
#include "ShapeDrawer.h"
#include "BoundedBox.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

shared_ptr<Image> image;

class MyDrawer : public ShapeDrawer {
public:
	MyDrawer(int width ,int height, shared_ptr<BoundedBox> box) : ShapeDrawer(width, height, box) {

	}

	void onDrawTriangle(shared_ptr<Vertex> v) {
		image->setPixel(v->getX(), v->getY(), v->getColor()->getR(), v->getColor()->getG(), v->getColor()->getB());
	}

	void onDrawBoundBox(shared_ptr<Vertex> v) {
		image->setPixel(v->getX(), v->getY(), v->getColor()->getR(), v->getColor()->getG(), v->getColor()->getB());
	}
};

template<typename T>
shared_ptr<vector<T>> slice(shared_ptr<vector<T>> const& v, int m, int n)
{
	auto first = v->cbegin() + m;
	auto last = v->cbegin() + n + 1;

	auto vec = make_shared<vector<T>>(first, last);
	return vec;
}

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
	int taskNum = /* atoi(argv[5]) */ 1;

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

	Color color = Color(0, 0, 0);


	auto vertices = make_shared<vector<shared_ptr<Vertex>>>();

	for (int i = 0; i < posBuf.size(); i++) {
		
		int colMod = (i % 7);
		color = *Color::getRandomColor(colMod);
		//color.set(255, 255, 255);

		int mod = (i % 3);
		switch (mod)
		{
		case (0):
			//make_shared<Color>(RANDOM_COLORS[(i % 3) % 7])
			vertices->push_back(make_shared<Vertex>(posBuf.at(i) , 0, 0, color.getR(), color.getG(), color.getB() ));

			break;
		case (1):
			vertices->at(vertices->size() - 1)->setY(posBuf.at(i) );
			break;
		case (2):
			vertices->at(vertices->size() - 1)->setZ(posBuf.at(i) );

			break;
			
		default:
			break;
		}
	}

	MyDrawer td = MyDrawer(imageWidth, imageHeight, make_shared<BoundedBox>(*vertices));
	td.modifyVertices();

	vector<shared_ptr<vector<shared_ptr<Vertex>>>> triplets = vector<shared_ptr<vector<shared_ptr<Vertex>>>>();
	for (int i = 0; i < vertices->size(); i++) {
		short mod = i % 3;

		switch (mod)
		{
		case (0): {
			auto cur = make_shared<vector<shared_ptr<Vertex>>>();
			cur->push_back(vertices->at(i));
			triplets.push_back(cur);
			break;
		}
		case (1):
		case (2):
			triplets.at(triplets.size() - 1)->push_back(vertices->at(i));
			break;
		default:
			break;
		}
	}


	switch (taskNum) {
	case (1):
		
		cout << "Task 1" << endl;
		for (int i = 0; i < triplets.size(); i++) {
			auto col = Color::getRandomColor(i % 7);
			auto bounded = make_shared<BoundedBox>(*triplets.at(i), col);
			td.drawBoundBox(bounded);
		}
		break;
	case (2):
		cout << "Task 2" << endl;
		break;

	case(3):
		cout << "Task 3" << endl;

		for (int i = 0; i < vertices->size() / 3; i++) {
			auto test = make_shared<Triangle>(*slice(vertices, i, i + 3 - 1));
			td.drawTriangle(test);
			//auto bounded = make_shared<BoundedBox>(slice(*vertices, i, i + 3 - 1), Color::RED);
			//td.drawBoundBox(make_shared<BoundedBox>(*slice(vertices, i, i + 3 - 1), Color::RED));
		}


		break;
	}

	//auto b = make_shared<BoundedBox>(*vertices, make_shared<Color>(c.getR(), c.getG(), c.getB()));
	//td.drawBoundBox(b);
	
	image->writeToFile(outputName);

	return 0;
}
