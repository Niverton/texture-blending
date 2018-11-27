#include "opengl.hpp"
#include "rtexception.hpp"
#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(ShaderType type) {
  switch (type) {
  case ShaderType::Vertex:
    id = glCreateShader(GL_VERTEX_SHADER);
    break;
  case ShaderType::Fragment:
    id = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  }
}

Shader::~Shader() { delete_shader(); }

bool Shader::create_from_file(const std::string &file_name) {
  if (is_valid()) {
    throw RTException("Trying to recreate already compiled shader.\n");
  }
  std::ifstream f{file_name};
  std::stringstream content;
  content << f.rdbuf();

  return create_from_string(content.str());
}

bool Shader::create_from_string(const std::string &content) {
  if (is_valid()) {
    throw RTException("Trying to recreate already compiled shader.\n");
  }

  const char *data = content.c_str();
  glShaderSource(id, 1, &data, nullptr);

  glCompileShader(id);

  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  is_ready = success == GL_TRUE;
  return is_ready;
}

std::string Shader::get_log() const {
  int log_size = 0;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_size);

  if (log_size <= 1) {
    return "OK";
  }

  std::vector<char> message(log_size);

  glGetShaderInfoLog(id, log_size, nullptr, message.data());

  return std::string(message.data(), log_size - 1);
}

void Shader::delete_shader() {
  if (id != 0) {
    glDeleteShader(id);
  }
}
