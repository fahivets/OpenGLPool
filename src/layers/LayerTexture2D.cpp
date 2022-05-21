#include "LayerTexture2D.h"

#include <GL/glew.h>

#include "ErrorHandler.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"

namespace Layer
{
	LayerTexture2D::LayerTexture2D()
	{
		float position[] = {
            100.0f,   100.0f, 0.0f, 0.0f,
        	200.0f,   100.0f, 1.0f, 0.0f,
        	200.0f,   200.0f, 1.0f, 1.0f,
            100.0f,   200.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_vertexArray = std::make_unique<VertexArray>();
        m_vertexBuffer = std::make_unique<VertexBuffer>(position, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_vertexArray->AddBuffer(*m_vertexBuffer, layout);
        m_indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_shader->Bind();
        //Texture texture("res/textures/TEMP.png");
        m_texture = std::make_unique<Texture>("res/textures/PIKA.png");
        m_shader->SetUniform1i("u_Texture", 0);

        // TEST MATRIX
        // TODO: fix object position
        m_proj = glm::ortho<float>(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        m_view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        m_translation = glm::vec3(200.f, 200.f, 0.f);
	}

	LayerTexture2D::~LayerTexture2D()
	{
        GLCall(glDisable(GL_BLEND));
	}

	void LayerTexture2D::OnUpdate(float deltaTime)
	{
	}

	void LayerTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
        Renderer renderer;

        m_texture->Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation);
        glm::mat4 mvp = m_proj * m_view * model;

        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_vertexArray, *m_indexBuffer, *m_shader);
	}

	void LayerTexture2D::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation", glm::value_ptr(m_translation), 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
