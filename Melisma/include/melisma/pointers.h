#pragma once
#include "core.h"
//#include "core.h"

#define TYPE(type) #type

#if 0
#define mlLogRef(msg) mlLog("Ref<T>: " << msg)
#else
#define mlLogRef(msg)
#endif

namespace melisma {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}