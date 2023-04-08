#include "objects/LightCube.h"

LightCube::LightCube() : Cube()
{
	intensity = 20.f;
	brightness = 8.f;
	// Define vertexs, norms and indexs
	const float halfW = 0.5f;

	/*   4---------7
		/|        /|
	   / |       / |
	  5---------6  |
	  |  0------|--3
	  | /       | /
	  |/        |/
	  1---------2
	 */

	glm::vec3 verts[] = {
		glm::vec3(-halfW, -halfW, -halfW),
		glm::vec3(-halfW, -halfW,  halfW),
		glm::vec3(halfW, -halfW,  halfW),
		glm::vec3(halfW, -halfW, -halfW),
		glm::vec3(-halfW,  halfW, -halfW),
		glm::vec3(-halfW,  halfW,  halfW),
		glm::vec3(halfW,  halfW,  halfW),
		glm::vec3(halfW,  halfW, -halfW)
	};
	glm::vec3 norms[] = {
		glm::vec3(0.f, -1.f,  0.f),
		glm::vec3(0.f,  1.f,  0.f),
		glm::vec3(-1.f,  0.f,  0.f),
		glm::vec3(1.f,  0.f,  0.f),
		glm::vec3(0.f,  0.f, -1.f),
		glm::vec3(0.f,  0.f,  1.f)
	};

	glm::vec3 cubeVerts[] = {
		verts[1], verts[0], verts[2], verts[3],
		verts[5], verts[6], verts[4], verts[7],
		verts[1], verts[5], verts[0], verts[4],
		verts[2], verts[3], verts[6], verts[7],
		verts[0], verts[4], verts[3], verts[7],
		verts[1], verts[2], verts[5], verts[6]
	};
	glm::vec3 cubeNorms[] = {
		norms[0], norms[0], norms[0], norms[0],
		norms[1], norms[1], norms[1], norms[1],
		norms[2], norms[2], norms[2], norms[2],
		norms[3], norms[3], norms[3], norms[3],
		norms[4], norms[4], norms[4], norms[4],
		norms[5], norms[5], norms[5], norms[5]
	};
	GLubyte cubeIdx[] = {
		0, 1, 2, 3, UCHAR_MAX,
		4, 5, 6, 7, UCHAR_MAX,
		8, 9, 10, 11, UCHAR_MAX,
		12, 13, 14, 15, UCHAR_MAX,
		16, 17, 18, 19, UCHAR_MAX,
		20, 21, 22, 23, UCHAR_MAX
	};

	// Initialize buffers
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(3, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(cubeVerts),
		cubeVerts,
		GL_STATIC_DRAW);
	glVertexAttribPointer(
		(GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNorms), cubeNorms, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glPrimitiveRestartIndex(UCHAR_MAX);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIdx), cubeIdx, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Initialize program
	program = new Program("LightCube");
	program->compileAndAttachShader("shaders/Cube.vert", GL_VERTEX_SHADER, "vertex");
	program->compileAndAttachShader("shaders/Cube.frag", GL_FRAGMENT_SHADER, "fragment");

	// Bind Attrib locations
	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_Normal");

	// Link program
	program->link();
}

LightCube::~LightCube()
{
}

void LightCube::setPosition(glm::vec3 position)
{
	pos = position;
}

glm::vec3 LightCube::getPosition()
{
	return pos;
}

glm::vec4 LightCube::getColor()
{
	return color;
}

float LightCube::getIntensity()
{
	return intensity;
}

float LightCube::getBrightness()
{
	return brightness;
}

void LightCube::DrawGUI()
{
	ImGui::Text("Light");
	ImGui::SliderFloat4("color", &color.r, 0.f, 1.f);
	ImGui::SliderFloat("position x", &pos.x, -6.f, 6.f);
	ImGui::SliderFloat("position y", &pos.y, -1.f, 8.f);
	ImGui::SliderFloat("position z", &pos.z, -6.f, 6.f);
	ImGui::SliderFloat("intensity", &intensity, 0.f, 80.f);
	ImGui::SliderFloat("brightness", &brightness, 1.f, 64.f);
}
