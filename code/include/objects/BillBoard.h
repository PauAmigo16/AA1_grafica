#pragma once
#include "Program.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "renderers/Renderer.h"
#include "objects/TextureHandler.h"

class BillBoard
{
private:
	TextureHandler* texHandler;

	glm::mat4 objMat;
	glm::vec3 _pivot;
	glm::vec2 _size;
	
	GLuint VAO;
	GLuint VBO;
	Program* program;
	CameraTransforms cam;

public:
	BillBoard(glm::vec3 pivot);
	~BillBoard();

	void UpdateTransform(glm::vec3 pivot, CameraTransforms camTr);

	void draw();
	//void drawGUI();	
};

