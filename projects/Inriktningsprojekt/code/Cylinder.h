#pragma once
#include "core/app.h"
#include <vector>
#include <iostream>

class Cylinder {


public:

	void buildVerticesFlat();
	void buildUnitCircleVertices();
	void buildVertices();

	std::vector<float> computeFaceNormal(float x1, float y1, float z1,  // v1
		float x2, float y2, float z2,  // v2
		float x3, float y3, float z3);  // v3


	void printSelf() const;

	std::vector<float> getSideNormals();

	void set(float baseRadius, float topRadius, float height, int sectors,
		int stacks, bool smooth);

	Cylinder(float baseRadius, float topRadius, float height, int sectors,
		int stacks, bool smooth);

	void formatData(std::vector<GLuint>& indexdata, std::vector<float>& vertexdata);

	void formatData(std::vector<GLuint>& indexdata, std::vector<float>& vertexdata, int offset);
	

	void clearArrays();

	void addTexCoord(float s, float t);
	void addNormal(float nx, float ny, float nz);
	void addVertex(float x, float y, float z);
	void addIndices(float i1, float i2, float i3);

	float baseRadius;
	float topRadius;
	unsigned int baseIndex;
	unsigned int topIndex;
	float height;
	int sectorCount;
	int stackCount;
	//int topIndex; 
	bool smooth;

	std::vector<float> unitCircleVertices;
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	std::vector<GLuint> indices;
	std::vector<GLuint> lineIndices;


};