#pragma once
#include "Renderer.h"
#include "objects/ObjLoader.h"

class AA1 : 
	public Renderer
{
public:
	AA1(int width, int height);
	~AA1();
	void render();

private:
	std::vector<glm::vec3>vertices;
	std::vector<glm::vec2>uvs;
	std::vector<glm::vec3>normals;


};