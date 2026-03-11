#version 330
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
uniform float weight;
uniform float time;
out vec4 fpos;
out vec2 uv;
void main(){gl_Position = vec4(pos, 1.0);uv = texCoord;}
