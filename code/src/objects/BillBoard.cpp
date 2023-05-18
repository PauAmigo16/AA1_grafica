#include "objects/BillBoard.h"

BillBoard::BillBoard(glm::vec3 pivot): _pivot(pivot)
{
	// Initialize buffers
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &_pivot, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Initialize program
	program = new Program("BillBoard");
	program->compileAndAttachShader("shaders/Billboard.vert", GL_VERTEX_SHADER, "BB vertex");
	program->compileAndAttachShader("shaders/Billboard.geom", GL_GEOMETRY_SHADER, "BB geometry");
	program->compileAndAttachShader("shaders/Billboard.frag", GL_FRAGMENT_SHADER, "BB fragment");

	// Bind Attrib locations
	program->bindAttribLocation(0, "thePivot");

	// Link program
	program->link();


	// Tranform
	objMat = glm::translate(glm::mat4(), _pivot);
	_size = glm::vec2(4.f);
	
	// Load texture
	std::vector<std::string> thePaths;
	thePaths.push_back("res/wall_texture.jpg");


	texHandler = new TextureHandler(thePaths);
}

BillBoard::~BillBoard()
{
	glDeleteBuffers(1, &VAO);
	glDeleteVertexArrays(1, &VAO);
	delete texHandler;
}

void BillBoard::UpdateTransform(glm::vec3 pivot, CameraTransforms camTr)
{
	_pivot = pivot;
	objMat = glm::translate(glm::mat4(), _pivot);
	cam = camTr;
}

void BillBoard::draw()
{
	glBindVertexArray(VAO);
	program->use();

	glUniformMatrix4fv(
		program->getUniform("objMat"),
		1, GL_FALSE, glm::value_ptr(objMat)
	);
	glUniformMatrix4fv(
		program->getUniform("mv_Mat"),
		1, GL_FALSE, glm::value_ptr(cam._modelView)
	);
	glUniformMatrix4fv(
		program->getUniform("mvpMat"),
		1, GL_FALSE, glm::value_ptr(cam._MVP)
	);
	glUniform2f(program->getUniform("size"),
		_size.x, _size.y
	);
	glUniformMatrix4fv(
		program->getUniform("proj_Mat"),
		1, GL_FALSE, glm::value_ptr(cam._projection)
	);
	glUniform1f(
		program->getUniform("text"), 
		texHandler->GetTexID(0)
	);

	glBindTexture(GL_TEXTURE_2D, texHandler->GetTexID(0));
	glDrawArrays(GL_POINTS, 0, 1);
	glBindTexture(GL_TEXTURE_2D, 0);

	program->unuse();
	glBindVertexArray(0);

}
