#include "objects/MyModel.h"

MyModel::MyModel(std::string name, std::string path)
{
	bool res = ObjLoader::LoadOBJ(path.c_str(), vertices, uvs, normals);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Initialize program
	program = new Program(name.c_str());
	program->compileAndAttachShader("shaders/Spaceship.vert", GL_VERTEX_SHADER, "vertex");
	program->compileAndAttachShader("shaders/Spaceship.frag", GL_FRAGMENT_SHADER, "fragment");

	// Bind Attrib locations
	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_Normal");

	// Link program
	program->link();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

MyModel::~MyModel()
{
	glDeleteBuffers(2, VBO);
	glDeleteVertexArrays(1, &VAO);
	delete program;
}

void MyModel::setTransforms(glm::mat4 objMat, CameraTransforms cam)
{
	this->objMat = objMat;
	this->camTr = cam;
}

void MyModel::setColor(glm::vec4 color)
{
	this->color = color;
}

void MyModel::draw()
{
	glBindVertexArray(VAO);
	program->use();
	
	glUniformMatrix4fv(program->getUniform("objMat"), 1, GL_FALSE, glm::value_ptr(objMat));
	glUniformMatrix4fv(program->getUniform("mv_Mat"), 1, GL_FALSE, glm::value_ptr(camTr._modelView));
	glUniformMatrix4fv(program->getUniform("mvpMat"), 1, GL_FALSE, glm::value_ptr(camTr._MVP));
	glUniform4f(program->getUniform("color"), color.r, color.g, color.b, color.w);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	program->unuse();
	glBindVertexArray(0);
}

void MyModel::DrawGUI()
{
}
