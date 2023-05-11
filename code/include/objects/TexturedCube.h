#pragma once
#include "Cube.h"

class TexturedCube : public Cube
{
private:
	GLuint texture[6];

public:
	const float halfSide = 0.45f;

	TexturedCube();
	~TexturedCube();

	void LoadImage(int text);
	void draw() override;
};

