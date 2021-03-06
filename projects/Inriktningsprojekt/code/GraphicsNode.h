
#pragma once
#include "core/app.h"
#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include "ObjLoader.h"
#include <memory>

/*
Graphics Node Instructions
Combine all the resources into a GraphicsNode class. It should contain MeshResource, TextureResource, ShaderObject and a transform.
1. Store (smart) pointers to the resources and shader objects.
2. Add get/set functions for all the resource types.
3. Add a draw function that will bind the resource objects, apply the transform and finally render the object. 
4. It has to be possible to have multiple  instances of GraphicsNode
*/

class GraphicsNode {
public:
	GraphicsNode();

	//Shared ptrs to resources
	std::shared_ptr<MeshResource> meshR;
	std::shared_ptr<TextureResource> texR;
	std::shared_ptr<ShaderObject> ShaderO;


	//position and rotation
	Matrix4D transform; 

	//First time instantiates the resources
	void pointerSetup();
	//Calls setup functions for each resource
	void setup();
	void setup(const char* modelPath, const char* texturePath);
	void setupAndGenerateTree(std::vector<Segment> segmentList);
	//calls the draw functions required every frame
	void draw();

	//Getfunctions for shared ptrs 
	std::shared_ptr<MeshResource> getMeshR();
	std::shared_ptr<TextureResource> getTextureR();
	std::shared_ptr<ShaderObject> getShaderO();


	//Condensed get function for every shared ptr
	void getPtrsFromOtherNode(GraphicsNode& otherNode);

	//Setting shared ptrs 
	void setMeshR(std::shared_ptr<MeshResource> meshRptr);
	void setTextureR(std::shared_ptr<TextureResource> textureRptr);
	void setShaderO(std::shared_ptr<ShaderObject> shaderOptr);

};