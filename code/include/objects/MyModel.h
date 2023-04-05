#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <Program.h>
#include <renderers/Renderer.h>
#include "ObjLoader.h"
#include "LightReciever.h"

class MyModel : public LightReciever
{
public:
	MyModel(std::string name, std::string path);
	~MyModel();

	void setTransforms(glm::mat4 objMat, CameraTransforms cam);
	void setColor(glm::vec4 color);
	void draw();

	void DrawGUI();

private:
	std::vector<glm::vec3>vertices;
	std::vector<glm::vec2>uvs;
	std::vector<glm::vec3>normals;

	glm::vec4 color;
	glm::mat4 objMat;

	CameraTransforms camTr;

	GLuint VAO;
	GLuint VBO[2];
	Program* program;
};