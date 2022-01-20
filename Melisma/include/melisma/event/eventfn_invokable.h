#pragma once

#include "core.h"
#include "event.h"

namespace melisma {

	class melismaAPI EventFnInvokable {
	public:
		virtual void OnEvent(Event*) = 0;
	};
}