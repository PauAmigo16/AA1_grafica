#version 330

in vec2 vert_UVs;
out vec4 out_Color;

uniform sampler2D text;

void main() {
	out_Color = texture(text, vert_UVs);
}