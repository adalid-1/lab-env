#pragma once
#include "core/app.h"
#include "config.h"
#include <string>
#include "render/window.h"
#include <iostream>


#include "stb_image.h"

// Basic usage (see HDR discussion below for HDR usage):
//    int x,y,n;
//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
//    // ... process data if not NULL ...
//    // ... x = width, y = height, n = # 8-bit components per pixel ...
//    // ... replace '0' with '1'..'4' to force that many components per pixel
//    // ... but 'n' will always be the number that it would have been if you said 0
//    stbi_image_free(data)
//
// Standard parameters:
//    int *x                 -- outputs image width in pixels
//    int *y                 -- outputs image height in pixels
//    int *channels_in_file  -- outputs # of image components in image file
//    int desired_channels   -- if non-zero, # of image components requested in result


class TextureResource
{
public:

	int width, height, nrChannels;
	unsigned char *data;
	unsigned int texture;
	std::string fileName = "resources/textures/wall.jpg";

	void setup();
	void activate();
	void LoadFromFile(const char* fileName);

	TextureResource();
	~TextureResource();

	void cleanup(); 

};

