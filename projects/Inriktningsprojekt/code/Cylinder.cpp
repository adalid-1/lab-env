#include "Cylinder.h"


const int MIN_SECTOR_COUNT = 3;
const int MIN_STACK_COUNT = 1;


Cylinder::Cylinder(float baseRadius, float topRadius, float height, int sectors,
	int stacks, bool smooth)
{
	set(baseRadius, topRadius, height, sectors, stacks, smooth);
}

void Cylinder::formatData(std::vector<GLuint>& indexdata, std::vector<float>& vertexdata)
{
	//stuffs vertex data into a float vector
	for (int i = 0,  j = 0; i < vertices.size()-2; i += 3, j += 2)
	{
		vertexdata.push_back(vertices[i]);
		vertexdata.push_back(vertices[i+1]);
		vertexdata.push_back(vertices[i + 2]);

		vertexdata.push_back(texCoords[j]);
		vertexdata.push_back(texCoords[j+1]);

		vertexdata.push_back(normals[i]);
		vertexdata.push_back(normals[i+1]);
		vertexdata.push_back(normals[i+2]);
	}


	for (int i = 0; i < indices.size(); i++) {
		indexdata.push_back(indices[i] );
	}
	std::cout << vertexdata.size() << std::endl;
	std::cout << indexdata.size() << std::endl;


}

void Cylinder::formatData(std::vector<GLuint>& indexdata, std::vector<float>& vertexdata, int offset)
{
	//stuffs vertex data into a float vector
	for (int i = 0, j = 0; i < vertices.size() - 2; i += 3, j += 2)
	{
		vertexdata.push_back(vertices[i]);
		vertexdata.push_back(vertices[i + 1]);
		vertexdata.push_back(vertices[i + 2]);

		vertexdata.push_back(texCoords[j]);
		vertexdata.push_back(texCoords[j + 1]);

		vertexdata.push_back(normals[i]);
		vertexdata.push_back(normals[i + 1]);
		vertexdata.push_back(normals[i + 2]);
	}


	for (int i = 0; i < indices.size(); i++) {
		indexdata.push_back(indices[i] + offset);
	}
	std::cout << vertexdata.size() << std::endl;
	std::cout << indexdata.size() << std::endl;


}


void Cylinder::clearArrays()
{
	std::vector<float>().swap(vertices);
	std::vector<float>().swap(normals);
	std::vector<float>().swap(texCoords);
	std::vector<unsigned int>().swap(indices);
	std::vector<unsigned int>().swap(lineIndices);
}

void Cylinder::addTexCoord(float s, float t)
{
	texCoords.push_back(s);
	texCoords.push_back(t);
}

void Cylinder::addNormal(float nx, float ny, float nz)
{
	normals.push_back(nx);
	normals.push_back(ny);
	normals.push_back(nz);
}

void Cylinder::addVertex(float x, float y, float z)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
}

void Cylinder::addIndices(float i1, float i2, float i3)
{
	indices.push_back(i1);
	indices.push_back(i2);
	indices.push_back(i3);
}




void Cylinder::buildUnitCircleVertices()
{
	const float PI = acos(-1);
	float sectorStep = 2 * PI / sectorCount;
	float sectorAngle;
	//Not sure why we are swapping
	std::vector<float>().swap(unitCircleVertices);
	for (int i = 0; i <= sectorCount; i++) {

		sectorAngle = i * sectorStep;
		unitCircleVertices.push_back(cos(sectorAngle)); //x
		unitCircleVertices.push_back(sin(sectorAngle)); //y
		unitCircleVertices.push_back(0);				 //z

	}
}

