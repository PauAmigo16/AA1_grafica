#version 330

in vec4 vert_Normal;
in vec4 FragPos;
out vec4 out_Color;

uniform mat4 mv_Mat;
uniform vec4 color;

void main() {
	//ambient
	vec4 ambient = color;

	//Diffuse
	//vec4 diffuse = color;


	//Specular
	//vec4 specular = color;
	

	//
	out_Color = color;
}