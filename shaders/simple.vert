#version 330 core

in vec4 vtx_position;
in vec2 vtx_texcoords;

out vec2 texcoords;
out vec2 smpcoords;
out vec2 vtxcoords;

void main() {
  texcoords = vtx_texcoords;
  gl_Position = vtx_position;
}
