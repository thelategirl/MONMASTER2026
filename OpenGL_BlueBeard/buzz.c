#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dh.h>
#include <stdio.h>

static void init(void);
static void draw(void);
static void sortie(void);

static GLuint _quadId = 0;
static GLuint _pId = 0;

void buzz(int state) {
  switch(state) {
  case GL4DH_INIT:init();return;
  case GL4DH_FREE:sortie();return;
  case GL4DH_UPDATE_WITH_AUDIO: {return;}
  default:draw();return;}}

void init(void) {
  _pId = gl4duCreateProgram("<vs>shaders/buzz.vs", "<fs>shaders/buzz.fs", NULL);
  _quadId = gl4dgGenQuadf();
}

void draw(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.5f, 0.9f, 0.1f, 1.0f);
  glUseProgram(_pId);
  glUniform1f(glGetUniformLocation(_pId, "weight"),1.5);
  glUniform1f(glGetUniformLocation(_pId, "time"),gl4dGetElapsedTime() / 100.0f);
  gl4dgDraw(_quadId);
  glUseProgram(0);
}

void sortie(void) {printf("anyways5\n");}

