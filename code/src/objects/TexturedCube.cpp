#include "objects/TexturedCube.h"

TexturedCube::TexturedCube()
{
	for (int i = 0; i < 6; i++) {
		cube[i] = new TexturedPlane();
	}
}

TexturedCube::~TexturedCube()
{
	for (int i = 0; i < 6; i++) {
		delete cube[i];
	}
}

void TexturedCube::setTransforms(glm::mat4 _objMat, CameraTransforms cam)
{
	this->objMat = _objMat;
	this->cam = cam;
	cube[0]->setTransform(glm::translate(objMat, glm::vec3(0.f, 0.f, 0.f)), cam);
	this->objMat = _objMat;
	cube[1]->setTransform(glm::translate(objMat, glm::vec3(0.f, 0.f, -0.f)), cam);
	this->objMat = _objMat;
	cube[2]->setTransform(glm::rotate(objMat, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)) * glm::translate(objMat, glm::vec3(0.f, 0.f, 0.f)), cam);
	this->objMat = _objMat;
	cube[3]->setTransform(glm::rotate(objMat, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f)) * glm::translate(objMat, glm::vec3(0.f, -0.f, 0.f)), cam);
	this->objMat = _objMat;
	cube[4]->setTransform(glm::rotate(objMat, glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f)) * glm::translate(objMat, glm::vec3(0.f, 0.f, 0.f)), cam);
	this->objMat = _objMat;
	cube[5]->setTransform(glm::rotate(objMat, glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f)) * glm::translate(objMat, glm::vec3(-0.f, 0.f, 0.f)), cam);
	this->objMat = _objMat;

}

void TexturedCube::draw()
{
	for (int i = 0; i < 6; i++) {
		cube[i]->draw();
	}
}