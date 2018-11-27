#pragma once

#include "quad.hpp"
#include "shader_program.hpp"
#include <SFML/Window.hpp>

class Viewer {
public:
  Viewer(sf::ContextSettings context, int argc, char **argv);
  void init();
  int run();
  void update();

protected:
  sf::Window window;
  Quad screen{};

  ShaderProgram simple_prg;
};
