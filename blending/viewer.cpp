#include "opengl.hpp"
#include "rtexception.hpp"
#include "viewer.hpp"
#include <SFML/Graphics/Image.hpp>
#include <iostream>

Viewer::Viewer(sf::ContextSettings context, int argc, char **argv)
    : window{sf::VideoMode{800, 600}, "Texture Blending test",
             sf::Style::Default, context} {
  (void)argc;
  (void)argv;
  // std::cerr << context.majorVersion;
  window.setActive(true);
  glewInit(); // IMPORTANT
  glViewport(0, 0, 800, 600);
}

void Viewer::init() {
  std::cerr << "Vendor: \t" << glGetString(GL_VENDOR) << "\n";
  std::cerr << "Renderer:\t" << glGetString(GL_RENDERER) << "\n";
  std::cerr << "Version:\t" << glGetString(GL_VERSION) << "\n";
  std::cerr << "GLSL Version:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << "\n";

  // Init shaders
  Shader vertex{ShaderType::Vertex}, fragment{ShaderType::Fragment};

  auto validate = [](const Shader &s, std::string name) {
    if (!s.is_valid()) {
      std::cerr << "Error compiling " << name << "\nMessage:\n";
      std::cerr << s.get_log() << "\n";
      throw RTException("Shader compilation failed.\n");
    }
  };

  vertex.create_from_file("../shaders/simple.vert");
  validate(vertex, "Simple::Vertex");
  fragment.create_from_file("../shaders/simple.frag");
  validate(fragment, "Simple::Fragment");

  if (!simple_prg.create({&vertex, &fragment})) {
    std::cerr << "Error linking program Simple\n";
    std::cerr << simple_prg.get_log() << "\n";
    throw RTException("Shader linkage failed.\n");
  }

  glClearColor(0.f, 0.f, 0.f, 1.f);

  // Init scene
  // Load texture
  // TODO get file from argv
  sf::Image texture{};
  texture.loadFromFile("../data/brick.jpg");
  screen.init(texture);

  checkError();
}

int Viewer::run() {
  bool running = true;
  while (running) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        running = false;
      } else if (event.type == sf::Event::Resized) {
        // adjust the viewport when the window is resized
        glViewport(0, 0, event.size.width, event.size.height);
      }
    }

    update();
    window.display();
  }
  window.close();

  return 0;
}

void Viewer::update() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT
  simple_prg.enable();
  screen.draw(simple_prg);
  simple_prg.disable();

  checkError();
}
