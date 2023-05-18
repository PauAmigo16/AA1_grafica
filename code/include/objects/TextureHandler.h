#pragma once
#include <vector>
#include <GL/glew.h>
#include <string>
#include <iostream>


class TextureHandler
{
private:
	int w, h, n;
	std::vector<GLuint> textures;

public:
	TextureHandler(const std::vector<std::string>& paths);
	~TextureHandler();

	GLuint GetTexID(int index) const;
};

