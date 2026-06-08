#pragma once

#include "Layer.h"
#include "Scene.h"

namespace PhysicsEngine
{
	class SceneLayer : public Layer
	{
	private:
		using SceneFactoryMethod = std::function<std::unique_ptr<Scene>()>;
		using FactoryMethodMap   = std::unordered_map<std::string, SceneFactoryMethod>;

		FactoryMethodMap        m_Factories;
		std::unique_ptr<Scene>  m_ActiveScene{ nullptr };
		float                   m_CurrentAspect{ 16.0f / 9.0f }; // Why am I storing the aspect ratio here?
		AssetManager*           m_AssetsRef; // Why do I need to store a reference to the asset manager

	public:
		// Virtual functions
		void OnAttach()		    override;
		void OnDetach()			override;
		void OnRender()			override;
		void OnUpdate(float dt) override;
		void OnEvent(Event& e)  override;

		void RegisterScene(const std::string& name, SceneFactoryMethod factory) { m_Factories.emplace(name, factory); }
		void DeRegisterScene(const std::string& name) { m_Factories.erase(name); }
		void SetAssetsRef(AssetManager* assetManager) { m_AssetsRef = assetManager; } // Why do I have an assets ref here?
		void SetActiveScene(const std::string& name);
		FactoryMethodMap& GetFactories() { return m_Factories; } // Why do I have a getter for factories?
	};
}