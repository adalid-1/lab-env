#pragma once


#include "core/app.h"
#include "ObjLoader.h"
#include <vector>

class MeshResource
{

public:
	//vertexbuffer 
	GLfloat* buf;
	GLuint vbo = 0;
	GLuint VbufferLen = 0;
	GLuint VbufferSize = 0;

	GLfloat* cubeBuffer;

	//Indexbuffer
	GLuint* ibuf;
	GLuint ibo = 0;
	GLuint IbufferLen;
	GLuint IbufferSize;

	//Vertex array object
	GLuint vao = 0;
	//Specifies the number of elements to be rendered. 
	GLuint numIndices;

	//contain data
	float arra[40];
	GLuint indid[36];
	vector<float> vbufferData;
	vector<GLuint> indexData;

	MeshResource();
	MeshResource(GLfloat* Vbuf, GLuint Vlength, GLuint* Ibuf, GLuint Ilength);
	~MeshResource();

	void SetupVertexBuffer();
	void SetupIndexBuffer();
	void SetupVertexArrayObject();

	//Sets some things up
	void Setup();



	void DrawMesh(void);
	//Draws mesh without vao
	void DrawMesh2(void);

	void Test(void);


	void generateCube(float sideLen);

	void setupModel(ObjLoader& objL);

};



