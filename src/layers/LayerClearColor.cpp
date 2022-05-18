#include "LayerClearColor.h"

#include <GL/glew.h>

#include "ErrorHandler.h"
#include "imgui/imgui.h"

namespace Layer
{
	LayerClearColor::LayerClearColor() : m_clearColor{ 0.0f, 0.4f, 0.2f, 1.0f }
	{

	}

	LayerClearColor::~LayerClearColor()
	{

	}

	void LayerClearColor::OnUpdate(float deltaTime)
	{
	}

	void LayerClearColor::OnRender()
	{
		GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void LayerClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_clearColor);
	}
}
