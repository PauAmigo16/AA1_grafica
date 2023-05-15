#version 330

uniform mat4 objMat;
uniform mat4 mv_Mat;
uniform mat4 mvpMat;

in vec3 thePivot;

void main() {
	gl_Position = mv_Mat * objMat * vec4(thePivot, 1.0);
}