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
void creer_pave (float a, float c, float e, float b, float d, float f); 
int keyboard(SDL_Event * event);
GLfloat angle = 0;
GLfloat angle2 = 0;

GLdouble near = 10.;
GLdouble far = 2000.;
GLfloat whereiam = 700.;
  
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
    if (event.key.keysym.sym == SDLK_KP_MINUS) {
        far+=10;
        whereiam+=10;
    }
    if (event.key.keysym.sym == SDLK_KP_PLUS) {
        if (whereiam > 10) {
        far-=10;
        whereiam-=10;
        }
    }
    if (event.key.keysym.sym == SDLK_UP) {
        if (angle < 1.5) {
        angle+=0.1;
        }
    }
    if (event.key.keysym.sym == SDLK_DOWN) {
        if (angle > -1.5) {
        angle-=0.1;
        }

    }
        if (event.key.keysym.sym == SDLK_LEFT) {
        if (angle2 < 1.5) {
        angle2+=0.1;
        }
    }
    if (event.key.keysym.sym == SDLK_RIGHT) {
        if (angle2 > -1.5) {
        angle2-=0.1;
        }

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
  gluLookAt(sin(angle2)*whereiam,sin(angle)*whereiam,cos(angle) * whereiam,0.,0.,0.,0.,1.,0.);
  
  glColor3f(197./255.,167./255., 147./255.);
  glBegin(GL_QUADS);
  glVertex3f(-500.,-750.,0.); 
  glVertex3f(-500.,750.,0.); 
  glVertex3f(500.,750.,0.);
  glVertex3f(500.,-750.,0.);
  glEnd();

  creer_pave(-100.,0.,0.,-200,400.,100.);
  creer_pave(100.,0.,0.,200,400.,100.);
  creer_pave(-200.,350.,0.,-300.,400.,100.);
  creer_pave(200.,350.,0.,300.,400.,100.);
  creer_pave(-300.,-300.,0.,-500.,400.,200.);
  creer_pave(300.,-300.,0.,500.,400.,200.);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(120.,1.,near,far);
  
  glMatrixMode(GL_MODELVIEW);
    
    
  SDL_GL_SwapWindow(fenetre);

  GLenum erreur;
  if ((erreur = glGetError()) != GL_NO_ERROR) {
    fprintf(stderr, "Erreur OpenGL dans display : %s\n", gluErrorString(erreur));
  }
 
}

void creer_pave (float a, float c, float e, float b,
                    float d, float f) {
              
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3f(a, c, f); // c'est le point en bas à gauche
  glVertex3f(b, c, f);  // on tourne dans le sens trigo
  glVertex3f(b, d, f);
  glVertex3f(a, d, f);
  glEnd();
  // On dessine un carré vert dans le plan -.4xy
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3f(a, c, e); 
  glVertex3f(b, c, e);  
  glVertex3f(b, d, e);
  glVertex3f(a, d, e);
  glEnd();
  //On dessine un carré bleu  .2yz
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glVertex3f(b, d, f); 
  glVertex3f(b, c, f); 
  glVertex3f(b, c, e);
  glVertex3f(b, d, e);
  glEnd();
    //On dessine un carré jaune  -.2yz
  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  glVertex3f(a, d, f); 
  glVertex3f(a, c, f); 
  glVertex3f(a, c, e);
  glVertex3f(a, d, e);
  glEnd();
  //On dessine un carré cyan  .2xz
  glColor3f(0.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glVertex3f(a, d, f); 
  glVertex3f(b, d, f); 
  glVertex3f(b, d, e);
  glVertex3f(a, d, e);
  glEnd();
  //On dessine un carré majenta -.2xz
  glColor3f(1.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glVertex3f(a, c, f); 
  glVertex3f(b, c, f); 
  glVertex3f(b, c, e);
  glVertex3f(a, c, e);
  glEnd();                        
                        
                        
  
  
                        
  }


    
