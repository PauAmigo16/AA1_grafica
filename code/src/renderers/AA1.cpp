#include "renderers/AA1.h"

AA1::AA1(int width, int height) : Renderer(width, height)
{
	bool res = ObjLoader::LoadOBJ("src/objects/QB.obj", vertices, uvs, normals);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(2, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Initialize program
	program = new Program("Cube");
	program->compileAndAttachShader("shaders/Cube.vert", GL_VERTEX_SHADER, "vertex");
	program->compileAndAttachShader("shaders/Cube.frag", GL_FRAGMENT_SHADER, "fragment");

	// Bind Attrib locations
	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_Normal");

	// Link program
	program->link();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

AA1::~AA1()
{
	glDeleteBuffers(2, VBO);
	glDeleteVertexArrays(1, &VAO);
	delete program;
}

void AA1::render()
{
	glBindVertexArray(VAO);
	program->use();

	glUniformMatrix4fv(program->getUniform("objMat"), 1, GL_FALSE, glm::value_ptr(objMat));
	glUniformMatrix4fv(program->getUniform("mv_Mat"), 1, GL_FALSE, glm::value_ptr(cam._modelView));
	glUniformMatrix4fv(program->getUniform("mvpMat"), 1, GL_FALSE, glm::value_ptr(cam._MVP));
	glUniform4f(program->getUniform("color"), color.r, color.g, color.b, color.w);

	glDrawArrays(GL_TRIANGLES, 0, 48);

	program->unuse();
	glBindVertexArray(0);
}