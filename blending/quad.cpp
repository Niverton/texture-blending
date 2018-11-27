#include "opengl.hpp"
#include "quad.hpp"

using Eigen::Vector3f, Eigen::Vector3i, Eigen::Vector2f;

// TODO corriger les coordonnées de texture

Quad::Quad()
    : vertices{{{-1, -1, 0}, {1, -1, 0}, {1, 1, 0}, {-1, 1, 0}}},
      faces{{{0, 1, 3}, {1, 2, 3}}}, //
      texcoords{{{0, 1}, {1, 1}, {1, 0}, {0, 0}}} {
  //
}

void Quad::init(const sf::Image &image) {
  // Geometry

  glGenVertexArrays(1, &VAO);
  glGenBuffers(VBO_COUNT, VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTICES]);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3f),
               vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[FACES]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(Vector3i),
               faces.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXCOORDS]);
  glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(Vector2f),
               texcoords.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector2f), nullptr);
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  // Texture
  const unsigned char *data = image.getPixelsPtr();
  auto [w, h] = image.getSize();
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Quad::~Quad() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(VBO_COUNT, VBO);
  glDeleteTextures(1, &texture);
}

void Quad::draw(const ShaderProgram &shader) {
  glBindVertexArray(VAO);

  // Bind attributes

  int vertex_loc = shader.get_attribute_location("vtx_position");
  if (vertex_loc >= 0) {
    glEnableVertexAttribArray(vertex_loc);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTICES]);
    glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  }

  int texCoord_loc = shader.get_attribute_location("vtx_texcoord");
  if (texCoord_loc >= 0) {
    glEnableVertexAttribArray(texCoord_loc);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXCOORDS]);
    glVertexAttribPointer(texCoord_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  }

  // Bind uniforms
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  int text_loc = shader.get_uniform_location("text");
  glUniform1i(text_loc, 0);

  glDrawElements(GL_TRIANGLES, faces.size() * 3, GL_UNSIGNED_INT, nullptr);

  if (vertex_loc >= 0) {
    glDisableVertexAttribArray(vertex_loc);
  }
  if (texCoord_loc >= 0) {
    glDisableVertexAttribArray(texCoord_loc);
  }

  glBindVertexArray(0);
}
