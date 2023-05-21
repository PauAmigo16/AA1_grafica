#include "objects/TexturedPlane.h"

TexturedPlane::TexturedPlane(std::string path)
{
    float vertices[]{
        //positions            //Texture coords
         0.5f,  0.5f, 0.f,    1.f, 1.f,    //top right
        -0.5f,  0.5f, 0.f,    0.f, 1.f,    //top left
        -0.5f, -0.5f, 0.f,    0.f, 0.f,    //bottom left
         0.5f, -0.5f, 0.f,    1.f, 0.f    //bottom right
    };
    unsigned int indices[]{
        0, 1, 3,    //top triangle
        1, 2, 3        //bottom
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Bind VAO
    glBindVertexArray(VAO);

    //EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
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

    program = new Program("Square");
    program->compileAndAttachShader("shaders/Texture.vert", GL_VERTEX_SHADER, "texture vs");
    program->compileAndAttachShader("shaders/Texture.frag", GL_FRAGMENT_SHADER, "texture fs");
    program->bindAttribLocation(0, "in_Position");
    program->bindAttribLocation(1, "in_UV");

    program->link();

    const std::vector<std::string> paths(1, path);
    texHandler = new TextureHandler(paths);

    glBindVertexArray(0);
    program->unuse();
}

TexturedPlane::~TexturedPlane()
{
	delete program;
	glDeleteVertexArrays(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VAO);
}

void TexturedPlane::draw()
{
	glBindVertexArray(VAO);
	program->use();

    glUniformMatrix4fv(
        program->getUniform("objMat"),
        1, GL_FALSE, glm::value_ptr(objMat)
    );
    glUniformMatrix4fv(
        program->getUniform("mvpMat"),
        1, GL_FALSE, glm::value_ptr(cam._MVP)
    );

    glBindTexture(GL_TEXTURE_2D, texHandler->GetTexID(0));

	glDrawElements(
		GL_TRIANGLE_STRIP,
		6,
		GL_UNSIGNED_INT,
		0
	);

	program->unuse();
	glBindVertexArray(0);
}

void TexturedPlane::setTransform(glm::mat4 objMat, CameraTransforms cam)
{
	this->objMat = objMat;
	this->cam = cam;
}
