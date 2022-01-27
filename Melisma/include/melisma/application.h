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
		virtual void Run() final;
		virtual void OnEvent(Event &) final;

		virtual void PushLayerTop(Ref<Layer>) final;
		virtual void PushLayerBottom(Ref<Layer>) final;
		virtual Ref<Layer> PopLayer(Ref<Layer>) final;

		virtual bool IsKeyPressed(KeyCode keyCode) final { return m_Window->IsKeyPressed(keyCode); }
		virtual bool IsMouseButtonPressed(MouseCode mouseCode) final { return m_Window->IsMouseButtonPressed(mouseCode); }

		const Scope<Window> &GetWindow() const { return m_Window; }

	protected:
		bool m_Running;
		Scope<Window> m_Window;
		LayerStack m_LayerStack;

	public:
		static Application *Instance;
	};
}