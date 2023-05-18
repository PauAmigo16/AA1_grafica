#pragma once
#include <glm/glm.hpp>

class LightReciever
{
public:
	void SetLightPos(glm::vec3 lPos);
	void SetLightColor(glm::vec4 lColor);
	void SetLightIntensity(float power);
	void SetBrightness(float bright);
	void SetAmbient(float amb);
	void SetDiffuse(float diff);
	void SetSpecular(float spec);


protected:
	glm::vec3 lightPos;
	glm::vec4 lightColor;
	float lightIntensity;
	float brightness;

	float kAmbient;
	float kDiffuse;
	float kSpecular;
};