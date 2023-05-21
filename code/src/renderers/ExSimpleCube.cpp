#include <renderers/ExSimpleCube.h>

ExSimpleCube::ExSimpleCube(int width, int height) : Renderer(width, height)
{
	cube = new Cube();
	cube->setColor(glm::vec4(1.f, 0.f, 0.f, 1.f));

}

ExSimpleCube::~ExSimpleCube()
{
	delete cube;
}

void ExSimpleCube::render(float dt)
{
	cube->setTransforms(
		glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -1.5f)) *
		cam._cameraRotationMat *
		glm::scale(glm::mat4(), glm::vec3(.2f)),
		cam
	);

	cube->Draw();

}

void ExSimpleCube::renderGUI()
{
}
