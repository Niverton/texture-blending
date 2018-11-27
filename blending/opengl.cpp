#include "opengl.hpp"
#include <iostream>

inline void perror(const char *e, const char *f, const char *l) {
  std::cerr << "OpenGL Error: " << e << " at " << f << ":" << l << "\n";
}

void _check_gl_error(const char *file, int line) {
  using std::cerr;
  GLenum error = glGetError();

  /* TODO nécessaire ?
  switch (error) {
  case GL_NO_ERROR:
    // Nothing to do
    break;
  case GL_INVALID_ENUM:
    perror("GL_INVALID_ENUM", file, line);
    break;
  case GL_INVALID_VALUE:
    perror("GL_INVALID_VALUE", file, line);
    break;
  case GL_INVALID_OPERATION:
    perror("GL_INVALID_OPERATION", file, line);
    break;
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    perror("GL_INVALID_FRAMEBUFFER_OPERATION", file, line);
    break;
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    perror("GL_INVALID_FRAMEBUFFER_OPERATION", file, line);
    break;
  default:
    cerr << "Unknown error " << error << " in file " << file << ":" << line
         << "\n";
    break;
  }
  */

  if (error != GL_NO_ERROR) {
    std::cerr << "error: " << error << " in " << file << " at l." << line
              << "\n";
  }
}
