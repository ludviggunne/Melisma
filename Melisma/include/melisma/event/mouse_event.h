#pragma once
#include "event.h"

#include "melisma/input/mousecodes.h"
#include "glm/glm.hpp"

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
		MouseMovedEvent(int xpos, int ypos) : m_Position({ xpos, ypos }) {}
		mlEventType(MouseMoved);

		glm::ivec2 GetPos() const { return m_Position; }
	private:
		glm::ivec2 m_Position;
	};

	class melismaAPI MouseScrolledEvent : public Event {
	public:
		mlEventType(MouseScrolled);
	};

}