#pragma once
#include "event.h"

#include "melisma/input/mousecodes.h"

namespace melisma{

	class melismaAPI MouseButtonEvent : public Event {
	public:
		MouseButtonEvent(MouseCode mouseCode) : m_MouseCode(mouseCode) {}
		virtual MouseCode GetMouseCode() const { return m_MouseCode; }

	protected:
		MouseCode m_MouseCode;
	};

	class melismaAPI MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(MouseCode mouseCode) : MouseButtonEvent(mouseCode) {}
		mlEventType(MouseButtonPressed);
	};

	class melismaAPI MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(MouseCode mouseCode) : MouseButtonEvent(mouseCode) {}
		mlEventType(MouseButtonReleased);
	};
	
	class melismaAPI MouseMovedEvent : public Event {
	public:
		mlEventType(MouseMoved);
	};

	class melismaAPI MouseScrolledEvent : public Event {
	public:
		mlEventType(MouseScrolled);
	};

}