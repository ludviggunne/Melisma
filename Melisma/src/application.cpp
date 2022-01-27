#include "melisma/application.h"
#include "melisma/rendering/renderer2D.h"

#include <functional>
#include <chrono>

// Melisma Todo: Remove this macro
#define mlDispatchEventApplication(event_type_name)\
	case event_type_name:\
		if (On##event_type_name(static_cast<event_type_name##Event &>(e))) return;\
		break

namespace melisma {

	Application::Application() : m_Running(true) {
		m_Window = CreateScope<Window>();
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	void Application::Run()
	{
		using namespace std::chrono;
		DeltaTime delta_time = 1.0f / 30;
		
		while (m_Running) {
			// Begin frame timing
			auto t_begin = high_resolution_clock::now();

			// Update components and render
			m_LayerStack.OnUpdate(delta_time);
			m_Window->OnUpdate(delta_time);

			m_LayerStack.OnRender();

			// Calculate delta time
			auto t_end = high_resolution_clock::now();
			delta_time = duration<float>(t_end - t_begin).count();
		}
	}

	void Application::OnEvent(Event &e)
	{
		if (e.GetType() == EventType::WindowClose)
		{
			m_Running = false;

			return;
		}

		m_LayerStack.OnEvent(e);
	}

	void Application::PushLayerTop(Ref<Layer> layer)
	{
		m_LayerStack.PushLayerTop(layer);
	}

	void Application::PushLayerBottom(Ref<Layer> layer)
	{
		m_LayerStack.PushLayerBottom(layer);
	}

	Ref<Layer> Application::PopLayer(Ref<Layer> layer)
	{
		return m_LayerStack.PopLayer(layer);
	}

	Application *Application::Instance = nullptr;
}