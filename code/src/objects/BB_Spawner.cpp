#include "objects/BB_Spawner.h"

BB_Spawner::BB_Spawner(std::string path, glm::vec3 pivots[])
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glm::vec3 thePivots[5];
	for (int i = 0; i < 5; i++)
	{
		thePivots[i] = pivots[i];
		_objMats[i] = glm::translate(glm::mat4(), pivots[i]);
	}

	// Create the program
	program = new Program("Billboard Spwr");
	program->compileAndAttachShader("shaders/BillboardSpw.vert", GL_VERTEX_SHADER, "BB spw vert");
	program->compileAndAttachShader("shaders/BillboardSpw.geom", GL_GEOMETRY_SHADER, "BB spw geom");
	program->compileAndAttachShader("shaders/BillboardSpw.frag", GL_FRAGMENT_SHADER, "BB spw frag");
	program->bindAttribLocation(0, "in_Pivot");
	program->link();

	// Create & bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);

	// upload data
	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(thePivots), &thePivots[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	const std::vector<std::string> paths(1, path);
	textureH = new TextureHandler(paths);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

BB_Spawner::~BB_Spawner()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	delete program;
	delete textureH;
}

void BB_Spawner::SetCameraParams(CameraTransforms cam)
{
	this->cam = cam;
}

void BB_Spawner::SetPivots(glm::vec3 pivots[])
{
	for (int i = 0; i < 5; i++)
	{
		_objMats[i] = glm::translate(glm::mat4(), pivots[i]);
	}
}

void BB_Spawner::Resize(glm::vec2 newSize)
{
	size = newSize;
}

void BB_Spawner::draw()
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

	Resize(glm::vec2(0.1f, 0.13f));

	glUniform2f(program->getUniform("size"),
		size.x, size.y
	);
	glUniformMatrix4fv(
		program->getUniform("proj_Mat"),
		1, GL_FALSE, glm::value_ptr(cam._projection)
	);
	glUniform1f(program->getUniform("text"), textureH->GetTexID(0));

	glUniformMatrix4fv(program->getUniform("objMat"), 5, GL_FALSE, glm::value_ptr(_objMats[0]));
	
	glBindTexture(GL_TEXTURE_2D, textureH->GetTexID(0));
	glDrawArraysInstanced(GL_POINTS, 0, 1, 5);
	glBindTexture(GL_TEXTURE_2D, 0);

	program->unuse();
	glBindVertexArray(0);
	
}
