#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dh.h>
#include <stdio.h>

static void init(void);
static void draw(void);
static void sortie(void);

static GLuint _sphereId = 0, _quadId = 0 ;
static GLuint _pId = 0;
static GLuint flamme = 0, nb=3;

void chandelier(int state) {
  switch(state) {
  case GL4DH_INIT:init();return;
  case GL4DH_FREE:sortie();return;
  case GL4DH_UPDATE_WITH_AUDIO: {return;}
  default:draw();return;}}

void init(void) {
  _pId = gl4duCreateProgram("<vs>shaders/candles.vs", "<fs>shaders/candles.fs", NULL);
  _sphereId = gl4dgGenSpheref(25, 25);
  _quadId = gl4dgGenQuadf();
}

void draw(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f,0.0f, 0.f, 1.0f);
  glUseProgram(_pId);
  float t = gl4dGetElapsedTime()/1000;
  printf("temps:%lf\n", t);
  if (t > 10) {nb = 2;}
  if (t > 18.0) {nb = 1;}
  for (int i = 0; i < nb; i++){
    flamme = 1;
    glUniform1i(glGetUniformLocation(_pId, "flamme"),flamme);
    glUniform1f(glGetUniformLocation(_pId, "time"),gl4dGetElapsedTime()/1000.0f);
    glUniform1i(glGetUniformLocation(_pId, "nb"),i);
    gl4dgDraw(_sphereId);
    flamme = 0;
    glUniform1i(glGetUniformLocation(_pId, "flamme"),flamme);
    glUniform1i(glGetUniformLocation(_pId, "nb"),i);
    gl4dgDraw(_quadId);
  }

  glUseProgram(0);
}

void sortie(void) {printf("anyways2\n");}
