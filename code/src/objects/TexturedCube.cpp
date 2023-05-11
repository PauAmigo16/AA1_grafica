#include "objects/TexturedCube.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TexturedCube::TexturedCube() : Cube()
{
	float vertices[]{
		//positions                            //Texture coords
		 halfSide,  halfSide, halfSide,     1.f, 1.f,    //front top right
		-halfSide,  halfSide, halfSide,     0.f, 1.f,    //front top left
		-halfSide, -halfSide, halfSide,     0.f, 0.f,    //front bottom left
		 halfSide, -halfSide, halfSide,     1.f, 0.f,    //front bottom right

		 halfSide,  halfSide, -halfSide,    1.f, 1.f,    //right top right
		 halfSide,  halfSide,  halfSide,    0.f, 1.f,    //right top left
		 halfSide, -halfSide,  halfSide,    0.f, 0.f,    //right bottom left
		 halfSide, -halfSide, -halfSide,    1.f, 0.f,    //right bottom right 

		 halfSide,  halfSide, -halfSide,    1.f, 1.f,    //top top right
		-halfSide,  halfSide, -halfSide,    0.f, 1.f,    //top top left
		-halfSide,  halfSide,  halfSide,    0.f, 0.f,    //top bottom left
		 halfSide,  halfSide,  halfSide,    1.f, 0.f,    //top bottom right

		-halfSide,  halfSide,  halfSide,    1.f, 1.f,    //left top right
		-halfSide,  halfSide, -halfSide,    0.f, 1.f,    //left top left
		-halfSide, -halfSide, -halfSide,    0.f, 0.f,    //left bottom left
		-halfSide, -halfSide,  halfSide,    1.f, 0.f,    //left bottom right

		 halfSide, -halfSide,  halfSide,    1.f, 1.f,    //bottom top right
		-halfSide, -halfSide,  halfSide,    0.f, 1.f,    //bottom top left
		-halfSide, -halfSide, -halfSide,    0.f, 0.f,    //bottom bottom left
		 halfSide, -halfSide, -halfSide,    1.f, 0.f,    //bottom bottom right

		-halfSide,  halfSide, -halfSide,    1.f, 1.f,    //back top right
		 halfSide,  halfSide, -halfSide,    0.f, 1.f,    //back top left
		 halfSide, -halfSide, -halfSide,    0.f, 0.f,    //back bottom left
		-halfSide, -halfSide, -halfSide,    1.f, 0.f,    //back bottom right
	};

	unsigned int indices[]{
		0, 1, 3,        //front top triangle
		1, 2, 3,        //front bottom triangle

		4, 5, 7,        //right top triangle
		5, 6, 7,        //right bottom triangle

		8, 9, 11,       //top top trinagle
		9, 10, 11,      //top bottom triangle

		12, 13, 15,     //left top triangle
		13, 14, 15,     //left bottom triangle

		16, 17, 19,     //bottom top triangle
		17, 18, 19,     //bottom bottom triangle

		20, 21, 23,     //back top triangle
		21, 22, 23,     //back bottom triangle
	};

	//Bind VAO
	glBindVertexArray(VAO);

	//EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//define the position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//define texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(float),            //stride ->  v, x, y, z, u  (float)
		(void*)(3 * sizeof(float))    //offset
	);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	program = new Program("TexturedCube");
	program->compileAndAttachShader(std::string("shaders/").append("QB").append(".vert").c_str(), GL_VERTEX_SHADER, std::string("TexturedCube").append(" VS").c_str());
	program->compileAndAttachShader(std::string("shaders/").append("QB").append(".geom").c_str(), GL_GEOMETRY_SHADER, std::string("TexturedCube").append(" GS").c_str());
	program->compileAndAttachShader(std::string("shaders/").append("QB").append(".frag").c_str(), GL_FRAGMENT_SHADER, std::string("TexturedCube").append(" FS").c_str());
	program->bindAttribLocation(0, "in_Position");
	program->bindAttribLocation(1, "in_UVs");
	program->link();

	for (int i = 0; i < 6; i++) {
		LoadImage(i);
	}
}

TexturedCube::~TexturedCube()
{
	delete program;
	glDeleteBuffers(3, VBO);
	glDeleteVertexArrays(1, &VAO);
}

void TexturedCube::LoadImage(int i)
{
	
	glGenTextures(1, &texture[i]);

	int height, width, nrChannels;

	unsigned char* data = stbi_load(
		"res/wall_texture.jpg",
		&width, &height,
		&nrChannels, 0
	);
	glBindTexture(GL_TEXTURE_2D, texture[i]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

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
		glBindTexture(GL_TEXTURE_2D, texture[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glUniform1f(
			program->getUniform("text"),
			texture[i]
		);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(unsigned int)));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	program->unuse();
	glBindVertexArray(0);
}
