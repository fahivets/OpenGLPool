#pragma once

#include "LayerBase.h"

namespace Layer
{
	class LayerClearColor : public LayerBase
	{
	public:
		LayerClearColor();
		~LayerClearColor() override;

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_clearColor[4];
	};
}