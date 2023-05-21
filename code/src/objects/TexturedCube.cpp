#include "objects/TexturedCube.h"

TexturedCube::TexturedCube() {
	SingleTexture();
}

TexturedCube::~TexturedCube() {
	for (int i = 0; i < 6; i++) {
		delete cube[i];
	}
}

void TexturedCube::setTransforms(glm::mat4 _objMat, CameraTransforms cam) {
	this->objMat = _objMat;
	this->cam = cam;
	// Front face
	cube[0]->setTransform(glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, 0.5f)), cam);
	// Back face
	cube[1]->setTransform(glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -0.5f)), cam);
	// Up face
	cube[2]->setTransform(glm::translate(glm::mat4(), glm::vec3(0.f, 0.5f, 0.f)) * glm::rotate(glm::mat4(), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)), cam);
	// Down face
	cube[3]->setTransform(glm::translate(glm::mat4(), glm::vec3(0.f, -0.5f, 0.f)) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f)), cam);
	// Left face
	cube[4]->setTransform(glm::translate(glm::mat4(), glm::vec3(0.5f, 0.f, 0.f)) * glm::rotate(glm::mat4(), glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f)), cam);
	// Right face
	cube[5]->setTransform(glm::translate(glm::mat4(), glm::vec3(-0.5f, 0.f, 0.f)) * glm::rotate(glm::mat4(), glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f)), cam);

}

void TexturedCube::Draw() {
	for (int i = 0; i < 6; i++) {
		cube[i]->draw();
	}
}

void TexturedCube::DrawGUI() {
	if (ImGui::Button("SingleTexture")) {
		SingleTexture();
	}

	if (ImGui::Button("MultipleTexture")) {
		MultipleTexture();
	}
}

void TexturedCube::SingleTexture() {
	// One texture all cube
	cube[0] = new TexturedPlane("res/wall_texture.jpg");
	cube[1] = new TexturedPlane("res/wall_texture.jpg");
	cube[2] = new TexturedPlane("res/wall_texture.jpg");
	cube[3] = new TexturedPlane("res/wall_texture.jpg");
	cube[4] = new TexturedPlane("res/wall_texture.jpg");
	cube[5] = new TexturedPlane("res/wall_texture.jpg");
}

void TexturedCube::MultipleTexture() {
	// One texture all cube
	cube[0] = new TexturedPlane("res/pizza1.jpg");
	cube[1] = new TexturedPlane("res/pizza2.jpg");
	cube[2] = new TexturedPlane("res/pizza3.jpg");
	cube[3] = new TexturedPlane("res/pizza4.jpg");
	cube[4] = new TexturedPlane("res/pizza5.jpg");
	cube[5] = new TexturedPlane("res/pizza6.jpg");
}