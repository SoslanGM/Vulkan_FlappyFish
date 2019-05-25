#version 450

layout (location = 0) in vec2 uv;
layout (set = 0, binding = 1) uniform sampler2D tex;

layout (location = 0) out vec4 color;

layout (push_constant) uniform push_offset
{
    uint y;
} offset;

void main()
{
    vec2 fish_uv = uv * vec2(0.5, 1.0) + vec2(0.5 * offset.y, 0.0);
    color = texture(tex, fish_uv);
}