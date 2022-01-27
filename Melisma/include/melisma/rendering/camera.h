#pragma once
#include "melisma/core.h"
#include "glm/glm.hpp"
#include "viewport.h"

namespace melisma {

	class melismaAPI Camera {
	public:
		virtual glm::mat4 GetProjection() const = 0;
	};

	class melismaAPI ScreenCoordCamera : public Camera {
	public:
		ScreenCoordCamera(Viewport viewport, glm::vec2 position, float scale)
			: Viewport(viewport), Position(position), Scale(scale)
		{
		}

		virtual glm::mat4 GetProjection() const override;

	public:
		Viewport Viewport;
		glm::vec2 Position;
		float Scale;
	};
}

