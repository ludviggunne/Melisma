#pragma once

#include "core.h"

#include <functional>

#include "event/event.h"
#include "delta_time.h"
#include "input/keycodes.h"
#include "input/mousecodes.h"
#include "glm/glm.hpp"

namespace melisma {

	class melismaAPI Window {

		using EventCallbackFn = std::function<void(Event &)>;
		
	public:
		Window(int width = 800, int height = 600, const char *title = "Melisma Application");
		~Window();

		void SetEventCallback(const EventCallbackFn &callback) { m_UserData.EventCallback = callback; }

		void OnUpdate(const DeltaTime &deltaTime = DeltaTime{}) const;

		void SetResizable(bool resizable) const;
		void SetSize(int width, int height);
		void Maximize();

		void GetFrameBufferSize(int &width, int &height) const;
		int GetWidth() const;
		int GetHeight() const;

		bool IsKeyPressed(KeyCode keyCode) const;
		bool IsMouseButtonPressed(MouseCode mouseCode) const;
		glm::vec2 GetMousePos() const;

	private:
		void *m_NativeHandle;

		struct UserData {
			int Width;
			int Height;
			
			EventCallbackFn EventCallback;
		} m_UserData;
	};
}