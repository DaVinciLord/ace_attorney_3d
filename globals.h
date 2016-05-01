#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "structures.h"

// Global variables

// Partie Graphique
SDL_Window *fenetre;
SDL_GLContext context;
GLuint tex[122];
GLUquadric * quad;

GLfloat whereiamx;
GLfloat whereiamy;
GLfloat whereiamz;

GLfloat whereilookx;
GLfloat whereilooky;
GLfloat whereilookz;

GLdouble near;
GLdouble far;
int lock;
int deskslaming;
int noding;
int langledubrasdephoenixwright;
int mouvementmarteau;

Mix_Music *musique;
Mix_Music *musique_trial;
Mix_Music *musique_objection;
Mix_Music *musique_cornered;
Mix_Music *musique_moderate;
Mix_Music *musique_allegro;
Mix_Music *musique_foule;
Mix_Music *musique_marteau;
Mix_Music *musique_examination;

Mix_Chunk *chunk;
Mix_Chunk *musique_holdit;
Mix_Chunk *musique_takethat;
Mix_Chunk *musique_slam;
Mix_Chunk *musique_payne;
Mix_Chunk *musique_phoenix;

SDL_Event sdlevent;

struct evidence evidences;
char *talking;
char *slamming;
char *objecting;
int witness;
int good_objection;
int allegro;

#endif // GLOBALS_H_
