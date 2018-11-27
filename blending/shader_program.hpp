#pragma once

#include "shader.hpp"
#include <vector>

class ShaderProgram {
public:
  ShaderProgram() = default;
  ShaderProgram(const ShaderProgram &) = delete;
  ShaderProgram(const ShaderProgram &&) = delete;
  void operator=(const ShaderProgram &) = delete;
  void operator=(const ShaderProgram &&) = delete;
  virtual ~ShaderProgram();

  unsigned int get_id() const { return id; }
  bool is_valid() const { return is_ready; }

  std::string get_log() const;

  void enable();
  void disable();

  int get_attribute_location(const char *attribute) const;
  int get_uniform_location(const char *uniform) const;

  bool create(std::vector<const Shader *> shaders);

  void link();
  void delete_program();

protected:
  unsigned int id = 0;
  bool is_ready = false;
};
