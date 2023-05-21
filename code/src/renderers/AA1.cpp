#include "renderers/AA1.h"

AA1::AA1(int width, int height) : Renderer(width, height)
{
	theModel = new MyModel("Object xdd", "src/objects/dragon.obj");
	theModel->setColor(glm::vec4(0.f, .7f,0.f, 1.f));
	theLight = new LightCube();
	theLight->setColor(glm::vec4(0.f, .7f, 0.f, 1.f));
	theLight->setPosition(glm::vec3(.0f, 5.f, -2.f));
	theModel->SetAmbient(0.4f);
	theModel->SetDiffuse(0.55f);
	theModel->SetSpecular(0.25f);
	theCube = new TexturedCube();
	billboard = new BillBoard(glm::vec3(0.f, 0.f, -6.f));
}

AA1::~AA1()
{
	delete theModel;
	delete theLight;
}

void AA1::render(float dt)
{
	theModel->setTransforms(
		glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -2.f)) * 
		glm::scale(glm::mat4(), glm::vec3(0.1f)),
		cam
	);

	theLight->setTransforms(
		glm::translate(glm::mat4(), theLight->getPosition()) *
		glm::scale(glm::mat4(), glm::vec3(0.3f)),
		cam
	);

	theCube->setTransforms(
		glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, 0.f)),
		cam
	);

	billboard->UpdateTransform(glm::vec3(0.f, 1.5f, -8.f), cam);

	theModel->SetLightPos(theLight->getPosition());
	theModel->SetLightColor(theLight->getColor());
	theModel->SetLightIntensity(theLight->getIntensity());
	theModel->SetBrightness(theLight->getBrightness());

	theModel->Update(dt);

	theModel->Draw();	
	theLight->Draw();
	theCube->Draw();
	billboard->Draw();
}

void AA1::renderGUI()
{
	theLight->DrawGUI();
	ImGui::Spacing();
	theModel->DrawGUI();
	theCube->DrawGUI();
}
