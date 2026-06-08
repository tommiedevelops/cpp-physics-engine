#pragma once

#include "Window.h"
#include "Scene.h"
#include "AssetManager.h"
#include "GameTime.h"
#include "Layer.h"

namespace PhysicsEngine
{
	using Layers = std::vector<std::shared_ptr<Layer>>;

	class App
	{
	public:
		static void Init(WindowProperties& windowProperties);
		static App* GetInstance();

		void Run();
		void OnEvent(Event& e);

		Window* GetWindow()
		{
			return &m_Window;
		}

		// no copies and moves
		App(const App&) = delete;
		App& operator=(const App&) = delete;

		AssetManager* GetAssetsRef()
		{
			return &m_Assets;
		}

		void PushLayer(std::shared_ptr<Layer> layer);

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
		
		void MainLoop();
	private:

		App(WindowProperties& windowProperties);
		Layers  			 m_Layers;
		Window               m_Window;
		WindowProperties&    m_WindowProperties;
		AssetManager         m_Assets;
		GameTime             m_GameTime;
	};
}
