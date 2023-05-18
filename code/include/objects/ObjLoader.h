#pragma once
#include <vector>
#include <string>
#include <glm/detail/type_vec.hpp>
#include <glm/glm.hpp>

class ObjLoader
{
public:
	static bool LoadOBJ(
		const char* path,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2 >& out_uvs,
		std::vector<glm::vec3>& out_normals
	);
};

