#include "Texture.h"

#include <stb/stb_image.h>

#include <stdexcept>



Texture::Texture(const std::filesystem::path& image)
{
	int width = 0;
	int height = 0;
	int channels = 0;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image.string().c_str(), &width, &height, &channels, 0);

	if (!bytes)
	{
		throw std::runtime_error("Texture::Texture(): failed to load texture: " + image.string() + " (" + stbi_failure_reason() + ")");
	}

	GLenum format = GL_RGB;
	GLint internalFormat = GL_RGB8;

	if (channels == 1)
	{
		format = GL_RED;
		internalFormat = GL_R8;
	}
	else if (channels == 3)
	{
		format = GL_RGB;
		internalFormat = GL_RGB8;
	}
	else if (channels == 4)
	{
		format = GL_RGBA;
		internalFormat = GL_RGBA8;
	}
	else
	{
		stbi_image_free(bytes);
		throw std::runtime_error("Texture::Texture(): unsupported channel count");
	}

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    Delete();
}

void Texture::Bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    if (ID)
    {
        glDeleteTextures(1, &ID);
        ID = 0;
    }
}
