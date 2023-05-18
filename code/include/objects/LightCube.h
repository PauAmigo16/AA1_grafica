#pragma once
#include "Cube.h"
#include <glm/glm.hpp>
#include <imgui/imgui.h>

class LightCube : public Cube
{
public:
	LightCube();
	~LightCube();
	
	void setPosition(glm::vec3 position);

	glm::vec3 getPosition();
	glm::vec4 getColor();
	float getIntensity();
	float getBrightness();

	void DrawGUI();

private:
	glm::vec3 pos;
	float intensity;
	float brightness;
};

