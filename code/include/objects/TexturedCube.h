#pragma once
#include "TexturedPlane.h"
#include "Program.h"
#include <renderers/Renderer.h>
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>

class TexturedCube
{
private:
	TexturedPlane* cube[6];

	glm::mat4 objMat;
	CameraTransforms cam;
public:
	const float halfSide = 0.45f;

	TexturedCube();
	~TexturedCube();

	void draw();

	void setTransforms(glm::mat4 _objMat, CameraTransforms cam);
};