//Smooth shading variant, might want flat
void Cylinder::buildVertices()
{
	//Clear arrays

	//Vertex positions
	float x, y, z;  
	//Radius for each stack
	float radius;

	//get normals for sides
	std::vector<float> sideNormals = getSideNormals();

	//put vertices cylinder side to array by scaling unit circle
	for (int i = 0; i <= stackCount; i++) {

		z = -(height * 0.5) + (float)i / stackCount * height; //Vertex position z
		radius = baseRadius + (float)i / stackCount * (topRadius - baseRadius); //lerp
		float t = 1.0f - (float)i / stackCount;		//top to bottom

		for (int j = 0,  k = 0; j <= sectorCount; ++j, k += 3) {
			x = unitCircleVertices[k];
			y = unitCircleVertices[(k + 1)];
			//position
			addVertex(x * radius, y * radius, z);
			//normal
			addNormal(sideNormals[k], sideNormals[k + 1], sideNormals[k + 2]);
			//texcoord
			addTexCoord((float)j / sectorCount, t);

		}

	}

	//remember where the base.top vertices start
	unsigned int baseVertexIndex = (unsigned int)vertices.size() / 3;

	//put vertices of cylinder base
	z = -height * 0.5;
	addVertex(0, 0, z);
	addNormal(0, 0, -1);
	addTexCoord(0.5f, 0.5f);
	for (int i = 0, j = 0; i < sectorCount; ++i, j += 3)
	{
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];
		//position
		addVertex(x * baseRadius, y * baseRadius, z);
		//normal
		addNormal(0, 0, -1);
		//texcoord
		addTexCoord(-x * 0.5f + 0.5f, -y * 0.5f + 0.5f);

	}

	//remember where the base vertices start
	unsigned int topVertexIndex = (unsigned int)vertices.size() / 3;

	//put vertices of top cylinder
	z = height * 0.5f;
	addVertex(0, 0, z);
	addNormal(0, 0, 1);
	addTexCoord(0.5f, 0.5f);
	for (int i = 0, j = 0; i < sectorCount; ++i, j += 3)
	{
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];
		//position
		addVertex(x * topRadius, y * topRadius, z);
		//normal
		addNormal(0, 0, 1);
		//texcoord
		addTexCoord(x * 0.5f + 0.5f, y * 0.5f + 0.5f);
	}
	//Indices part 
	//--------------------------------------------------------------------------

	//Put indices for sides
	unsigned int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		//Beginning of current stack
		k1 = i * (sectorCount + 1);
		//Beginning of next stack
		k2 = k1 + sectorCount + 1; 

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
			// 2 triangles per sector
			addIndices(k1, k1 + 1, k2);
			addIndices(k2, k1 + 1, k2 + 1);
			// vertical lines for all stacks
			lineIndices.push_back(k1);
			lineIndices.push_back(k2);
			// horizontal lines
			lineIndices.push_back(k2);
			lineIndices.push_back(k2 + 1);

			if (i == 0) {
				lineIndices.push_back(k1);
				lineIndices.push_back(k1 + 1);
			}
		}
	}

	//remember where base indices start
	baseIndex = (unsigned int)indices.size();

	//put indices for base
	for (int i = 0, k = baseVertexIndex + 1; i < sectorCount; ++i, ++k) {
		if (i < (sectorCount - 1)) {
			addIndices(baseVertexIndex, k + 1, k);
		}
		else
		{
			//last triangle
			addIndices(baseVertexIndex, baseVertexIndex + 1, k);
		}
	}

	//remember where base indices start
	topIndex = (unsigned int)indices.size();
	//Put top indices
	for (int i = 0, k = topVertexIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < (sectorCount - 1)) {
			addIndices(topVertexIndex, k, k + 1);
		}
		else {
			//last
			addIndices(topIndex, k, topVertexIndex + 1);
		}
	}

}

void Cylinder::set(float baseRadius, float topRadius, float height, int sectors,
	int stacks, bool smooth)
{
	this->baseRadius = baseRadius;
	this->topRadius = topRadius;
	this->height = height;
	this->sectorCount = sectors;
	if (sectors < MIN_SECTOR_COUNT)
		this->sectorCount = MIN_SECTOR_COUNT;
	this->stackCount = stacks;
	if (stacks < MIN_STACK_COUNT)
		this->stackCount = MIN_STACK_COUNT;
	this->smooth = smooth;

	// generate unit circle vertices first
	buildUnitCircleVertices();

	if (smooth){ buildVertices(); }
		
	else {//buildVerticesFlat();
	}
	printSelf(); 
		
}

