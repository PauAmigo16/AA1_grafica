#pragma once
#include <vector>
#include <glm/detail/type_vec.hpp>

class ObjLoader
{
public:
	bool  loadOBJ(
		const char*,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec3>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);
};

