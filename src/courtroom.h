#ifndef COURTROOM_H_
#define COURTROOM_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "globals.h"
#include "structures.h"
#include "animations.h"
#include "draw_functions.h"
#include "camera.h"
#include "script_read.h"

// Init functions
void init(void);
void init_globals(void);
void init_SDL(void);
void init_GL(void);
void GL_Quit(void);
void printGLInfos(void);
void initTexture(void); 
void defTexture(const char * filename);


// Main functions
void game_loop(void);
int keyboard(SDL_Event * event);


// Quit functions
void quit_all(void);
void GL_Quit(void);


#endif // COURTROOM_H_
