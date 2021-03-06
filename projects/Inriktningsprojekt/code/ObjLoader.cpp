#include "ObjLoader.h"

void ObjLoader::loadOBJ(const char* filename, vector<GLuint>& indices, vector<float>& data)
{
	//Vertex data
	vector<Vector4D> vertex_positions;
	vector<Vector4D> vertex_texcoords;
	vector<Vector4D> vertex_normals;

	//Face Vectors
	vector<GLint> vertex_position_indices;
	vector<GLint> vertex_texcoord_indices;
	vector<GLint> vertex_normal_indices;

	//Assembly Vertex array
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
	

	//check if file is open
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
		//Counter to spot quads
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

	
		//Triangulate quads
		if (verticesInFace == 4)
		{
			GLint endOfVector1 = vertex_position_indices.size() - 1;
			GLint endOfVector2 = vertex_texcoord_indices.size() - 1;
			GLint endOfVector3 = vertex_normal_indices.size() - 1;
			//Saves the index of the fourth vertex in face to a temp variable
			GLint temp_pos = vertex_position_indices[endOfVector1];
			GLint temp_coord = vertex_texcoord_indices[endOfVector2];
			GLint temp_normal = vertex_normal_indices[endOfVector3];
			//removes forth index 
			vertex_position_indices.pop_back();
			vertex_texcoord_indices.pop_back();
			vertex_normal_indices.pop_back();


			//constructs second triangle
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
		


	
		
	}
	vertices.resize(vertex_position_indices.size(), vertex());
	//build final array 
	//Load in all indicies
	for (int i = 0; i < vertices.size() ; i++)
	{
		vertices[i].position = vertex_positions[vertex_position_indices[i] - 1];
		vertices[i].textureCoord = vertex_texcoords[vertex_texcoord_indices[i] - 1];
		vertices[i].normal = vertex_normals[vertex_normal_indices[i] - 1];
		//skicka in en färg

	}
	//stuffs vertex data into a float vector
	for (int i = 0; i < vertices.size(); i++)
	{
		data.push_back(vertices[i].position.getX());
		data.push_back(vertices[i].position.getY());
		data.push_back(vertices[i].position.getZ());

		data.push_back(vertices[i].textureCoord.getX());
		data.push_back(vertices[i].textureCoord.getY());

		data.push_back(vertices[i].normal.getX());
		data.push_back(vertices[i].normal.getY());
		data.push_back(vertices[i].normal.getZ());
	}
	//triangles are already in order 
	for (int i = 0; i < vertices.size(); i++)
	{
		indices.push_back(i);
	}


	cout << "OBJ file loaded! \n";

}
