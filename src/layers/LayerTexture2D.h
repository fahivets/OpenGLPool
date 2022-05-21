#pragma once

#include "LayerBase.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"

namespace Layer
{
	class LayerTexture2D : public LayerBase
	{
	public:
		LayerTexture2D();
		~LayerTexture2D() override;

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_vertexArray;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_texture;

		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::vec3 m_translation;
	};
}