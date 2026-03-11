/*!\file animations.h
 *
 * \brief Votre espace de liberté : c'est ici que vous pouvez ajouter
 * vos fonctions de transition et d'animation avant de les faire
 * référencées dans le tableau _animations du fichier \ref window.c
 *
 * Des squelettes d'animations et de transitions sont fournis pour
 * comprendre le fonctionnement de la bibliothèque. En bonus des
 * exemples dont un fondu en GLSL.
 *
 * \author Farès BELHADJ, amsi@up8.edu
 * \date April 12, 2023
 */
#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

  extern void noir(int state);
  extern void animationsInit(void);

  extern void intro(int state);
  extern void chandelier(int state);
  extern void eyes(int state);
  extern void snake(int state);
  extern void buzz(int state);
  extern void texte_intro(int state);
  extern void blood(int state);

  /*extern void wall_shade(int state);
  extern void god_rays(int state);
  extern void forest_fire(int state);
  extern void key(int state);*/

#ifdef __cplusplus
}
#endif

#endif
