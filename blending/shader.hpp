#pragma once
#include <string>

enum class ShaderType { Vertex, Fragment };

class Shader {
public:
  explicit Shader(ShaderType type);
  Shader(const Shader &) = delete;
  Shader(const Shader &&) = delete;
  void operator=(const Shader &) = delete;
  void operator=(const Shader &&) = delete;
  virtual ~Shader();

  virtual bool create_from_file(const std::string &file_name);
  virtual bool create_from_string(const std::string &content);

  virtual std::string get_log() const;
  bool is_valid() const { return is_ready; }
  unsigned int get_id() const { return id; }

  void delete_shader();

protected:
  bool is_ready = false;
  unsigned int id = 0;
};
