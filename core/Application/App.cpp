#include "app.h"

#include "SceneLayer.h"
#include "GlobalOverlayLayer.h"
#include "Event.h"
#include "Input.h"

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif


#include <iostream> // for DEBUG

namespace PhysicsEngine
{
	// Singleton for App
	static App* s_Instance = nullptr;

	static void EmscriptenMainLoop()
	{
		s_Instance->MainLoop();
	}

	App* App::GetInstance()
	{
		return s_Instance;
	}

	App::App(WindowProperties& windowProperties)
		: m_Window{windowProperties}
		, m_Assets{}
		, m_GameTime{}
		, m_WindowProperties{windowProperties}
	{
		m_Window.SetEventCallback(
			[this](Event& e) { OnEvent(e); }
		);

		Input::Init(m_Window.GetNativeWindow());
	}

	void App::Init(WindowProperties& windowProperties)
	{
		s_Instance = new App(windowProperties);
	}

	void App::PushLayer(std::shared_ptr<Layer> layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

	void App::OnEvent(Event& e)
	{
		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			if (e.IsHandled()) break;
			(*it)->OnEvent(e);
		}
	}

	void App::MainLoop()
	{
			m_GameTime.Update();
			m_Window.PollEvents();

			for (const auto& layer : m_Layers)
			{
				layer->OnUpdate(m_GameTime.GetDeltaTime());
				layer->OnRender();
			}

			m_Window.SwapBuffers();
	}

	void App::Run()
	{
		s_Instance = this;
		
#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop(EmscriptenMainLoop, 0, 1);
		emscripten_hide_mouse();
#else
		while (!m_Window.ShouldClose())
		{
			MainLoop();
		}
#endif
	};
}
