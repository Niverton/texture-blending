#version 330 core

uniform sampler2D text;

in vec2 texcoords;

out vec4 out_color;

void main() {
  out_color = texture(text, texcoords);
  //out_color = vec4(texcoords, 0, 1);
}
