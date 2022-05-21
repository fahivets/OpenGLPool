#include "LayerBase.h"

#include "imgui/imgui.h"

namespace Layer
{
	LayerMenu::LayerMenu(LayerBase*& currentLayerPtr) : m_currentLayer(currentLayerPtr)
	{

	}

	LayerMenu::~LayerMenu()
	{
	}

	void LayerMenu::OnImGuiRender()
	{
		for (const auto& layer : m_layers)
		{
			if (ImGui::Button(layer.first.c_str()))
			{
				m_currentLayer = layer.second();
			}
		}

	}
}
