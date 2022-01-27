#pragma once
#include "melisma/core.h"
#include "glm/glm.hpp"

namespace melisma {

	class melismaAPI Camera {
	public:
		virtual glm::mat4 GetProjection() const = 0;
	};

}