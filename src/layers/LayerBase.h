#pragma once

namespace Layer
{
	class LayerBase
	{
	public:
		LayerBase() {}
		virtual ~LayerBase() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};
}