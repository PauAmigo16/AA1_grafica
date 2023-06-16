#include "objects/CarSpawner.h"

CarSpawner::CarSpawner(std::string path, glm::mat4 objM[])
{
	ObjLoader::LoadOBJ(path.c_str(), verts, uvs, normals);

	// Create the program
	program = new Program("CarSpawner");
	program->compileAndAttachShader(std::string("shaders/CarSpw.vert").c_str(), GL_VERTEX_SHADER, "CarSpw VS");
	program->compileAndAttachShader(std::string("shaders/CarSpw.frag").c_str(), GL_FRAGMENT_SHADER, "CarSpw FS");
	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_Normal");
	program->link();

	// Create & bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(3, VBO);

	// upload data
	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), &verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	for (int i = 0; i < 10; i++)
	{
		_objMats[i] = objM[i];
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

CarSpawner::~CarSpawner()
{
	glDeleteBuffers(3, VBO);
	glDeleteVertexArrays(1, &VAO);
	delete program;
}

void CarSpawner::setCameraParams(CameraTransforms cam)
{
	this->cam = cam;
}

void CarSpawner::draw()
{
	glBindVertexArray(VAO);
	program->use();

	glUniformMatrix4fv(
		program->getUniform("mv_Mat"),
		1, GL_FALSE, glm::value_ptr(cam._modelView)
	);
	glUniformMatrix4fv(
		program->getUniform("mvpMat"),
		1, GL_FALSE, glm::value_ptr(cam._MVP)
	);
	
	glUniformMatrix4fv(program->getUniform("objMats"), 10, GL_FALSE, glm::value_ptr(_objMats[0]));
	
	glDrawArraysInstanced(GL_TRIANGLES, 0, verts.size(), 10);

	program->unuse();
	glBindVertexArray(0);
}

void CarSpawner::RenderGUI()
{
}

glm::mat4 CarSpawner::GetPF_Tr()
{
	return _objMats[0];
}

void CarSpawner::SetFPCarTr(glm::mat4 objMat_p)
{
	_objMats[0] = objMat_p;
}

void CarSpawner::SetNPCCarsTr(glm::mat4 objMats[])
{
	for (int i = 1; i < 10; i++)
	{
		_objMats[i] = objMats[i];
	}
}

glm::mat4* CarSpawner::GetObjMats()
{
	return _objMats;
}


