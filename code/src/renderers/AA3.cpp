#include "renderers/AA3.h"

AA3::AA3(int w, int h) : Renderer(w,h)
{
	theTrack = new TexturedPlane("res/circular_track.jpg");

	glm::mat4 tr[] = {
		glm::mat4(),
		glm::mat4(),
		glm::mat4(),
		glm::mat4(),
		glm::mat4(),
		glm::mat4(),
		glm::mat4(),
		glm::mat4(),
		glm::mat4(),
		glm::mat4()
	};
	cars = new CarSpawner("res/cotxe.obj", tr);

	glm::vec3 treesPiv[] = {
		glm::vec3(0.1f, 0.01f, -0.15f),
		glm::vec3(-0.1f, 0.01f, 0.15f),
		glm::vec3(-0.65f, 0.01f, 0.2f),
		glm::vec3(1.15f, 0.01f, 1.4f),
		glm::vec3(-1.4f, 0.01f, -1.15f)
	};
	trees = new BB_Spawner("res/tree.jpg", treesPiv);
}

AA3::~AA3()
{
	delete theTrack;
	delete cars;
	delete trees;
}

void AA3::render(float dt)
{
	
	HandleCameraMode();
	
	
	glm::mat4 trackTR = glm::translate(glm::mat4(), glm::vec3(0.f, -0.1f, 0.f)) 
		* glm::rotate(glm::mat4(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f))
		* glm::scale(glm::mat4(), glm::vec3(3.75f, 3.75f, 1.f)
	);
	theTrack->setTransform(trackTR, cam);	
	theTrack->draw();

	//FP car
	cars->SetFPCarTr(
		glm::rotate(glm::mat4(), ImGui::GetTime(), glm::vec3(0.f, 1.f, 0.f))
		* glm::translate(glm::mat4(), glm::vec3(1.39f, -0.08f, 0.075f))
		* glm::rotate(glm::mat4(), glm::pi<float>(), glm::vec3(0.f, 1.f, 0.f))
		* glm::scale(glm::mat4(), glm::vec3(0.0225f))
	);


	//other cars
	cars->setCameraParams(cam);
	glm::mat4 npcTR[10];
	for (int i = 1; i < 10; i++)
	{
		npcTR[i] =
			glm::rotate(glm::mat4(), i * ImGui::GetTime() / (i + 1), glm::vec3(0.f, -1.f, 0.f))
			* glm::translate(glm::mat4(), glm::vec3(1.2f, -0.08f, 0.075f))
			* glm::scale(glm::mat4(), glm::vec3(0.02f));
	}
	cars->SetNPCCarsTr(npcTR);
	cars->draw();

	// trees
	trees->SetCameraParams(cam);
	trees->draw();
}

void AA3::renderGUI()
{
	ImGui::Checkbox("Pilot View", &inFP_Mode);
}

void AA3::HandleCameraMode()
{
	if (inFP_Mode)
	{
		blockMouseInput = true;
		//FP mode
		cam._modelView = glm::rotate(glm::mat4(), glm::pi<float>(), glm::vec3(0.f, -1.f, 0.f));
		cam._modelView = glm::translate(cam._modelView, glm::vec3(1.39f, -0.08f, 0.f));
		cam._modelView = glm::rotate(cam._modelView, ImGui::GetTime(),  glm::vec3(0.f, -1.f, 0.f));
		*cam.FOV = 60.f;
	}
	else
	{
		blockMouseInput = false;
		//Free camera mode
		cam._modelView = glm::translate(glm::mat4(), glm::vec3(panv[0], panv[1], panv[2]));
		cam._cameraRotationMat = glm::rotate(glm::mat4(), rota[1], glm::vec3(1.f, 0.f, 0.f));
		cam._cameraRotationMat = glm::rotate(cam._cameraRotationMat, rota[0], glm::vec3(0.f, 1.f, 0.f));
		cam._modelView *= cam._cameraRotationMat;
		*cam.FOV = 70.f;
	}
	cam._MVP = cam._projection * cam._modelView;
}
