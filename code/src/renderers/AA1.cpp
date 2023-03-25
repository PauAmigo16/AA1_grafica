#include "renderers/AA1.h"

AA1::AA1(int width, int height) : Renderer(width, height)
{
	bool res = ObjLoader::LoadOBJ("../src/objects/QB.obj", vertices, uvs, normals);
}

AA1::~AA1()
{
}

void AA1::render()
{
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

}
