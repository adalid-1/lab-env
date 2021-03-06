#pragma once


#include "core/app.h"


class MeshResource
{

public:
	//vertexbuffer 
	GLfloat* buf;
	//opengl handle
	GLuint vbo = 0;
	//nr of elements
	GLuint VbufferLen = 0;
	//actual size
	GLuint VbufferSize = 0;

	//Indexbuffer
	GLuint* ibuf;
	//opengl handle
	GLuint ibo = 0;
	//nr of elements
	GLuint IbufferLen;
	//size of buffer
	GLuint IbufferSize;

	//Vertex array object handle
	GLuint vao = 0;

	//constructor that takes buffers as params
	MeshResource(GLfloat* Vbuf, GLuint Vlength, GLuint* Ibuf, GLuint Ilength);

	//setup vertexbuffer in opengl, layout is defined here
	void SetupVertexBuffer();
	//setup indexbuffer
	void SetupIndexBuffer();
	//Setup vertex and indexbuffer while vertex array object is bound
	void SetupVertexArrayObject();
	//Binds vao and draws 
	void DrawMesh(void);
};



