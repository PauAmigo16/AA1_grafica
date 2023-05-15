#version 330

in vec2 vert_UVs;
out vec4 out_Color;

uniform sampler2D myTexture;

void main() {
	out_Color = texture(myTexture, vert_UVs);
}