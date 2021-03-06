#include "MeshResource.h"
#include <iostream>
#include "TextureResource.h"

MeshResource::MeshResource()
{
}

MeshResource::MeshResource(GLfloat* Vbuf, GLuint Vlength, GLuint* Ibuf, GLuint Ilength)
{
    buf = Vbuf;
    ibuf = Ibuf;
	VbufferLen = Vlength;
	IbufferLen = Ilength;
}

MeshResource::~MeshResource()
{
	//delete[] buf;
//Clean up stuff 
}




void MeshResource::SetupVertexBuffer()
{
	//Generate vertex buffer object (vbo), bind vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Uppload vertexbuffer data to GPU
	VbufferSize = sizeof(GLfloat) * VbufferLen;
	glBufferData(GL_ARRAY_BUFFER, VbufferSize, buf, GL_STATIC_DRAW);

	//Set up vertex attribute pointers:
	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, NULL);
	//tex c00rds
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)(sizeof(GLfloat) * 3));
	
	//tells the system that we are using Nth place in the shader
	//tells the GPU what layout the vertex-buffer has
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

	//Setup vertex and indexbuffer
	SetupVertexBuffer();
	SetupIndexBuffer();

	//Unbind vao
	glBindVertexArray(0);
}

void MeshResource::DrawMesh()
{
	//Bind the vao
	glBindVertexArray(vao);

	//Draw 
	glDrawElements(GL_TRIANGLES, IbufferLen, GL_UNSIGNED_INT, NULL);

	//Unbind the VAO
	glBindVertexArray(0);

}

void MeshResource::Setup() {
    SetupVertexArrayObject();
    SetupVertexBuffer();
    SetupIndexBuffer();
}

void MeshResource::generateCube(float sideLen)
{
	//indices 
	GLuint hej[] = {
		//Front facing
		0, 1, 3,
		1, 2, 3,
		//Back facing
		4, 5, 7,
		5, 6, 7,
		//right facing
		0, 4, 1,
		4, 5, 1,
		//left facing
		2, 7, 3,
		6, 2, 7,
		//Top
		7, 4, 0,
		0, 3 , 7,
		//Bottom
		1, 2, 5,
		6, 5, 2

	};


	float half = sideLen  ;
	//vertices
	float cubeBuffer[] = {
		half, half, half,           //Front upper right
		//1,        0,        0,        1,    // color 0
		1, 1,

		half, -half, half,          //Front lower right
	//	1,        0,        0.5,        1,    // color 0
		1, 0,

		-half, -half, half,         //Front lower left
		//1,        0,        0.5,        1,    // color 0
		0, 0,

		-half, half, half,          //Front upper left
		//1,        0,        0,        1,    // color 0
		0, 1,




		half, half, -half,          //Back upper right
	//a	0,        1,        0,        1,    // color 0
		0, 1,

		half, -half, -half,         //Back lower right
	//	0,        1,        0.5,        1,    // color 0
		0, 0,

		-half, -half, -half,        //Back lower left
	//	0,        1,        0.5,        1,    // color 0
		1, 0,


		-half, half, -half,         //Back upper left
	//	0,        1,        0,        1,    // color 0
		1, 1

	};

	//Have to stuff these arrays into something that won´t go out of scope, might be some better way
	for (int i = 0; i < 36; i++)
	{
		indid[i] = hej[i];
	}
	for (int i = 0; i < 40; i++)
	{
		arra[i] = cubeBuffer[i];
	}

	buf = arra;
	ibuf = indid;
	VbufferLen =  GLuint(40);
	IbufferLen =  GLuint(36);
	
}


void MeshResource::setupModel(ObjLoader& objL)
{
	//objL.loadOBJ("TestOBJ.obj", indexData, vbufferData);
	objL.loadOBJ("cottage_obj.obj", indexData, vbufferData);
	buf = vbufferData.data();
	ibuf = indexData.data();
	VbufferLen = GLuint(vbufferData.size());
	IbufferLen = GLuint(indexData.size());
	//void loadOBJ(const char* filename, vector<GLuint>& indices, vector<float>& data);
}



//Draw without Vertex Array Objects
//not currently in use
void MeshResource::DrawMesh2(void)
{
	//Bind vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	//Bind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


	//Draw
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);

	//Maybe unbind buffers here to be safe
}


