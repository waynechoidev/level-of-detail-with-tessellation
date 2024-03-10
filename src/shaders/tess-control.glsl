#version 420 core

layout (vertices = 3) out;

in vec3 posWorld[];
in vec3 normalWorld[];
in vec2 TexCoord[];

out vec3 tc_posWorld[];
out vec3 tc_normalWorld[];
out vec2 tc_TexCoord[];

layout(std140) uniform Fragment
{
    vec3 viewPosition; // 12    0
    bool useTexture; // 4       12
    float depth; // 4           16
    // 20
};

void main() {
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    int index = gl_InvocationID;
    tc_posWorld[gl_InvocationID] = posWorld[gl_InvocationID];
    tc_normalWorld[gl_InvocationID] = normalWorld[gl_InvocationID];
    tc_TexCoord[gl_InvocationID] = TexCoord[gl_InvocationID];

    int scale = 6 + int(depth);

    gl_TessLevelOuter[0] = scale; // left for quads
    gl_TessLevelOuter[1] = scale; // bot for quads
    gl_TessLevelOuter[2] = scale; // right for quads
    gl_TessLevelOuter[3] = scale; // top for quads
    
    gl_TessLevelInner[0] = scale; // top bot for quads
    gl_TessLevelInner[1] = scale; // left right for quads
}
