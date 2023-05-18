#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec4 vert_Normal[];

uniform mat4 mv_Mat;
uniform mat4 mvpMat;
uniform mat4 proj_Mat;

uniform float dt;

out vec4 frag_Normal;

void main()
{
	vec4 a=gl_in[1].gl_Position - gl_in[0].gl_Position;
	vec4 b=gl_in[2].gl_Position - gl_in[0].gl_Position;

	vec3 explodeNormal = normalize(cross(a.xyz, b.xyz));

	for(int i=0; i<3;i++)
	{
		gl_Position=gl_in[i].gl_Position + vec4(explodeNormal, 0.f)*dt;
		frag_Normal=vert_Normal[i];
		EmitVertex();
	}
	EndPrimitive();
}
