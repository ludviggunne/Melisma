#pragma once

#include "keycodes.h"
#include "mousecodes.h"

namespace melisma {

	bool IsKeyPressed(KeyCode keyCode);
	bool IsMouseButtonPressed(MouseCode mouseCode);

}