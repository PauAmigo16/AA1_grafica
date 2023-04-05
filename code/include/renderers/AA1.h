#pragma once
#include "Renderer.h"
#include "objects/MyModel.h"

class AA1 : public Renderer
{
public:
	AA1(int width, int height);
	~AA1();
	void render(float dt) override;

private:
	MyModel* theModel;
	/*std::vector<glm::vec3>vertices;
	std::vector<glm::vec2>uvs;
	std::vector<glm::vec3>normals;

	glm::vec4 color;
	glm::mat4 objMat;

	GLuint VAO;
	GLuint VBO[2];
	Program* program; */
};