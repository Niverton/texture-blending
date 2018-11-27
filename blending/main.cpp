#include "viewer.hpp"
#include <SFML/Window/ContextSettings.hpp>
#include <exception>
#include <iostream>

int main(int argc, char **argv) {
  sf::ContextSettings context{24, 8, 0, 4, 5, sf::ContextSettings::Core};

  Viewer viewer{context, argc, argv};
  try {
    viewer.init();
    viewer.run();
  } catch (std::exception &e) {
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
