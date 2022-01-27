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
		virtual ~Application() { }

		Application(const Application &) = delete;
		Application operator =(const Application &) = delete;

		virtual void Init() = 0;
		void Run();
		void OnEvent(Event &);

		void PushLayerTop(Ref<Layer>);
		void PushLayerBottom(Ref<Layer>);
		Ref<Layer> PopLayer(Ref<Layer>);

		bool IsKeyPressed(KeyCode keyCode) { return m_Window->IsKeyPressed(keyCode); }
		bool IsMouseButtonPressed(MouseCode mouseCode) { return m_Window->IsMouseButtonPressed(mouseCode); }

		const Scope<Window> &GetWindow() const { return m_Window; }

	protected:
		bool m_Running;
		Scope<Window> m_Window;
		LayerStack m_LayerStack;

	public:
		static Application *Instance;
	};
}