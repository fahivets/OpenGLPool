#include "ErrorHandler.h"

#include <GL/glew.h>
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR)
	{
	}
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (const GLenum error = glGetError())
	{
		std::cout << "[OpenGL][ERROR] (" << error << ") "
			<< file << ": " << function << ", " << line
			<< std::endl;
		return false;
	}
	return true;
}