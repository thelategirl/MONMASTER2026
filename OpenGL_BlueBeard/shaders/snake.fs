#version 330
out vec4 fragColor;
in vec4 fpos;
in vec2 uv;
uniform float time;

#define A(k) vec2( 1.7 * cos(6.3 * t * (k)), sin(10.9 * t * (k)))

void main() {
    vec2 R = vec2(1200.0, 960.0);
    vec2 u = uv * R;
    float v = 1.0;
    for (float t = 0.0; t < 1.0; t+=0.001){
        bool cond1 = v > 0.0 ? (t < v): (t > 0.5);
        vec2 P = .5 * A(-0.3) + .3 * A(3.0);
        vec2  Q     = (u + u - R) / R.y;
        if(cond1 && length(P - Q) < 0.3) {v = t;}}
    float o = (v < 1.0) ? (9.0 * sin(300.0 * v - 9.0 * time) - 8.0) : 0.0;
    fragColor = vec4(vec3(o), 1.0);
    }
