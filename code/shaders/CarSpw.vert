#version 330

in vec3 in_Position;
in vec3 in_Normal;
out vec4 fragm_Normal;

uniform mat4 objMats[10];
uniform mat4 mv_Mat;
uniform mat4 mvpMat;

void main() {		
	gl_Position = mvpMat * objMats[gl_InstanceID] * vec4(in_Position, 1.0);
	fragm_Normal = mv_Mat * objMats[gl_InstanceID] * vec4(in_Normal, 0.0);		
}