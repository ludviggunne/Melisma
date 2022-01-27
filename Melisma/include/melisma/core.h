#pragma once

#include <iostream>
#include <sstream>

#define melismaAPI

#define ML_MAX_TEXTURES 32

// Melisma Todo: implement debug features / logging (spdlog?)

#ifdef ML_DEBUG
	#define mlAssert(expr)            if(!(expr)) __debugbreak(); // Melisma Warning: __debugbreak is windows specific
	#define mlAssertMsg(expr, errmsg) if(!(expr)) { mlLog("[Melisma assert]: " << errmsg); __debugbreak(); }
	#define mlVerify(expr)            if(!(expr)) __debugbreak();
	#define mlVerifyMsg(expr, errmsg) if(!(expr)) { mlLog("[Melisma verify]: " << errmsg); __debugbreak(); }
	#define mlLog(msg)                std::cout << "[Melisma log]: " << msg << '\n';
	
	#define mlDeclareDebugName        public: std::string _debugName
	#define mlDefineDebugName(stream) { std::stringstream s; s << stream; _debugName = s.str(); }
#else
	#define mlAssert(expr)
	#define mlAssertMsg(expr, errmsg)
	#define mlVerify(expr) expr
	#define mlVerifyMsg(expr, errmsg) expr
	#define mlLog(msg)
	
	#define mlDeclareDebugName	
	#define mlDefineDebugName(stream)
#endif