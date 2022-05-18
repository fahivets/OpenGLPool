#include "VertexArray.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "ErrorHandler.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (size_t id = 0; id < elements.size(); ++id)
	{
		const auto& element = elements[id];
		GLCall(glEnableVertexAttribArray(id));
		GLCall(glVertexAttribPointer(id, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
	}

}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_rendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
