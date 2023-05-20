#pragma once
#include "Program.h"
#include "GL/glew.h"
#include "TextureHandler.h"
#include "renderers/Renderer.h"

class TexturedPlane
{
private:
	Program* program;
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	glm::mat4 objMat;
	CameraTransforms cam;

	TextureHandler* texHandler;

public:
	TexturedPlane();
	~TexturedPlane();

	void draw();
	void setTransform(glm::mat4 objMat, CameraTransforms cam);
};

