#include "MeshResource.h"
#include <iostream>
#include "TextureResource.h"



MeshResource::MeshResource()
{
	vbuf = NULL;
	ibuf = NULL;
	VbufferLen = 0;
	IbufferLen = 0;
	
}

MeshResource::~MeshResource()
{
	cleanBuffers();
	cleanOpengl();
}
MeshResource::MeshResource(GLfloat* Vbuf, GLuint Vlength, GLuint* Ibuf, GLuint Ilength)
{
	vbuf = Vbuf;
	ibuf = Ibuf;
	VbufferLen = Vlength;
	IbufferLen = Ilength;
}
//Generates vertexbuffer,loads in data and sets up layout
void MeshResource::SetupVertexBuffer()
{
	//Generate vertex buffer object (vbo), bind vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Uppload bufferdata to GPU
	VbufferSize = sizeof(GLfloat) * VbufferLen;
	glBufferData(GL_ARRAY_BUFFER, VbufferSize, vbuf, GL_STATIC_DRAW);


	//Set up vertex attribute pointers for pos and texcoords
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 5));
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
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void MeshResource::cleanBuffers()
{
	delete[] vbuf;
	delete[] ibuf;
}

void MeshResource::cleanOpengl()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vao);
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


void MeshResource::generateCube(float sideLen)
{
	//removes any previous data from index and vertexbuffer
	cleanBuffers();


	VbufferLen = GLuint(40);
	IbufferLen = GLuint(36);

	//GLfloat half = sideLen;
	ibuf = { new GLuint[IbufferLen]{
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
	} };



	float half = sideLen;
	vbuf = { new GLfloat[VbufferLen]{
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

	} };
}

//Add parameter for file to load
void MeshResource::setupModel(const char* path)
{
	
	objL = new ObjLoader();
	objL->loadOBJ(path, indexData, vbufferData);
	vbuf = vbufferData.data();
	ibuf = indexData.data();
	VbufferLen = GLuint(vbufferData.size());
	IbufferLen = GLuint(indexData.size());
	delete objL;
}

void MeshResource::setupCylinderModel()
{
	cylinder = new Cylinder(1, 1, 2, 6, 1, true);
	
	cylinder->formatData(indexData, vbufferData);
	vbuf = vbufferData.data();
	ibuf = indexData.data();
	VbufferLen = GLuint(vbufferData.size());
	IbufferLen = GLuint(indexData.size());
	delete cylinder; 
}

void MeshResource::genTreeModel(std::vector<Segment> segments)
{
	trb = new TreeModelBuilder(); 
	trb->buildTreeModel(segments);
	vbufferData = trb->vertices;
	indexData = trb->indices;
	vbuf = vbufferData.data();
	ibuf = indexData.data();
	VbufferLen = GLuint(trb->vertices.size());
	IbufferLen = GLuint(trb->indices.size());

	delete trb;

}




