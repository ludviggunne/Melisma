#pragma once

#include "melisma/core.h"

// TODO: Implement event cathegory

namespace melisma {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	class melismaAPI Event {
	public:
		Event() : Handled(false) {}

		virtual EventType GetType() const { return EventType::None; }

	public:
		bool Handled;

	};

	template<class E>
	concept EventClass = std::is_base_of<Event, E>::value;

	#define mlEventType(type) virtual EventType GetType() const override { return EventType::##type; }

	// QUESTION: Use EventStatus enum for OnEvent return value?
	enum class EventStatus : bool {
		UnHandled = 0,
		Handled   = 1
	};

}

