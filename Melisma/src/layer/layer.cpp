#include "melisma/layer/layer.h"

#define mlDispatchEventLayer(event_type_name)\
	case EventType::##event_type_name: return On##event_type_name(static_cast<event_type_name##Event &>(e))

namespace melisma {

	bool Layer::OnEvent(Event &e) {

		switch (e.GetType()) {
			mlDispatchEventLayer(WindowClose);
			mlDispatchEventLayer(WindowResize);
			mlDispatchEventLayer(WindowFocus);
			mlDispatchEventLayer(WindowLostFocus);
			mlDispatchEventLayer(WindowMoved);

			mlDispatchEventLayer(KeyPressed);
			mlDispatchEventLayer(KeyReleased);
			mlDispatchEventLayer(KeyTyped);

			mlDispatchEventLayer(MouseButtonPressed);
			mlDispatchEventLayer(MouseButtonReleased);
			mlDispatchEventLayer(MouseMoved);
			mlDispatchEventLayer(MouseScrolled);
		}

		return false;
	}

}