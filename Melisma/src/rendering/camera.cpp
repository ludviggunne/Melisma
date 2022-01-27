#include "melisma/rendering/camera.h"
#include "glm/ext.hpp"

namespace melisma {

	glm::mat4 ScreenCoordCamera::GetProjection() const
	{

		glm::mat4 proj(1.0f);
		proj = glm::scale(proj, glm::vec3(Scale, Scale, 0.0f));
		proj *= glm::ortho(
			static_cast<float>(Viewport.X - Viewport.Width / 2),
			static_cast<float>(Viewport.X + Viewport.Width / 2),
			static_cast<float>(Viewport.Y - Viewport.Height / 2),
			static_cast<float>(Viewport.Y + Viewport.Height / 2),
			-1.0f, 10.0f
		);
		proj = glm::translate(proj, -glm::vec3(Position, 0.0f));

		return proj;
	}

}