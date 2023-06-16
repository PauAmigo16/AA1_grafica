#pragma once
#include <GL/glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <Program.h>
#include <renderers/Renderer.h>
#include <vector>
#include <string>
#include <objects/ObjLoader.h>

class CarSpawner
{
public:
	CarSpawner(std::string path, glm::mat4 objM[]);
	~CarSpawner();

	//void setTransforms(std::vector<glm::mat4> objMats, CameraTransforms cam);
	void setCameraParams(CameraTransforms cam);
	void draw();
	void RenderGUI();

	glm::mat4 GetPF_Tr();
	void SetFPCarTr(glm::mat4 objMat_p);
	void SetNPCCarsTr(glm::mat4 objMats[]);
	glm::mat4* GetObjMats();

private:
	GLuint VAO;
	GLuint VBO[3];
	Program* program;
	glm::mat4 _objMats[10];

	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	CameraTransforms cam;
};

