#pragma once
#include "event.h"

namespace melisma {

	class melismaAPI WindowCloseEvent : public Event {
	public:
		mlEventType(WindowClose);
	};

	class melismaAPI WindowResizeEvent : public Event {
	public:
		mlEventType(WindowResize);
		WindowResizeEvent(int width, int height) : Width(width), Height(height) {}

		const int Width;
		const int Height;
	};

	class melismaAPI WindowFocusEvent : public Event {
	public:
		mlEventType(WindowFocus);
	};

	class melismaAPI WindowLostFocusEvent : public Event {
	public:
		mlEventType(WindowLostFocus);
	};

	class melismaAPI WindowMovedEvent : public Event {
	public:
		WindowMovedEvent(int xpos, int ypos) : m_xPos(xpos), m_yPos(ypos) {}
		mlEventType(WindowMoved);

		int GetXPos() const { return m_xPos; }
		int GetYPos() const { return m_yPos; }

	private:
		int m_xPos;
		int m_yPos;
	};

}