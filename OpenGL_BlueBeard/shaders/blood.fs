#version 330
out vec4 fragColor;
in vec2 uv;
uniform float time;

vec2 random2(vec2 st){
    st = vec2(dot(st,vec2(127.1,311.7)),
              dot(st,vec2(269.5,183.3)));
    return -1.0 + 2.0 * fract(sin(st) * 43758.5453123);
}

float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);
    vec2 u = f*f*(3.0 - 2.0*f);

    float a = dot(random2(i + vec2(0.0,0.0)), f - vec2(0.0,0.0));
    float b = dot(random2(i + vec2(1.0,0.0)), f - vec2(1.0,0.0));
    float c = dot(random2(i + vec2(0.0,1.0)), f - vec2(0.0,1.0));
    float d = dot(random2(i + vec2(1.0,1.0)), f - vec2(1.0,1.0));

    return mix(mix(a, b, u.x),
               mix(c, d, u.x), u.y);
}

void main() {
    vec2 iResolution = vec2(1200, 960);
    vec2 st = uv * iResolution;
    st /= iResolution.y;
    vec3 color = vec3(1.0, 0.5, 0.2);

    float t = abs(1.0 - sin(time * 0.1)) * 5.0;
    st += noise(st * 2.272) * t;

    // grosses gouttes sombres
    color += vec3(0.9, 0.017, 0.0)
          * smoothstep(1.076, 0.3, noise(st));

    // éclaboussures
    color += smoothstep(0.15, 0.2, noise(st * 10.0));
    color *= smoothstep(0.15, 0.6, noise(st * 10.0));

    fragColor = vec4(color, 1.0);
}
