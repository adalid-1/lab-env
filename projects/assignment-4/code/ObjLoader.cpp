#include "ObjLoader.h"

void ObjLoader::loadOBJ(const char* filename, vector<GLuint>& indices, vector<float>& data)
{
	//Vertex positions
	vector<Vector4D> vertex_positions;
	vector<Vector4D> vertex_texcoords;
	vector<Vector4D> vertex_normals;

	//Face Vectorsa
	vector<GLint> vertex_position_indices;
	vector<GLint> vertex_texcoord_indices;
	vector<GLint> vertex_normal_indices;

	//Vertex array
	vector<vertex> vertices;

	stringstream ss;
	ifstream in_file(filename);
	string line = "";
	string prefix = "";
	Vector4D temp_vec;
	Vector4D temp_vec2;
	Vector4D temp_vec3;
	GLint temp_glint = 0;
	float x, y, z;


	//This is where the magic happens
	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Could not open file.";


	}
	//Read a line at a time
	while (std::getline(in_file, line)){
		//Get the prefix of the line 
		ss.clear();
		ss.str(line);
		ss >> prefix;
		int verticesInFace = 1;

		if (prefix == "v") //vertex position
		{
			ss >> x >> y >> z;
			temp_vec.setXYZW(x, y, z, 0);
			vertex_positions.push_back(temp_vec);
		}
		else if (prefix == "vt") //texture coordinates
		{
			ss >> x >> y >> z;
			temp_vec2.setXYZW(x, y, 0, 0);
			vertex_texcoords.push_back(temp_vec2);
		}
		else if (prefix == "vn") //normals
		{
			ss >> x >> y >> z;
			temp_vec3.setXYZW(x, y, z, 0);
			vertex_normals.push_back(temp_vec3);
		}
		else if (prefix == "f") //faces
		{
			int counter = 0;
		
			while (ss >> temp_glint) {
				//pushing indicies into arrays
				if (counter == 0)
				{
					vertex_position_indices.push_back(temp_glint);
					//indices.push_back(temp_glint);

				}
				else if (counter == 1) {
					vertex_texcoord_indices.push_back(temp_glint);
					
				}
				else if (counter == 2) {
					vertex_normal_indices.push_back(temp_glint);
				}
				//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					++verticesInFace;
					ss.ignore(1, ' ');
				}
				//Reset counter
				if (counter > 2)
				{
					counter = 0;
				}

			}

		}
		else{}

	
		
		if (verticesInFace == 4)
		{
			GLint endOfVector1 = vertex_position_indices.size() - 1;
			GLint endOfVector2 = vertex_texcoord_indices.size() - 1;
			GLint endOfVector3 = vertex_normal_indices.size() - 1;
			GLint temp_pos = vertex_position_indices[endOfVector1];
			GLint temp_coord = vertex_texcoord_indices[endOfVector2];
			GLint temp_normal = vertex_normal_indices[endOfVector3];

			vertex_position_indices.pop_back();
			vertex_texcoord_indices.pop_back();
			vertex_normal_indices.pop_back();



			vertex_position_indices.push_back(vertex_position_indices[endOfVector1-3]);
			vertex_texcoord_indices.push_back(vertex_texcoord_indices[endOfVector2-3]);
			vertex_normal_indices.push_back(vertex_normal_indices[endOfVector3-3]);

			vertex_position_indices.push_back(vertex_position_indices[endOfVector1-1]);
			vertex_texcoord_indices.push_back(vertex_texcoord_indices[endOfVector2-1]);
			vertex_normal_indices.push_back(vertex_normal_indices[endOfVector3-1]);

			vertex_position_indices.push_back(temp_pos);
			vertex_texcoord_indices.push_back(temp_coord);
			vertex_normal_indices.push_back(temp_normal);
		}
		


		//Debug stuff
		cout << "nr of vertices: " << vertex_positions.size() << "\n";
		
	}
	vertices.resize(vertex_position_indices.size(), vertex());
	//build final array 
	//Load in all indicies
	for (int i = 0; i < vertices.size()-4 ; i++)
	{
		vertices[i].position = vertex_positions[vertex_position_indices[i] - 1];
		vertices[i].textureCoord = vertex_texcoords[vertex_texcoord_indices[i] - 1];
		vertices[i].normal = vertex_normals[vertex_normal_indices[i] - 1];
		//skicka in en färg

	}
	for (int i = 0; i < vertices.size(); i++)
	{
		data.push_back(vertices[i].position.getX());
		data.push_back(vertices[i].position.getY());
		data.push_back(vertices[i].position.getZ());

		data.push_back(vertices[i].textureCoord.getX());
		data.push_back(vertices[i].textureCoord.getY());
/*
		data.push_back(vertices[i].normal.getX());
		data.push_back(vertices[i].normal.getY());
		data.push_back(vertices[i].normal.getZ());
		*/


	}
	for (int i = 0; i < vertices.size(); i++)
	{
		indices.push_back(i);
	}


	cout << "OBJ file loaded! \n";
	//Loaded succ succ
	//return vertices;
}
//
//void ObjLoader::LoadFromFile(const char* filename, std::vector<Vector4D>& out_vertices, std::vector<Vector4D>& out_uvs, std::vector<Vector4D>& out_normals)
//{
//	float x, y, z, w;
//
//	using namespace std;
//	//Temp string for loading each line
//	string line;
//	//Tries to open file 
//	ifstream myfile(filename);
//	FILE* file = fopen(filename, "r");
//	if (file == NULL) {
//		printf("impossible to open the file!\n");
//		return;
//	}
//
//	while (1)
//	{
//		char lineHeader[128];
//		int res = fscanf(file, "%s", lineHeader);
//		if (res == EOF)
//			break;
//
//		//Vertices
//		if (strcmp(lineHeader, "v") == 0){ 
//			fscanf(file, "%f %f %f\n", &x, &y, &z);
//				Vector4D vertex(x,y,z,0);
//
//			temp_vertices.push_back(vertex);
//
//		}
//		//texcoords
//		else if (strcmp(lineHeader, "vt") == 0) {
//			fscanf(file, "%f %f\n", &x, &y);
//			Vector4D vertex(x, y, 0, 0);
//
//			temp_uvs.push_back(vertex);
//
//		}
//		//normals
//		else if (strcmp(lineHeader, "vn") == 0) {
//			fscanf(file, "%f %f %f\n", &x, &y, &z);
//			Vector4D vertex(x, y, z, 0);
//
//			temp_normals.push_back(vertex);
//		}
//		else if (strcmp(lineHeader, "f") == 0) {
//			std::string vertex1, vertex2, vertex3;
//			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
//			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
//			if (matches != 9) {
//				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
//				return;
//			}
//			vertexIndices.push_back(vertexIndex[0]);
//			vertexIndices.push_back(vertexIndex[1]);
//			vertexIndices.push_back(vertexIndex[2]);
//			uvIndices.push_back(uvIndex[0]);
//			uvIndices.push_back(uvIndex[1]);
//			uvIndices.push_back(uvIndex[2]);
//			normalIndices.push_back(normalIndex[0]);
//			normalIndices.push_back(normalIndex[1]);
//			normalIndices.push_back(normalIndex[2]);
//
//			for (unsigned int i=0; i<vertexIndices.size(); i++) {
//				unsigned int vertexIndex = vertexIndices[i];
//				Vector4D vertex = temp_vertices[vertexIndex - 1];
//				out_vertices.push_back(vertex);
//			}
//			for (unsigned int i = 0; i < uvIndices.size(); i++) {
//				unsigned int uvIndex = uvIndices[i];
//				Vector4D uv = temp_uvs[uvIndex - 1];
//				out_uvs.push_back(uv);
//			}
//			for (unsigned int i = 0; i < normalIndices.size(); i++) {
//				unsigned int normalIndex = normalIndices[i];
//				Vector4D normal = temp_normals[normalIndex - 1];
//				out_normals.push_back(normal);
//			}
//		}
//	}
//
//	//cout << x << endl;
//	return;
//}
//
//void ObjLoader::LoadTest()
//{
//
//	LoadFromFile("TestOBJ.obj", o_vertices, o_uvs, o_normals);
//}
