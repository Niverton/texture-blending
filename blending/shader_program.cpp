#include "opengl.hpp"
#include "rtexception.hpp"
#include "shader_program.hpp"
#include <vector>

ShaderProgram::~ShaderProgram() { delete_program(); }

std::string ShaderProgram::get_log() const {
  int log_size = 0;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_size);

  if (log_size <= 1) {
    return "OK";
  }

  std::vector<char> message(log_size);

  glGetProgramInfoLog(id, log_size, nullptr, message.data());

  return std::string(message.data(), log_size - 1);
}

void ShaderProgram::enable() { glUseProgram(id); }

void ShaderProgram::disable() { glUseProgram(0); }

bool ShaderProgram::create(std::vector<const Shader *> shaders) {
  if (is_valid()) {
    throw RTException("Trying to create an already valid program.\n");
  }
  id = glCreateProgram();

  for (auto s : shaders) {
    glAttachShader(id, s->get_id());
  }

  glLinkProgram(id);

  for (auto s : shaders) {
    glDetachShader(id, s->get_id());
  }

  // Error status
  int is_linked = 0;
  glGetProgramiv(id, GL_LINK_STATUS, &is_linked);

  is_ready = is_linked == GL_TRUE;
  return is_ready;
}

void ShaderProgram::delete_program() {
  if (id != 0) {
    glDeleteProgram(id);
  }
}

int ShaderProgram::get_attribute_location(const char *attribute) const {
  return glGetAttribLocation(id, attribute);
}

int ShaderProgram::get_uniform_location(const char *uniform) const {
  return glGetUniformLocation(id, uniform);
}
