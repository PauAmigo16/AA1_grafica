#pragma once
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <Program.h>
#include <renderers/Renderer.h>
#include <string>
#include "objects/TextureHandler.h"

class BB_Spawner
{
public:
	BB_Spawner(std::string path, glm::vec3 pivots[]);
	~BB_Spawner();

	void SetCameraParams(CameraTransforms cam);
	void SetPivots(glm::vec3 pivots[]);
	void Resize(glm::vec2 newSize);
	void draw();

private:
	GLuint VAO;
	GLuint VBO;
	Program* program;
	glm::mat4 _objMats[5];
	glm::vec2 size;

	CameraTransforms cam;
	TextureHandler* textureH;
};

