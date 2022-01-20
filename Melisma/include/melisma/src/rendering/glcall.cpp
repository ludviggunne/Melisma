#include "glcall.h"

#include "glad/glad.h"

#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (0x" << std::hex << error << std::dec << "): " << function <<
			" " << file << ": " << line << std::endl; // Melisma Todo: replace with core log
		return false;
	}
	return true;
}