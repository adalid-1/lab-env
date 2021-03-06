#pragma once


#include "core/app.h"


class MeshResource
{

public:
	//vertexbuffer 
	GLfloat* vbuf;
	GLuint vbo = 0;
	GLuint VbufferLen = 0;
	GLuint VbufferSize = 0;

	//Indexbuffer
	GLuint* ibuf;
	GLuint ibo = 0;
	GLuint IbufferLen;
	GLuint IbufferSize;

	//Vertex array object
	GLuint vao = 0;

	MeshResource();
	MeshResource(GLfloat* Vbuf, GLuint Vlength, GLuint* Ibuf, GLuint Ilength);
	~MeshResource();

	void SetupVertexBuffer();
	void SetupIndexBuffer();
	void SetupVertexArrayObject();

	//cleanup functions ----
	//cleans my bufferpointers
	void cleanBuffers(); 
	//cleans opengl ptrs
	void cleanOpengl();

	void DrawMesh(void);
	void generateCube(float sideLen);

	
};



