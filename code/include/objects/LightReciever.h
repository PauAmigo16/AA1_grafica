#pragma once
#include <glm/glm.hpp>

class LightReciever
{
public:
	void SetLightPos(glm::vec3 lPos);
	void SetLightColor(glm::vec4 lColor);

protected:
	glm::vec3 lightPos;
	glm::vec4 lightColor;

	float lightPower;
};