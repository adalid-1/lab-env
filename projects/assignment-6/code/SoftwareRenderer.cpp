#include "SoftwareRenderer.h"

void SoftwareRenderer::framebufferSetup(int width, int height)
{	
	//Free previous memmory
	delete frameBuffer;
	//calculate size
	frameBufferSize = width * height * 3;
	//dynamic new float array for rgb
	frameBuffer = new float[frameBufferSize];

}

void SoftwareRenderer::setVxBuffer(float* vertexBuffer)
{
	vxBuffer = vertexBuffer;
}

void SoftwareRenderer::setIxBuffer(int* indexBuffer)
{
	ixBuffer = indexBuffer;
}

float* SoftwareRenderer::getFrameBuffer()
{
	return frameBuffer;
}

int SoftwareRenderer::getFrameBufferSize()
{
	return frameBufferSize;
}
