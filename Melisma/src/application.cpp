#include "melisma/application.h"

#include <functional>

#define mlDispatchEventApplication(event_type_name)\
	case event_type_name:\
		if (On##event_type_name(static_cast<event_type_name##Event &>(e))) return;\
		break

namespace melisma {

	Application::Application() : m_Running(true) {
		m_Window = Ref<Window>::Create();
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	void Application::OnEvent(Event &e)
	{
		using enum EventType;
		switch (e.GetType()) {
			mlDispatchEventApplication(WindowClose);
			mlDispatchEventApplication(WindowResize);
			mlDispatchEventApplication(WindowFocus);
			mlDispatchEventApplication(WindowLostFocus);
			mlDispatchEventApplication(WindowMoved);

			mlDispatchEventApplication(KeyPressed);
			mlDispatchEventApplication(KeyReleased);
			mlDispatchEventApplication(KeyTyped);

			mlDispatchEventApplication(MouseButtonPressed);
			mlDispatchEventApplication(MouseButtonReleased);
			mlDispatchEventApplication(MouseMoved);
			mlDispatchEventApplication(MouseScrolled);
		}

		m_LayerStack.OnEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent &)
	{
		m_Running = false;
		return true;
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