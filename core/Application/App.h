#pragma once

#include "Window.h"
#include "Scene.h"
#include "AssetManager.h"
#include "GameTime.h"
#include "Layer.h"

#include <vector>
#include <memory>

namespace PhysicsEngine
{
	using Layers = std::vector<std::shared_ptr<Layer>>;

	class App
	{
	public:
		static void Init(WindowProperties& windowProperties);
		static App* GetInstance();

		App(const App&)             = delete;
		App& operator=(const App&)  = delete;

		void   Run();
		void   MainLoop();
		void   OnEvent(Event& e);
		void   PushLayer(std::shared_ptr<Layer> layer);

		Window*       GetWindow()    { return &m_Window; }
		AssetManager* GetAssetsRef() { return &m_Assets; }

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
		
	private:
		App(WindowProperties& windowProperties);

		Layers  			 m_Layers;
		Window               m_Window;
		WindowProperties&    m_WindowProperties;
		AssetManager         m_Assets;
		GameTime             m_GameTime;

	};
}
