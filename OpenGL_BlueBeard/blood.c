#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dh.h>
#include <stdio.h>

static void init(void);
static void draw(void);
static void sortie(void);

static GLuint _quadId = 0;
static GLuint _pId = 0;

void blood(int state) {
  switch(state) {
  case GL4DH_INIT:init();return;
  case GL4DH_FREE:sortie();return;
  case GL4DH_UPDATE_WITH_AUDIO: {return;}
  default:draw();return;}}


void init(void) {
  _pId = gl4duCreateProgram("<vs>shaders/blood.vs", "<fs>shaders/blood.fs", NULL);
  _quadId = gl4dgGenQuadf();
}

void draw(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0f,1.0f, 1.001f, 1.0f);
  glUseProgram(_pId);
  glUniform1f(glGetUniformLocation(_pId, "weight"),1.1);
  glUniform1f(glGetUniformLocation(_pId, "time"),gl4dGetElapsedTime()/1000.0f);
  gl4dgDraw(_quadId);
  glUseProgram(0);
}


void sortie(void) {printf("anyways6\n");}
