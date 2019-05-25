#version 450

//in int gl_VertexID;
layout (location = 0) in vec4 coord;
layout (location = 1) in vec2 uv;
layout (set = 0, binding = 0) uniform matrix
{
    mat4 orthographic;
};

layout (location = 0) out vec2 _uv;
layout (location = 1) out int vert_index;

void main()
{
    gl_Position = coord * orthographic;
    _uv = uv;
    vert_index = gl_VertexIndex;
}