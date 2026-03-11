#include <GL4D/gl4dh.h>
#include <stdio.h>
#include <SDL_ttf.h>

static void init(void);
static void draw(void);
static void sortie(void);

static GLuint _quadId = 0, _pId = 0, _texId = 0;

void texte_intro(int state) {
  switch(state) {
  case GL4DH_INIT: init();return;
  case GL4DH_FREE: sortie();return;
  case GL4DH_UPDATE_WITH_AUDIO: {return;}
  default:draw();return;}
}


void init(void) {
  SDL_Surface * s = NULL, * d = NULL;
  TTF_Font * font = NULL;
  SDL_Color c = {255, 255, 255, 255};

  _quadId = gl4dgGenQuadf();
  _pId = gl4duCreateProgram("<vs>shaders/texte.vs", "<fs>shaders/texte.fs", NULL);

  if(TTF_Init() == -1) {
    fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }
  if( !(font = TTF_OpenFont("Basic5.woff2", 100)) ) {
    fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
    exit(2);
  }

  s = TTF_RenderUTF8_Blended_Wrapped(font,"Auteurs: Fares Belhadj\n Anyce Ekomono\n\nPolice: Basic5.woff2\nMusique:\n\nRemerciments:\n\nEL CUBE\n", c, 900);
  if(s == NULL) {
    TTF_CloseFont(font);
    fprintf(stderr, "Erreur lors du TTF_RenderText\n");
    exit(2);
  }
  d = SDL_CreateRGBSurface(0, s->w, s->h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
  SDL_BlitSurface(s, NULL, d, NULL);
  SDL_FreeSurface(s);

  glGenTextures(1, &_texId);
  assert(_texId);

  glBindTexture(GL_TEXTURE_2D, _texId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, d->w, d->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, d->pixels);

  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(d);
  TTF_CloseFont(font);


  gl4duGenMatrix(GL_FLOAT, "model");
  gl4duGenMatrix(GL_FLOAT, "view");
  gl4duGenMatrix(GL_FLOAT, "proj_id");
  gl4duBindMatrix("proj_id");
  gl4duLoadIdentityf();
}

void draw(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(_pId);

  gl4duBindMatrix("view");
  gl4duLoadIdentityf();

  gl4duBindMatrix("model");
  gl4duLoadIdentityf();
  gl4duSendMatrices();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId);
  glUniform1i(glGetUniformLocation(_pId, "use_tex"), 1);
  gl4dgDraw(_quadId);

  glUseProgram(0);
}

void sortie(void) {
  if(_texId) {
    glDeleteTextures(1, &_texId);
    _texId= 0;
  }
}

/*Remerciement :
 * Farès Belhadj
 * EL CUBE
 * Le poisson Steve
*/

