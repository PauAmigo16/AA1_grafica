#pragma once
#include "Renderer.h"
#include "objects/MyModel.h"
#include "objects/LightCube.h"

class AA1 : public Renderer
{
public:
	AA1(int width, int height);
	~AA1();
	void render(float dt) override;
	void renderGUI() override;


private:
	MyModel* theModel;
	LightCube* theLight;
	
};