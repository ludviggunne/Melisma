#pragma once
#include "event.h"
#include "../input/keycodes.h"

namespace melisma {

	class melismaAPI KeyEvent : public Event {
	public:
		KeyEvent(KeyCode keyCode) : m_KeyCode(keyCode) {}
		KeyCode GetKeyCode() const { return m_KeyCode; }
		
	protected:
		const KeyCode m_KeyCode;
	};




	class melismaAPI KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(KeyCode keyCode, bool repeated) : KeyEvent(keyCode), m_Repeated(repeated) {}
		bool IsRepeated() const { return m_Repeated; }

		mlEventType(KeyPressed);

	private:
		bool m_Repeated;
	};

	class melismaAPI KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(KeyCode keyCode) : KeyEvent(keyCode) {}
		mlEventType(KeyReleased);
	};

	class melismaAPI KeyTypedEvent : public KeyEvent {
	public:
		mlEventType(KeyTyped);
	};

}