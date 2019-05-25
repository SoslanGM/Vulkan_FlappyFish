#version 450

layout (location = 0) in vec4 coord;
layout (location = 1) in vec2 uv;
layout (set = 0, binding = 0) uniform matrix
{
    mat4 ortho;
};

layout (location = 0) out vec2 _uv;

void main()
{
    gl_Position = coord * ortho;
    _uv = uv;
}