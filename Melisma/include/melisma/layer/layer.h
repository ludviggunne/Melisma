#pragma once
#include "melisma/core.h"
#include "melisma/delta_time.h"

#include "melisma/event/key_event.h"
#include "melisma/event/mouse_event.h"
#include "melisma/event/window_event.h"

// IMPL
namespace melisma {

	// Melisma Todo: Implement OnRender
	class melismaAPI Layer { 
	public:
		Layer() {}
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(const DeltaTime &) {}
		virtual void OnRender() {}

		bool OnEvent(Event &);

		virtual bool OnWindowClose(WindowCloseEvent &)                  { return false; }
		virtual bool OnWindowResize(WindowResizeEvent &)                { return false; }
		virtual bool OnWindowFocus(WindowFocusEvent &)                  { return false; }
		virtual bool OnWindowLostFocus(WindowLostFocusEvent &)          { return false; }
		virtual bool OnWindowMoved(WindowMovedEvent &)                  { return false; }

		virtual bool OnKeyPressed(KeyPressedEvent &)                    { return false; }
		virtual bool OnKeyReleased(KeyReleasedEvent &)                  { return false; }
		virtual bool OnKeyTyped(KeyTypedEvent &)                        { return false; }

		virtual bool OnMouseButtonPressed(MouseButtonPressedEvent &)    { return false; }
		virtual bool OnMouseButtonReleased(MouseButtonReleasedEvent &)  { return false; }
		virtual bool OnMouseMoved(MouseMovedEvent &)                    { return false; }
		virtual bool OnMouseScrolled(MouseScrolledEvent &)              { return false; }

	};

}
