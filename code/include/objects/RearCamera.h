#pragma once
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <Program.h>
#include <renderers/Renderer.h>
#include <string>
#include <functional>


class RearCamera
{

public:
	RearCamera();
	~RearCamera();

	void RenderRearImage(std::function<void(float)>& rendCallback, float dt, CameraTransforms& cam_ref);

	void UpdateCamData(CameraTransforms camT);
	void Render();

private:
	glm::vec3 position;

	GLuint VAO;
	GLuint VBO;
	GLuint FBO;
	GLuint RBO;
	Program* program;
	GLuint fboTex;
	glm::mat4 objMat = glm::mat4(1.f);

	CameraTransforms camTr;
};

