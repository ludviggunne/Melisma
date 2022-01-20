#pragma once

#include "core.h"

#include "pointers.h"

#include "window.h"
#include "layer/layer_stack.h"

#include "event/key_event.h"
#include "event/mouse_event.h"
#include "event/window_event.h"

namespace melisma {

	class melismaAPI Application {
	public:
		Application();
		virtual ~Application() {}

		Application(const Application &) = delete;
		Application operator =(const Application &) = delete;

		virtual void Run() = 0;
		virtual void OnEvent(Event &) final;

		virtual bool OnWindowClose(WindowCloseEvent &) final;
		virtual bool OnWindowResize(WindowResizeEvent &)				{ return false; }
		virtual bool OnWindowFocus(WindowFocusEvent&)					{ return false;}
		virtual bool OnWindowLostFocus(WindowLostFocusEvent&)			{ return false;}
		virtual bool OnWindowMoved(WindowMovedEvent&)					{ return false;}

		virtual bool OnKeyPressed(KeyPressedEvent&)						{ return false;}
		virtual bool OnKeyReleased(KeyReleasedEvent&)					{ return false;}
		virtual bool OnKeyTyped(KeyTypedEvent&)							{ return false;}

		virtual bool OnMouseButtonPressed(MouseButtonPressedEvent&)		{ return false;}
		virtual bool OnMouseButtonReleased(MouseButtonReleasedEvent&)	{ return false;}
		virtual bool OnMouseMoved(MouseMovedEvent&)						{ return false;}
		virtual bool OnMouseScrolled(MouseScrolledEvent &)				{ return false;}

		virtual void PushLayerTop(Ref<Layer>) final;
		virtual void PushLayerBottom(Ref<Layer>) final;
		virtual Ref<Layer> PopLayer(Ref<Layer>) final;

		virtual bool IsKeyPressed(KeyCode keyCode) final { return m_Window->IsKeyPressed(keyCode); }

	public:

	protected:
		bool m_Running;
		Window *m_Window;
		LayerStack m_LayerStack;
	};

	//Application *CreateApplication();
}