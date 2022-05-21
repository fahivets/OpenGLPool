#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

//TODO: refactoring later on

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
	//TODO: transfer to a separate class
	class LayerMenu : public LayerBase
	{
	public:
		LayerMenu(LayerBase*& currentLayerPtr);
		~LayerMenu() override;

		//void OnUpdate(float deltaTime) override;
		//void OnRender() override;
		void OnImGuiRender() override;

		template<typename T>
		void RegisterLayer(const std::string& name)
		{
			//TODO: temp debug
			std::cout << "[DEBUG] Registering layer: " << name << std::endl;

			m_layers.push_back(std::make_pair(name, []() { return new T(); }));
		}

	private:
		LayerBase*& m_currentLayer;
		std::vector<std::pair<std::string, std::function<LayerBase* ()>>> m_layers; //TODO: use smart ptr?

	};
}
