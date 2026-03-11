#include <stdlib.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dh.h>
#include <GL4D/gl4duw_SDL2.h>
#include "animations.h"
#include "audioHelper.h"
static void init(void);
static void quit(void);
static void resize(int w, int h);
static void keydown(int keycode);

static GL4DHanime _animations[] = {
  { 1500, noir, NULL, NULL },
  { 4000, intro, NULL, NULL },
  { 2500, chandelier, NULL, NULL },
  { 1500, eyes, NULL, NULL },
  { 2000, snake, NULL, NULL },
  { 2000, buzz, NULL, NULL },
  { 4000, chandelier, NULL, NULL },
  //{ 5000, letter, NULL, NULL },
  { 1000, buzz, NULL, NULL },
  { 2000, chandelier, NULL, NULL },
  { 2000, blood, NULL, NULL },
  { 2000, chandelier, NULL, NULL },
  { 1000, buzz, NULL, NULL },
  { 2000, blood, NULL, NULL },
  { 1000, buzz, NULL, NULL },
  { 2000, chandelier, NULL, NULL },
  { 2000, blood, NULL, NULL },
  { 2000, chandelier, NULL, NULL },
  { 10000, texte_intro, NULL, NULL },
  { 1000, noir, NULL, NULL },
  {    0, NULL, NULL, NULL }
};

static GLfloat _dim[] = {1200, 960};

int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "BlueBeard",
			 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			 _dim[0], _dim[1],
			 SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwResizeFunc(resize);
  gl4duwKeyDownFunc(keydown);
  gl4duwDisplayFunc(gl4dhDraw);

  ahInitAudio("metronome-65396.mid");
  gl4duwMainLoop();
  return 0;
}

/*!\brief Cette fonction initialise les paramètres et éléments OpenGL
 * ainsi que les divers données et fonctionnalités liées à la gestion
 * des animations.
 */
static void init(void) {
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  gl4dhInit(_animations, _dim[0], _dim[1], animationsInit);
  resize(_dim[0], _dim[1]);
}

/*!\brief paramétre la vue (viewPort) OpenGL en fonction des
 * dimensions de la fenêtre.
 * \param w largeur de la fenêtre.
 * \param w hauteur de la fenêtre.
 */
static void resize(int w, int h) {
  _dim[0] = w; _dim[1] = h;
  glViewport(0, 0, _dim[0], _dim[1]);
}

/*!\brief permet de gérer les évènements clavier-down.
 * \param keycode code de la touche pressée.
 */
static void keydown(int keycode) {
  switch(keycode) {
  case SDLK_ESCAPE:
  case 'q':
    exit(0);
  default: break;
  }
}

/*!\brief appelée à la sortie du programme (atexit).
 */
static void quit(void) {
  ahClean();
  gl4duClean(GL4DU_ALL);
}
