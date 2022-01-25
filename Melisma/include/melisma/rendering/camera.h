#pragma once
#include "melisma/core.h"
#include "glm/glm.hpp"

namespace melisma {

	class melismaAPI Camera {
	public:
		Camera() : m_Projection(glm::mat4(1.0f)) {}
		Camera(const glm::mat4 &projection) : m_Projection(projection) {}

		glm::mat4 GetProjection() const { return m_Projection; }

	private:
		glm::mat4 m_Projection;
	};

}