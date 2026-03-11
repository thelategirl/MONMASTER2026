#version 330
out vec4 fragColor;
in vec4 fpos;
in vec2 uv;

uniform float time;
uniform int flamme;


// simple hash + bruit
float hash(float n) { return fract(sin(n)*43758.5453); }
float noise(vec2 x) {
    vec2 i = floor(x), f = fract(x);
    f = f*f*(3.0-2.0*f);
    float n = i.x + i.y*57.0;
    return mix(mix(hash(n+0.), hash(n+1.), f.x),
               mix(hash(n+57.),hash(n+58.), f.x),
               f.y);
}

// fbm (4 octaves)
float fbm(vec2 p){
    float f=0., w=1.;
    for(int i=0;i<4;i++){
        f += w*noise(p);
        p *= 2.0;
        w *= 0.5;
    }
    return f;
}

void main(){
    if (flamme == 1){
        // coordonnées de l’effet (de bas en haut)
        vec2 p = vec2(uv.x, uv.y*2.0 - time*0.5);

        // plus on monte, plus on disperse le bruit
        float f = fbm(p * vec2(2.0, 8.5));

        // ramer en bas pour simuler le “corps” de la flamme
        float flame = smoothstep(0.1, 1.0, uv.y) * f;

        // palette : de rouge sombre (bas) à jaune (sommet)
        vec3 col = mix(vec3(1.0,1.0,3.5),
                    vec3(0.0,0.0,1.0),
                    clamp(flame*2.0, 0.0, 1.0));

        // atténuer vers le haut
        col *= (0.6 - uv.y);

        fragColor = vec4(col, 1.0);
    }
    else {
        vec4 b = vec4(0, 0.051, 0.4, 1.0);
        vec4 j = vec4(2.1, 1.839, 1.059,1.0);
        vec4 n = vec4(0, 0, 0.03,1.0);
        //first = vec4(mix(j, b, (fpos.y+0.8)));
        fragColor = vec4(mix(b, j, (fpos.y+0.3)));
    }
    }

//     // simple hash + bruit
// float hash(float n) { return fract(sin(n)*43758.5453); }
// float noise(vec2 x) {
//     vec2 i = floor(x), f = fract(x*2);
//     f = f*f*(3.0-2.0*f);
//     float n = i.x + i.y*57.0;
//     return mix(mix(hash(n+0.), hash(n+1.), f.x),
//                mix(hash(n+57.),hash(n+58.), f.x),
// pour le sol               f.y);
// }
