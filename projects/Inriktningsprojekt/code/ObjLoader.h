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

	void loadOBJ(const char* filename, vector<GLuint>& indices, vector<float>& data);

};