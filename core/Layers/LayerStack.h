#pragma once

#include "Layer.h"
#include <vector>
#include <memory>
#include <stdexcept>

namespace PhysicsEngine
{
	using Layers = std::vector<std::shared_ptr<Layer>>;

	class LayerStack
	{
	private:
		Layers  m_Layers;
		Window* m_Window{ nullptr };
	public:
		LayerStack() = default;
		~LayerStack() = default;

		void PushLayer(std::shared_ptr<Layer> layer);

		void SetWindowRef(Window* window)
		{
			if (!window) throw std::logic_error("Window is null");
			m_Window = window;
		}

		template <typename T>
		T* GetLayer()
		{
			static_assert(std::derived_from<T, Layer>, "T must derive from Layer");

			for (const auto& layer : m_Layers)
			{
				if (T* result = dynamic_cast<T*>(layer.get()))
					return result;
			}

			return nullptr;
		}

		Layers& GetLayers() { return m_Layers; }

	};
}