
#pragma once


#include "core/app.h"
#include "MeshResource.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include "ObjLoader.h"

#include <memory>

/*
Graphics Node
Combine all the resources into a GraphicsNode class. It should contain MeshResource, TextureResource, ShaderObject and a transform.
1. Store (smart) pointers to the resources and shader objects.
2. Add get/set functions for all the resource types.
3. Add a draw function that will bind the resource objects, apply the transform and finally render the object. 
4. It has to be possible to have multiple  instances of GraphicsNode
*/

class GraphicsNode {
public:
	std::shared_ptr<MeshResource> meshR;
	//MeshResource meshR;
	std::shared_ptr<TextureResource> texR;
	std::shared_ptr<ShaderObject> ShaderO;
	std::shared_ptr<ObjLoader> O_Loader;
	Matrix4D transform; 
	GraphicsNode();

	void pointerSetup();
	void setup();
	void draw();

	std::shared_ptr<MeshResource> getMeshR();
	std::shared_ptr<TextureResource> getTextureR();
	std::shared_ptr<ShaderObject> getShaderO();


	std::shared_ptr<ObjLoader> getObjLoader();

	void setMeshR(std::shared_ptr<MeshResource> meshRptr);
	void setTextureR(std::shared_ptr<TextureResource> textureRptr);
	void setShaderO(std::shared_ptr<ShaderObject> shaderOptr);
	void setObjLoader(std::shared_ptr<ObjLoader> objptr);

	void getPtrsFromOtherNode(GraphicsNode& otherNode);

};