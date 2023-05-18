#version 330

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 mv_Mat;
uniform mat4 mvpMat;
uniform mat4 proj_Mat;

uniform vec2 size;

out vec2 f_uvCoord;

void main() {
	//create quad
	vec4 center_pivot = gl_in[0].gl_Position;
			
	vec4 BottomLeft = center_pivot + vec4(-size.x, -size.y, 0.0, 0.0);
	vec4 BottomRight = center_pivot + vec4(size.x, -size.y, 0.0, 0.0);
	vec4 TopLeft = center_pivot + vec4(-size.x, size.y, 0.0, 0.0);
	vec4 TopRight = center_pivot + vec4(size.x, size.y, 0.0, 0.0);
		
	gl_Position = proj_Mat * vec4(BottomLeft.xyz, 1.0);
	f_uvCoord = vec2(1.0,1.0);
	EmitVertex();
		
	gl_Position = proj_Mat * vec4(BottomRight.xyz, 1.0);
	f_uvCoord = vec2(0.0,1.0);
	EmitVertex();
		
	gl_Position = proj_Mat * vec4(TopLeft.xyz, 1.0);
	f_uvCoord = vec2(1.0, 0.0); 
	EmitVertex();
		
	gl_Position = proj_Mat * vec4(TopRight.xyz, 1.0);
	f_uvCoord = vec2(0.0,0.0);
	EmitVertex();

	EndPrimitive();
}