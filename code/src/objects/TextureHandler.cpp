#include "objects/TextureHandler.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureHandler::TextureHandler(const std::vector<std::string>& paths)
{
	if (paths.empty()) {
		std::cerr << "No hay texturas, perdaun :(";
		exit(2);
	}

	// Generate texture
	textures.resize(paths.size());
	glGenTextures(paths.size(), &textures[0]);

	for (int i = 0; i < paths.size(); i++)
	{				
		// Load image in CPU	
		unsigned char* data = stbi_load(
			paths[i].c_str(),
			&w,
			&h,
			&n,
			0
		);

		if (data)
		{
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(	
				GL_TEXTURE_2D,			// Texture target
				0,						// Mipmaplevel
				GL_RGB,					// Texture using RGB values
				w,
				h,
				0,
				GL_RGB,					// Source format
				GL_UNSIGNED_BYTE,		// Datatype of the source image
				data
			);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		else
		{
			std::cerr << "La textura esta chueca." << std::endl;
		}
		stbi_image_free(data);
	}
}

TextureHandler::~TextureHandler()
{
	glDeleteTextures(textures.size(), &textures[0]);
}

GLuint TextureHandler::GetTexID(int index) const
{
	return textures[index];
}