#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>

SDL_Window *fenetre;
SDL_GLContext context;

void init_SDL(void);
void init_GL(void);
void printGLInfos(void);
void display(void);

int keyboard(SDL_Event * event);


int main(int argc, char **argv) {
  if (argc != 1) {
    fprintf(stderr, "Usage %s\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  init_SDL();
  init_GL();

  printGLInfos();

  SDL_ShowWindow(fenetre);
    
  int continuer = 1;
  SDL_Event event;
  
  
   while (continuer) {

    
    
    // On attend le prochain évènement
    SDL_WaitEvent(&event);
    // On traite l'évènement
    switch (event.type) {
    case SDL_QUIT:
      // On a fermé la fenetre
      continuer = 0;
      break;
    case SDL_KEYDOWN:
      // On a appuyé sur une touche
      continuer = keyboard(&event);
      break;
    }
    display();
}

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();

  return EXIT_SUCCESS;
}




void init_SDL(void) {
  if (SDL_VideoInit(NULL) < 0) {
    fprintf(stderr, "Couldn't initialize video driver: %s\n",
            SDL_GetError());
    exit(EXIT_FAILURE);
  }
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    
  fenetre = SDL_CreateWindow("The first Turnabout",
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             640, 640,
                             SDL_WINDOW_OPENGL);
  
  if (fenetre == 0) {
    fprintf(stderr, "Erreur lors de la création de la fenÃªtre (SDL)\n");
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  
  context = SDL_GL_CreateContext(fenetre);
  if (context == 0) {
    fprintf(stderr, "Erreur lors de la création du contexte OpenGL (SDL)\n");
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
}


void init_GL(void) {
  glClearColor(1., 1., 1., 0.);
  glEnable(GL_DEPTH_TEST);
}



void printGLInfos(void) {
  const GLubyte* string;
  
  string = glGetString(GL_VENDOR);
  printf("Marque fournissant l'implémentation OpenGL : %s\n", string);

  string = glGetString(GL_RENDERER);
  printf("Configuration graphique : %s\n", string);

  string = glGetString(GL_VERSION);
  printf("Version : %s\n", string);
}


int keyboard(SDL_Event * event) {
  if (event->type == SDL_KEYDOWN) {
    switch(event->key.keysym.sym) {
    case SDLK_ESCAPE:
      return 0;
    default:
      break;
    }
  }
  
  return 1;
}


void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.,510.,0.,0.,0.,0.,0.,0.,1.);
  
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glVertex3f(-250.,0.,-750.); 
  glVertex3f(-250.,0.,750.); 
  glVertex3f(250.,0.,750.);
  glVertex3f(250.,0.,-750.);
  glEnd();
  
  glLoadIdentity();
  GLdouble near = 10.;
  GLdouble far = 550;
  gluPerspective(120,1.,near,far);
  
  glMatrixMode(GL_MODELVIEW);
    
    
  SDL_GL_SwapWindow(fenetre);

  GLenum erreur;
  if ((erreur = glGetError()) != GL_NO_ERROR) {
    fprintf(stderr, "Erreur OpenGL dans display : %s\n", gluErrorString(erreur));
  }
 
}


    
