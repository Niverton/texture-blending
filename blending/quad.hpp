#pragma once
#include "shader_program.hpp"
#include <SFML/Graphics/Image.hpp>
#include <eigen3/Eigen/Core>

class Quad {
public:
  Quad();
  Quad(const Quad &) = delete;
  Quad(const Quad &&) = delete;
  void operator=(const Quad &) = delete;
  void operator=(const Quad &&) = delete;
  virtual ~Quad();
  void init(const sf::Image &image);
  void draw(const ShaderProgram &shader);

protected:
  std::array<Eigen::Vector3f, 4> vertices;
  std::array<Eigen::Vector3i, 2> faces;
  std::array<Eigen::Vector2f, 4> texcoords;

  // VBO indexes
  enum {
    VERTICES = 0,
    FACES,
    TEXCOORDS,
    // NORMALS,
    /* INSERT NEW BEFORE */ VBO_COUNT
  };
  unsigned int VBO[VBO_COUNT] = {0};
  unsigned int VAO = 0;
  unsigned int texture = 0;
};
