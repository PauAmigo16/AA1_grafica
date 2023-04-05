#include "renderers/AA1.h"

AA1::AA1(int width, int height) : Renderer(width, height)
{
	theModel = new MyModel("Object xdd", "src/objects/Intergalactic_Spaceship.obj");
	theModel->setColor(glm::vec4(0.721f, 0.8f, 0.917f, 1.f));
}

AA1::~AA1()
{
	delete theModel;
}

void AA1::render(float dt)
{
	theModel->setTransforms(
		glm::translate(glm::mat4(), glm::vec3(0.f, 0.2f, -2.f)) * 
		glm::scale(glm::mat4(), glm::vec3(0.1f)),

		cam
	);

	theModel->draw();	
}