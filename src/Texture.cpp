#include "Texture.h"

#include <iostream>
#include <GL/glew.h>

#include "ErrorHandler.h"
#include "stb_image/stb_image.h"


Texture::Texture(const std::string& filePath)
	: m_rendererID(0), m_filePath(filePath), m_localBuffer(nullptr), m_width(0), m_height(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_BPP, 4);

	if (!m_localBuffer)
	{
		std::cout << "[STD_IMAGE][ERROR] " << stbi_failure_reason() << ": " << filePath << "\n";
	}

	GLCall(glGenTextures(1, &m_rendererID));

	Bind();

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

	Unbind();

	if(m_localBuffer)
	{
		stbi_image_free(m_localBuffer);
	}
}

Texture::~Texture()
{
	/*
	if (m_localBuffer)
	{
		stbi_image_free(m_localBuffer);
	}
	*/
	GLCall(glDeleteTextures(1, &m_rendererID));
}

void Texture::Bind(const unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
