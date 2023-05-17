#pragma once
#include "TextureHandler.h"
#include "Program.h"
#include <renderers/Renderer.h>
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>

class TexturedCube
{
private:
	TextureHandler* texHandler;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	Program* program;

	glm::mat4 objMat;
	CameraTransforms cam;
	glm::vec4 color;
public:
	const float halfSide = 0.45f;

	TexturedCube();
	~TexturedCube();

	void draw();

	void setTransforms(glm::mat4 objMat, CameraTransforms cam);
	void setColor(glm::vec4 color);
};