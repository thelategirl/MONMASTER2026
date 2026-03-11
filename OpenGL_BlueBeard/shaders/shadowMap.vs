#version 330 core
// matrice “modèle” : position/rotation/échelle de l’objet
uniform mat4 mod;
// matrice “vue” depuis la lumière (lookAt)
uniform mat4 lightView;
// matrice de projection de la lumière
uniform mat4 lightProj;
layout (location = 0) in vec3 vsiPosition;
layout (location = 1) in vec3 vsiNormal;
layout (location = 2) in vec2 vsiTexCoord;

void main(void) {
  gl_Position = lightProj * lightView * mod * vec4(vsiPosition, 1.0);
}
