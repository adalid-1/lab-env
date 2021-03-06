#pragma once
#include "core/app.h"
#include "config.h"
#include <string>
#include "render/window.h"
#include <iostream>
#include "stb_image.h"

class TextureResource
{
public:
	int width, height, nrChannels;
	unsigned char *data;
	unsigned int texture;

	void setup();
	void activate();
	void LoadFromFile(const char* fileName);

	TextureResource();
	~TextureResource();
};

