#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;


uniform float time;
uniform int flamme;
uniform int nb;
uniform vec2 bp;

out vec4 fpos;
out vec2 uv;

void main() {
     float np = pos.x;
     np *= cos(time * -5.0 + pos.y * 2.0)* 0.2;

     if (nb == 0){
          if (flamme == 1){gl_Position = vec4(np, pos.y+1.2, pos.z, 1.5);}
          if (flamme == 0){gl_Position = vec4(pos.x/5.0, pos.y-1.0, pos.z, 1.0);}}
     else if (nb == 1) {
          if (flamme == 1) {gl_Position = vec4(np-1.0, pos.y+1.5, pos.z, 1.5);}
          if (flamme == 0) {gl_Position = vec4((pos.x/5.0) - 0.7, pos.y-0.8, pos.z, 1.0);}}
     else {

          if (flamme == 1) {gl_Position = vec4(np+1.0, pos.y+1.5, pos.z, 1.5);}
          if (flamme == 0) {gl_Position = vec4((pos.x/5.0) + 0.7, pos.y-0.8, pos.z, 1.0);}
     }

     fpos = gl_Position;
     uv = texCoord;
}
