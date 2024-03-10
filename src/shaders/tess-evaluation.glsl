#version 420 core

layout(triangles, equal_spacing, cw) in;

in vec3 tc_posWorld[];
in vec3 tc_normalWorld[];
in vec2 tc_TexCoord[];

out vec3 posWorld;
out vec3 normalWorld;
out vec2 TexCoord;

void main() {

  gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
                       gl_TessCoord.y * gl_in[1].gl_Position +
                       gl_TessCoord.z * gl_in[2].gl_Position);

        posWorld = gl_TessCoord.x * tc_posWorld[0] +
                   gl_TessCoord.y * tc_posWorld[1] +
                   gl_TessCoord.z * tc_posWorld[2];

        normalWorld = gl_TessCoord.x * tc_normalWorld[0] +
                      gl_TessCoord.y * tc_normalWorld[1] +
                      gl_TessCoord.z * tc_normalWorld[2];

        TexCoord = gl_TessCoord.x * tc_TexCoord[0] +
                   gl_TessCoord.y * tc_TexCoord[1] +
                   gl_TessCoord.z * tc_TexCoord[2];
}