void Cylinder::printSelf() const
{
	std::cout << "===== Cylinder =====\n"
		<< "   Base Radius: " << baseRadius << "\n"
		<< "    Top Radius: " << topRadius << "\n"
		<< "        Height: " << height << "\n"
		<< "  Sector Count: " << sectorCount << "\n"
		<< "   Stack Count: " << stackCount << "\n"
		<< "Smooth Shading: " << (smooth ? "true" : "false") << "\n"
	/*	<< "Triangle Count: " << getTriangleCount() << "\n"
		<< "   Index Count: " << getIndexCount() << "\n"
		<< "  Vertex Count: " << getVertexCount() << "\n"
		<< "  Normal Count: " << getNormalCount() << "\n"
		<< "TexCoord Count: " << getTexCoordCount()*/ << std::endl;
}


std::vector<float> Cylinder::getSideNormals()
{
	const float PI = acos(-1);
	float sectorStep = 2 * PI / sectorCount;
	float sectorAngle;  // radian

	// compute the normal vector at 0 degree first
	// tanA = (baseRadius-topRadius) / height
	float zAngle = atan2(baseRadius - topRadius, height);
	float x0 = cos(zAngle);     // nx
	float y0 = 0;               // ny
	float z0 = sin(zAngle);     // nz

	// rotate (x0,y0,z0) per sector angle
	std::vector<float> normals;
	for (int i = 0; i <= sectorCount; ++i)
	{
		sectorAngle = i * sectorStep;
		normals.push_back(cos(sectorAngle)*x0 - sin(sectorAngle)*y0);   // nx
		normals.push_back(sin(sectorAngle)*x0 + cos(sectorAngle)*y0);   // ny
		normals.push_back(z0);  // nz
		/*
		//debug
		float nx = cos(sectorAngle)*x0 - sin(sectorAngle)*y0;
		float ny = sin(sectorAngle)*x0 + cos(sectorAngle)*y0;
		std::cout << "normal=(" << nx << ", " << ny << ", " << z0
				  << "), length=" << sqrtf(nx*nx + ny*ny + z0*z0) << std::endl;
		*/
	}

	return normals;
}




