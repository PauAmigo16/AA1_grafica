#include "objects/TexturedCube.h"

TexturedCube::TexturedCube()
{
	float vertices[]{
		// Positions                        // Texture coords
		 halfSide,  halfSide, halfSide,     1.f, 1.f,    // Front top right
		-halfSide,  halfSide, halfSide,     0.f, 1.f,    // Front top left
		-halfSide, -halfSide, halfSide,     0.f, 0.f,    // Front bottom left
		 halfSide, -halfSide, halfSide,     1.f, 0.f,    // Front bottom right

		 halfSide,  halfSide, -halfSide,    1.f, 1.f,    // Right top right
		 halfSide,  halfSide,  halfSide,    0.f, 1.f,    // Right top left
		 halfSide, -halfSide,  halfSide,    0.f, 0.f,    // Right bottom left
		 halfSide, -halfSide, -halfSide,    1.f, 0.f,    // Right bottom right 

		 halfSide,  halfSide, -halfSide,    1.f, 1.f,    // Top top right
		-halfSide,  halfSide, -halfSide,    0.f, 1.f,    // Top top left
		-halfSide,  halfSide,  halfSide,    0.f, 0.f,    // Top bottom left
		 halfSide,  halfSide,  halfSide,    1.f, 0.f,    // Top bottom right

		-halfSide,  halfSide,  halfSide,    1.f, 1.f,    // Left top right
		-halfSide,  halfSide, -halfSide,    0.f, 1.f,    // Left top left
		-halfSide, -halfSide, -halfSide,    0.f, 0.f,    // Left bottom left
		-halfSide, -halfSide,  halfSide,    1.f, 0.f,    // Left bottom right

		 halfSide, -halfSide,  halfSide,    1.f, 1.f,    // Bottom top right
		-halfSide, -halfSide,  halfSide,    0.f, 1.f,    // Bottom top left
		-halfSide, -halfSide, -halfSide,    0.f, 0.f,    // Bottom bottom left
		 halfSide, -halfSide, -halfSide,    1.f, 0.f,    // Bottom bottom right

		-halfSide,  halfSide, -halfSide,    1.f, 1.f,    // Back top right
		 halfSide,  halfSide, -halfSide,    0.f, 1.f,    // Back top left
		 halfSide, -halfSide, -halfSide,    0.f, 0.f,    // Back bottom left
		-halfSide, -halfSide, -halfSide,    1.f, 0.f,    // Back bottom right
	};

	unsigned int indices[]{
		2, 3, 1,         // Front top triangle
		3, 1, 0,        // Front bottom triangle
		UCHAR_MAX,

		6, 7, 5,        // Right top triangle
		7, 5, 4,        // Right bottom triangle
		UCHAR_MAX,
		10, 11, 9,      // Top top trinagle
		11, 9, 8,       // Top bottom triangle
		UCHAR_MAX,

		14, 15, 13,     // Left top triangle
		15, 13, 12,     // Left bottom triangle
		UCHAR_MAX,

		18, 19, 17,     // Bottom top triangle
		19, 17, 16,     // Bottom bottom triangle
		UCHAR_MAX,

		22, 23, 21,     // Back top triangle
		23, 21, 20, 
		UCHAR_MAX		// Back bottom triangle
	};

	// Bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// EBO
	glPrimitiveRestartIndex(UCHAR_MAX);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Define the position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Define texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(float),            // Stride ->  v, x, y, z, u  (float)
		(void*)(3 * sizeof(float))    // Offset
	);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	program = new Program("TexturedQB");
	program->compileAndAttachShader(std::string("shaders/").append("QB").append(".vert").c_str(), GL_VERTEX_SHADER, std::string("TexturedCube").append(" VS").c_str());
	program->compileAndAttachShader(std::string("shaders/").append("QB").append(".geom").c_str(), GL_GEOMETRY_SHADER, std::string("TexturedCube").append(" GS").c_str());
	program->compileAndAttachShader(std::string("shaders/").append("QB").append(".frag").c_str(), GL_FRAGMENT_SHADER, std::string("TexturedCube").append(" FS").c_str());
	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_UVs");
	program->link();

	// Load texture
	std::vector<std::string> thePaths;
	thePaths.push_back("res/gato.jpg");
	thePaths.push_back("res/gato.jpg");
	thePaths.push_back("res/gato.jpg");
	thePaths.push_back("res/gato.jpg");
	thePaths.push_back("res/gato.jpg");
	thePaths.push_back("res/gato.jpg");

	texHandler = new TextureHandler(thePaths);
}

TexturedCube::~TexturedCube()
{
	delete program;
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	delete texHandler;
}

void TexturedCube::setTransforms(glm::mat4 objMat, CameraTransforms cam)
{
	this->objMat = objMat;
	this->cam = cam;
}

void TexturedCube::setColor(glm::vec4 color)
{
	this->color = color;
}

void TexturedCube::draw()
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

	for (int i = 0; i < 6; i++) {
			
		glBindTexture(GL_TEXTURE_2D, texHandler->GetTexID(0));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glUniform1f(
			program->getUniform("myTexture"),
			texHandler->GetTexID(0)
		);
	}
	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	program->unuse();
	glBindVertexArray(0);
}