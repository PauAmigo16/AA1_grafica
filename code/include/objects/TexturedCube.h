#pragma once
#include "Cube.h"
#include "TextureHandler.h"

class TexturedCube : public Cube
{
private:
	TextureHandler* texHandler;

public:
	const float halfSide = 0.45f;

	TexturedCube();
	~TexturedCube();

	void draw() override;
};