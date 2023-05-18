#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 vert_UVs[];

out vec2 fragm_UVs;

void main() {
    for (int i = 0; i < 3; i++)
    {
        gl_Position = gl_in[i].gl_Position;
        fragm_UVs = vert_UVs[i];
        EmitVertex();
    }
    EndPrimitive();
}