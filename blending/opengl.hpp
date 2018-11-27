#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

void _check_gl_error(const char *file, int line);

#define checkError() _check_gl_error(__FILE__, __LINE__)
