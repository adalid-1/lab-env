#pragma once
#include "Vector4D.h"
#include "Matrix4D.h"

class SoftwareRenderer {
public:
	float* vxBuffer;
	int* ixBuffer;
	float* frameBuffer;
	int frameBufferSize = 0; 
	
	void framebufferSetup(int width, int height);
	void setVxBuffer(float* vertexBuffer);
	void setIxBuffer(int* indexBuffer);
	float* getFrameBuffer();
	int getFrameBufferSize();


	void vertexShaderSetup();
	void fragmentShaderSetup();
};

/*
The goal is to make a software rasterizer that can draw textured
and lit triangles into an image buffer. Upload image buffer to opengl
to render it as a quad.

1. Software renderer class functions:
	- Adding vertex buffer and indexbuffer
		should return a handle to be used with draw
	- Setting up framebuffer with arbitrary dimensions
	- Getting pointer to the framebuffer
	- Getting size of framebuffer

	- Setting a vertex shader by providing a lambda function as an argument
	- Setting a pixel shader by providing a lamda func -II-
	- Setting a model view projection matrix 
	- Setting a texture resource to texture the mesh with
	- Rasterizing a triangle
	- Drawing an indexbuffer to the framebuffer by passing 
	the bufferhandle as an argument.
		



*/