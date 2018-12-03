#version 330 core

in vec4 vtx_position;
in vec2 vtx_texcoords;

out vec2 texcoords;
out vec2 smpcoords;
out vec2 vtxcoords;

void main() {
  texcoords = vtx_texcoords;
  smpcoords = vtx_texcoords*8;
  gl_Position = vtx_position;
}
