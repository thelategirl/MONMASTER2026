#include <GL4D/gl4duw_SDL2.h>
#include <GL4D/gl4dh.h>
#include <stdio.h>

static void init(void);
static void draw(void);
static void sortie(void);
static void resize(int width, int height);
static void scene(GLboolean sm, GLfloat dt);


static const GLuint SHADOW_MAP_SIDE = 4096;
static GLuint _wW = 1200, _wH = 960;
static GLuint _quadId = 0, _pId = 0, _smpId = 0, _smTex = 0, _fbo = 0;
static GLfloat campos[]  = {-6.0f,4.0f,-10.0f,1.0f};

void intro(int state){
  switch(state){
    case GL4DH_INIT:init(); return;
    case GL4DH_FREE:sortie(); return;
    case GL4DH_UPDATE_WITH_AUDIO: {return;}
    default: draw(); return;}}

void init(void){
  _pId = gl4duCreateProgram("<vs>shaders/lights.vs", "<fs>shaders/lights.fs", NULL);
  _smpId  = gl4duCreateProgram("<vs>shaders/shadowMap.vs", "<fs>shaders/shadowMap.fs", NULL);
  _quadId = gl4dgGenQuadf();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  gl4duGenMatrix(GL_FLOAT, "proj");
  gl4duGenMatrix(GL_FLOAT, "mod");
  gl4duGenMatrix(GL_FLOAT, "view");
  gl4duGenMatrix(GL_FLOAT, "lightView");
  gl4duGenMatrix(GL_FLOAT, "lightProj");

  glGenTextures(1, &_smTex); assert(_smTex);
  glBindTexture(GL_TEXTURE_2D, _smTex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_MAP_SIDE, SHADOW_MAP_SIDE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glGenFramebuffers(1, &_fbo);
  resize(_wW, _wH);
}

static void resize(int width, int height) {
  GLfloat ratio;
  _wW = width;
  _wH = height;
  glViewport(0, 0, _wW, _wH);
  ratio = _wW / ((GLfloat)_wH);
  gl4duBindMatrix("proj");
  gl4duLoadIdentityf();
  gl4duFrustumf(-ratio, ratio, -1.0f, 1.0f, 2.0f, 100.0f);
  gl4duBindMatrix("lightProj");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.1f, 0.1f, -0.1f, 0.1f, 0.1f, 50.0f);
}

void draw(void){
  GLenum rendering = GL_COLOR_ATTACHMENT0;
  static double t0 = 0.0;
  double t = gl4dGetElapsedTime() / 1000.0, dt = t - t0;
  t0 = t;
  //printf("time:%lf\n", t);

  glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
  glDrawBuffer(GL_NONE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,    GL_TEXTURE_2D, 0, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _smTex, 0);
  glViewport(0, 0, SHADOW_MAP_SIDE, SHADOW_MAP_SIDE);
  glClear(GL_DEPTH_BUFFER_BIT);
  scene(GL_TRUE, dt);

  glDrawBuffers(1, &rendering);
  glViewport(0, 0, _wW, _wH);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gl4duBindMatrix("view");
  gl4duLoadIdentityf();
  gl4duLookAtf(campos[0], campos[1], campos[2], 0, 0, 0, 0.0f, 1.0f, 0);
  scene(GL_FALSE, dt);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);
}

void scene(GLboolean sm, GLfloat dt) {
  GLfloat lumpos0[] = {-1.0f, 10.0f,3.0f,1.0f}, lumpos[4];
  campos[0] += dt/2;

  GLfloat gris[] = {0.1f, 0.1f, 0.1f, 1.0f},
          noir[] = {0.0f, 0.0f, 0.0f, 1.0f},
          bleu[] = {0.0f, 1.5f, 0.9f, 1.0f};

  // on place une camera sur la lumière.
  gl4duBindMatrix("view");
  GLfloat* mat = (GLfloat*)gl4duGetMatrixData();
  MMAT4XVEC4(lumpos, mat, lumpos0);


  if (sm) {
    glUseProgram(_smpId);
    glCullFace(GL_FRONT);//On supprime les faces AVANT qui se feraient de l'ombre sur elles meme
    gl4duBindMatrix("lightView");
    gl4duLoadIdentityf();
    gl4duLookAtf(lumpos0[0], lumpos0[1], lumpos0[2], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);
  } else {
    glUseProgram(_pId);
    glCullFace(GL_BACK);

  }
  glEnable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _smTex);
  glUniform1i(glGetUniformLocation(_pId, "smTex"), 0);
  glEnable(GL_CULL_FACE); // Supprime les faces arrieres pour ameliorer les perfs

  gl4duBindMatrix("mod");
  glUniform4fv(glGetUniformLocation(_pId, "lcolor"), 1, bleu);
  glUniform4fv(glGetUniformLocation(_pId, "lumpos"), 1, lumpos);

 // MUR1
  gl4duLoadIdentityf();
  glDisable(GL_CULL_FACE);
  gl4duTranslatef(-3.5f, 3.0f, -1.5f);
  gl4duScalef(3.0f, 3.0f, 1.0f);
  //gl4duRotatef(180.0f, 1.0f, 0.0f, 0.0f);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "scolor"), 1, noir);
  gl4dgDraw(_quadId);

  // MURS 2
  gl4duLoadIdentityf();
  gl4duTranslatef(5.5f, 3.0f, -1.5f);
  gl4duScalef(3.0f, 3.0f, 1.0f);
  //gl4duRotatef(-180.0f, 1.0f, 0.0f, 0.0f);
  gl4duSendMatrices();
  gl4dgDraw(_quadId);

  // SOL
  gl4duLoadIdentityf();
  gl4duTranslatef(0.0f, 0.0f, -1.0f);
  gl4duScalef(8.0f, 1.0f, 8.0f);
  gl4duRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  gl4duSendMatrices();
  glUniform4fv(glGetUniformLocation(_pId, "scolor"), 1, gris);
  gl4dgDraw(_quadId);

  glUseProgram(0);
}

void sortie(void) {
  printf("anyway1\n");
}
