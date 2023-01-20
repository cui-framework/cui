#version 330 core

in vec2 textureCoords;
out vec4 fragColor;

uniform sampler2D tex;

void main() {
  vec4 modified = texture(tex, textureCoords);

  if (modified.a < 0.1) {
    discard;
  }

  fragColor = modified;
}
