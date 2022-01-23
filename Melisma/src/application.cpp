#include "melisma/application.h"
#include "melisma/rendering/renderer2D.h"

#include <functional>

// Melisma Todo: Remove this macro
#define mlDispatchEventApplication(event_type_name)\
	case event_type_name:\
		if (On##event_type_name(static_cast<event_type_name##Event &>(e))) return;\
		break

namespace melisma {

	Application::Application() : m_Running(true) {
		m_Window = Ref<Window>::Create();
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		Renderer2D::Init();
	}

	void Application::Run()
	{
		while (m_Running) {
			m_LayerStack.OnUpdate();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event &e)
	{
		if (e.GetType() == EventType::WindowClose)
		{
			Renderer2D::ShutDown();
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

}