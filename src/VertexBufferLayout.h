#pragma once

#include <vector>
#include <GL/glew.h>

#include "ErrorHandler.h"

struct VertexBufferLayoutElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return sizeof(float);
			case GL_UNSIGNED_INT:	return sizeof(unsigned int);
			case GL_UNSIGNED_BYTE:	return sizeof(char);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(sizeof(T) == 0, "[ERROR] Type of VertexBufferLayout not implemented.");
	}

	const std::vector<VertexBufferLayoutElement>& GetElements() const { return  m_elements; }
	unsigned int GetStride() const { return m_stride; }

private:
	std::vector<VertexBufferLayoutElement> m_elements;
	unsigned int m_stride;
};

// Template implementation
template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
	m_elements.push_back({ GL_FLOAT, count, false });
	m_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
	m_elements.push_back({ GL_UNSIGNED_INT, count, false });
	m_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
	m_elements.push_back({ GL_UNSIGNED_BYTE, count, true });
	m_stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}