///////////////////////////////////////////////////////////////////////////////
// generate vertices with flat shading
// each triangle is independent (no shared vertices)
///////////////////////////////////////////////////////////////////////////////
void Cylinder::buildVerticesFlat()
{
	// tmp vertex definition (x,y,z,s,t)
	struct Vertex
	{
		float x, y, z, s, t;
	};
	std::vector<Vertex> tmpVertices;

	int i, j, k;    // indices
	float x, y, z, s, t, radius;

	// put tmp vertices of cylinder side to array by scaling unit circle
	//NOTE: start and end vertex positions are same, but texcoords are different
	//      so, add additional vertex at the end point
	for (i = 0; i <= stackCount; ++i)
	{
		z = -(height * 0.5f) + (float)i / stackCount * height;      // vertex position z
		radius = baseRadius + (float)i / stackCount * (topRadius - baseRadius);     // lerp
		t = 1.0f - (float)i / stackCount;   // top-to-bottom

		for (j = 0, k = 0; j <= sectorCount; ++j, k += 3)
		{
			x = unitCircleVertices[k];
			y = unitCircleVertices[k + 1];
			s = (float)j / sectorCount;

			Vertex vertex;
			vertex.x = x * radius;
			vertex.y = y * radius;
			vertex.z = z;
			vertex.s = s;
			vertex.t = t;
			tmpVertices.push_back(vertex);
		}
	}

	// clear memory of prev arrays
	clearArrays();

	Vertex v1, v2, v3, v4;      // 4 vertex positions v1, v2, v3, v4
	std::vector<float> n;       // 1 face normal
	int vi1, vi2;               // indices
	int index = 0;

	// v2-v4 <== stack at i+1
	// | \ |
	// v1-v3 <== stack at i
	for (i = 0; i < stackCount; ++i)
	{
		vi1 = i * (sectorCount + 1);            // index of tmpVertices
		vi2 = (i + 1) * (sectorCount + 1);

		for (j = 0; j < sectorCount; ++j, ++vi1, ++vi2)
		{
			v1 = tmpVertices[vi1];
			v2 = tmpVertices[vi2];
			v3 = tmpVertices[vi1 + 1];
			v4 = tmpVertices[vi2 + 1];

			// compute a face normal of v1-v3-v2
			n = computeFaceNormal(v1.x, v1.y, v1.z, v3.x, v3.y, v3.z, v2.x, v2.y, v2.z);

			// put quad vertices: v1-v2-v3-v4
			addVertex(v1.x, v1.y, v1.z);
			addVertex(v2.x, v2.y, v2.z);
			addVertex(v3.x, v3.y, v3.z);
			addVertex(v4.x, v4.y, v4.z);

			// put tex coords of quad
			addTexCoord(v1.s, v1.t);
			addTexCoord(v2.s, v2.t);
			addTexCoord(v3.s, v3.t);
			addTexCoord(v4.s, v4.t);

			// put normal
			for (k = 0; k < 4; ++k)  // same normals for all 4 vertices
			{
				addNormal(n[0], n[1], n[2]);
			}

			// put indices of a quad
			addIndices(index, index + 2, index + 1);    // v1-v3-v2
			addIndices(index + 1, index + 2, index + 3);    // v2-v3-v4

			// vertical line per quad: v1-v2
			lineIndices.push_back(index);
			lineIndices.push_back(index + 1);
			// horizontal line per quad: v2-v4
			lineIndices.push_back(index + 1);
			lineIndices.push_back(index + 3);
			if (i == 0)
			{
				lineIndices.push_back(index);
				lineIndices.push_back(index + 2);
			}

			index += 4;     // for next
		}
	}

	// remember where the base index starts
	baseIndex = (unsigned int)indices.size();
	unsigned int baseVertexIndex = (unsigned int)vertices.size() / 3;

	// put vertices of base of cylinder
	z = -height * 0.5f;
	addVertex(0, 0, z);
	addNormal(0, 0, -1);
	addTexCoord(0.5f, 0.5f);
	for (i = 0, j = 0; i < sectorCount; ++i, j += 3)
	{
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];
		addVertex(x * baseRadius, y * baseRadius, z);
		addNormal(0, 0, -1);
		addTexCoord(-x * 0.5f + 0.5f, -y * 0.5f + 0.5f); // flip horizontal
	}

	// put indices for base
	for (i = 0, k = baseVertexIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < sectorCount - 1)
			addIndices(baseVertexIndex, k + 1, k);
		else
			addIndices(baseVertexIndex, baseVertexIndex + 1, k);
	}

	// remember where the top index starts
	topIndex = (unsigned int)indices.size();
	unsigned int topVertexIndex = (unsigned int)vertices.size() / 3;

	// put vertices of top of cylinder
	z = height * 0.5f;
	addVertex(0, 0, z);
	addNormal(0, 0, 1);
	addTexCoord(0.5f, 0.5f);
	for (i = 0, j = 0; i < sectorCount; ++i, j += 3)
	{
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];
		addVertex(x * topRadius, y * topRadius, z);
		addNormal(0, 0, 1);
		addTexCoord(x * 0.5f + 0.5f, -y * 0.5f + 0.5f);
	}

	for (i = 0, k = topVertexIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < sectorCount - 1)
			addIndices(topVertexIndex, k, k + 1);
		else
			addIndices(topVertexIndex, k, topVertexIndex + 1);
	}

	// generate interleaved vertex array as well
	//buildInterleavedVertices();
}


std::vector<float> Cylinder::computeFaceNormal(float x1, float y1, float z1,  // v1
	float x2, float y2, float z2,  // v2
	float x3, float y3, float z3)  // v3
{
	const float EPSILON = 0.000001f;

	std::vector<float> normal(3, 0.0f);     // default return value (0,0,0)
	float nx, ny, nz;

	// find 2 edge vectors: v1-v2, v1-v3
	float ex1 = x2 - x1;
	float ey1 = y2 - y1;
	float ez1 = z2 - z1;
	float ex2 = x3 - x1;
	float ey2 = y3 - y1;
	float ez2 = z3 - z1;

	// cross product: e1 x e2
	nx = ey1 * ez2 - ez1 * ey2;
	ny = ez1 * ex2 - ex1 * ez2;
	nz = ex1 * ey2 - ey1 * ex2;

	// normalize only if the length is > 0
	float length = sqrtf(nx * nx + ny * ny + nz * nz);
	if (length > EPSILON)
	{
		// normalize
		float lengthInv = 1.0f / length;
		normal[0] = nx * lengthInv;
		normal[1] = ny * lengthInv;
		normal[2] = nz * lengthInv;
	}

	return normal;
}
