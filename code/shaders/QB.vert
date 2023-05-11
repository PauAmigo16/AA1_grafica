 #version 330

in vec3 in_Position;
in vec2 in_UVs;

uniform mat4 objMat;
uniform mat4 mv_Mat;
uniform mat4 mvpMat;

out vec2 vert_UVs;

void main() {
	gl_Position = mvpMat * objMat * vec4(in_Position, 1.0);
	vert_UVs = in_UVs;
}