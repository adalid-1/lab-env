#pragma once


#include "core/app.h"
#include "ObjLoader.h"
#include "Cylinder.h"
#include "TreeModelBuilder.h"
#include <vector>

struct Segment; 

class MeshResource
{

public:

	//vertexbuffer 
	GLfloat* vbuf;
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
	//
	MeshResource();
	//setup vertexbuffer in opengl, layout is defined here
	void SetupVertexBuffer();
	//setup indexbuffer
	void SetupIndexBuffer();
	//Setup vertex and indexbuffer while vertex array object is bound
	void SetupVertexArrayObject();
	//Binds vao and draws 
	void DrawMesh(void);

	//Uses hardcoded cube that is not even correct
	void generateCube(float sideLen);
	//Uses objloader
	void setupModel(const char* path);

	//Used when loading obj, is deleted after 
	ObjLoader* objL;

	//contain data for objloader
	vector<float> vbufferData;
	vector<GLuint> indexData;

	//runs cleanup
	~MeshResource();
	//delete "new" allocated buffers 
	void cleanBuffers();
	//cleans up opengl handles
	void cleanOpengl();



	//model generator stuff
	Cylinder* cylinder; 

	void setupCylinderModel(); 

	void genTreeModel(std::vector<Segment> segments);

	TreeModelBuilder* trb;





};



