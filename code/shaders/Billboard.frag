#version 330

uniform sampler2D text;

in vec2 f_uvCoord;

out vec4 color;

void main() {
	//color = vec4(0.9, 0.7, 0.7, 1.0);
	color = texture(text, f_uvCoord);
}