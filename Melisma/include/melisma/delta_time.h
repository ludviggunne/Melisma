#pragma once
#include "core.h"

namespace melisma {

	class melismaAPI DeltaTime {
	public:
		DeltaTime() : m_Time(1.0) {}

		template<typename T>
		inline double operator *(const T &value) { return m_Time * value; }

	private:
		double m_Time;
	};

}