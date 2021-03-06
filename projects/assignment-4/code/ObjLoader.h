#pragma once


#include "core/app.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "Vector4D.h"
#include "Matrix4D.h"


using namespace std;


/*
Add support for loading a MeshResource from a .obj file. A definition of the obj file format can be found: bla

You do not need to implement support for parsing MTL. Use vertex, texture coord and normals from the OBJ files and create a MeshResource
with buffers for the vertices, normals and tex coords.

sometimes faces are quads that will have to be triangulated

*/
struct vertex {

	Vector4D position;
	Vector4D textureCoord;
	Vector4D normal;

};

class ObjLoader {
public:
	vector <unsigned int> vertexIndices, uvIndices, normalIndices;
	//vector<Vector4D> temp_vertices;
	//vector<Vector4D> temp_uvs;
	//vector<Vector4D> temp_normals;
	//

	//vector<Vector4D> o_vertices;
	//vector<Vector4D> o_uvs;
	//vector<Vector4D> o_normals;

	void loadOBJ(const char* filename, vector<GLuint>& indices, vector<float>& data);

	//Load a file into a given string
	/*
	void LoadFromFile(const char* filename, vector<Vector4D>& out_vertices, vector<Vector4D>& out_uvs, vector<Vector4D>& out_normals);
	void LoadTest();
	*/
};