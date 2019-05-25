#version 450

layout (location = 0) in vec2 uv;
layout (location = 1) flat in int vert_index;
layout (set = 0, binding = 1) uniform sampler2D tex;
layout (set = 0, binding = 2) buffer dims
{
    float heights[20];
};

layout (location = 0) out vec4 color;

void main()
{
    int index = vert_index / 4;
    
    float x_ratio = 2.0;
    float y_ratio = heights[index];
    
    vec2 block_uv = uv * vec2(x_ratio, y_ratio);
    color = texture(tex, block_uv);
}