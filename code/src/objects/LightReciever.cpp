#include "objects/LightReciever.h"

void LightReciever::SetLightPos(glm::vec3 lPos)
{
	lightPos = lPos;
}

void LightReciever::SetLightColor(glm::vec4 lColor)
{
	lightColor = lColor;
}

void LightReciever::SetLightIntensity(float power)
{
	lightIntensity = power;
}

void LightReciever::SetBrightness(float bright)
{
	brightness = bright;
}

void LightReciever::SetAmbient(float amb)
{
	kAmbient = amb;
}

void LightReciever::SetDiffuse(float diff)
{
	kDiffuse = diff;
}

void LightReciever::SetSpecular(float spec)
{
	kSpecular = spec;
}
