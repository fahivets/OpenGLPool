#pragma once

#include "Renderer.h"

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(const unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

private:
	unsigned int m_rendererID;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width;
	int m_height;
	int m_BPP;

};