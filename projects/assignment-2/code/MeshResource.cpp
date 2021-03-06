#include "MeshResource.h"
#include <iostream>

MeshResource::MeshResource(GLfloat* Vbuf, GLuint Vlength, GLuint* Ibuf, GLuint Ilength)
{
    buf = Vbuf;
    ibuf = Ibuf;
	VbufferLen = Vlength;
	IbufferLen = Ilength;
}

//Makes vbo,loads in data and sets up layout
void MeshResource::SetupVertexBuffer()
{
	//Generate vertex buffer object (vbo), bind vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Uppload bufferdata to GPU
	VbufferSize = sizeof(GLfloat) * VbufferLen;
	glBufferData(GL_ARRAY_BUFFER, VbufferSize, buf, GL_STATIC_DRAW);

	//Set up vertex attribute pointers, pos and color
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, NULL);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (void*)(sizeof(GLfloat) * 3));
}

void MeshResource::SetupIndexBuffer()
{
	//Generate index buffer object (ibo), bind that b-boy
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	//Upload buffer data to GPU
	IbufferSize = sizeof(GLuint) * IbufferLen;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IbufferSize, ibuf, GL_STATIC_DRAW);
}

void MeshResource::SetupVertexArrayObject()
{
	//Generate, Bind the vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Setup vertex and indexbuffer while vertex array object is bound
	SetupVertexBuffer();
	SetupIndexBuffer();

	//Unbind vao
	glBindVertexArray(0);
}
//Binds vao and draws 
void MeshResource::DrawMesh()
{
	//Bind the vao
	glBindVertexArray(vao);

	//Draw 
	glDrawElements(GL_TRIANGLES, IbufferLen, GL_UNSIGNED_INT, NULL);

	//Unbind the VAO
	glBindVertexArray(0);
}


