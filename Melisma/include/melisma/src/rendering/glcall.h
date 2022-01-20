#pragma once
#include "core.h"

void GLClearError();
bool GLLogCall(const char *, const char *, int);

#ifdef ML_DEBUG
#define GLcall(expr) GLClearError(); expr; mlAssert(GLLogCall(#expr, __FILE__, __LINE__))
#else
#define GLcall(expr) expr
#endif