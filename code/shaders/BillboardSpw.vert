#version 330

uniform mat4 objMat[5];
uniform mat4 mv_Mat;

in vec3 thePivot;

void main() {
	gl_Position = mv_Mat * objMat[gl_InstanceID] * vec4(thePivot, 1.0);
}