#version 330
out vec4 fragColor;
in vec2 fpos;

uniform float time;


float noise21 (vec2 p, float ta, float tb) {
    return fract(sin(p.x * ta + p.y + tb) * 5678.0);
}

void main() {
    float t = time + 123.0;
    float ta = t * 0.654321;
    float tb = t * (ta * 0.123456);

    float c = noise21(fpos, ta, tb);
    fragColor = vec4(vec3(c), 1.0);
}



