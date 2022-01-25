#pragma once

#include "keycodes.h"
#include "mousecodes.h"

#include "glm/glm.hpp"

namespace melisma {

	bool IsKeyPressed(KeyCode keyCode);
	bool IsMouseButtonPressed(MouseCode mouseCode);
	glm::vec2 GetMousePos();

}