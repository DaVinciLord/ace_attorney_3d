#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include <GL/glu.h>
#include <GL/gl.h>

SDL_Window *fenetre;
SDL_GLContext context;
GLuint tex[2];
void sol(int x0, int y0, int x1, int y1);
void defTexture(const char * filename);
void init_SDL(void);
void init_GL(void);
void printGLInfos(void);
void display(void);
void creer_pave (float a, float c, float e, float b, float d, float f);
void initTexture(); 
int keyboard(SDL_Event * event);
GLfloat whereiamx = 0.;
GLfloat whereiamy = 0.;
GLfloat whereiamz = 1000.;

GLdouble near = 10.;
GLdouble far = 2000.;

GLfloat matSpeculaire[4] = {1., 1., 1., 1.};
GLfloat matShininess = 50.;
GLfloat matBeige[4] = {197./255.,167./255., 147./255., 1.};
GLfloat matBrun[4] = {124./255., 64./255., 0., 1.};
  
int main(int argc, char **argv) {
  if (argc != 1) {
    fprintf(stderr, "Usage %s\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  init_SDL();
  init_GL();
  initTexture();
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
        whereiamz+=10;
    }
    if (event.key.keysym.sym == SDLK_KP_PLUS) {
        whereiamz -=10;
    }
    if (event.key.keysym.sym == SDLK_UP) {
        whereiamy+=10;
    }
    if (event.key.keysym.sym == SDLK_DOWN) {
        whereiamy -=10;
    }
    if (event.key.keysym.sym == SDLK_LEFT) {
        whereiamx -=10;
    }
    if (event.key.keysym.sym == SDLK_RIGHT) {
        whereiamx+=10;
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
  //glEnable(GL_CULL_FACE);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  //GLfloat intensite[] = {1.,1.,1, 1.};
 // glLightfv(GL_LIGHT0, GL_AMBIENT, intensite);
 // glLightfv(GL_LIGHT0, GL_DIFFUSE, intensite);
  
 // glLightfv(GL_LIGHT0, GL_SPECULAR, intensite);
  
  
 

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
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
  gluLookAt(whereiamx,whereiamy,whereiamz,0.,100.,180. ,- whereiamx + 1,-whereiamy + 100 ,180.);
  GLfloat pos[] = {0, 0, 500, 1};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpeculaire);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);
  
  
  //glColor3f(197./255.,167./255., 147./255.);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBeige);
  sol(-500,-750, 0, -250);
  sol(0,-750, 500, -250);
  sol(-500,-250, 0, 250);
  sol(0,-250, 500, 250);
  sol(-500, 250, 0, 750);
  sol(0,250, 500, 750);
  

  glBindTexture(GL_TEXTURE_2D, tex[1]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun);

  creer_pave(-100.,0.,0.,-200,400.,100.);
  creer_pave(100.,0.,0.,200,400.,100.);
  
  creer_pave(-200.,350.,0.,-300.,400.,100.);
  creer_pave(200.,350.,0.,300.,400.,100.);
  creer_pave(-300.,-300.,0.,-500.,400.,200.);
  creer_pave(300.,-300.,0.,500.,400.,200.);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60.,1.,near,far);
  
  glMatrixMode(GL_MODELVIEW);
    
    
  SDL_GL_SwapWindow(fenetre);

  GLenum erreur;
  if ((erreur = glGetError()) != GL_NO_ERROR) {
    fprintf(stderr, "Erreur OpenGL dans display : %s\n", gluErrorString(erreur));
  }
 
}

void creer_pave (float a, float c, float e, float b,
                    float d, float f) {
              
  glBegin(GL_QUADS);
  glNormal3f(0, 0, 1);
  glTexCoord2f(0., 0.); glVertex3f(a, c, f); // c'est le point en bas à gauche
  glTexCoord2f(0., 1.); glVertex3f(b, c, f);  // on tourne dans le sens trigo
  glTexCoord2f(1., 1.); glVertex3f(b, d, f);
  glTexCoord2f(1., 0.); glVertex3f(a, d, f);
  glEnd();
  // On dessine un carré vert dans le plan -.4xy
  glBegin(GL_QUADS);
  glNormal3f(0, 0, -1);
  glTexCoord2f(0., 0.); glVertex3f(a, c, e); 
  glTexCoord2f(1., 0.); glVertex3f(a, d, e);
  glTexCoord2f(1., 1.); glVertex3f(b, d, e); 
  glTexCoord2f(0., 1.); glVertex3f(b, c, e);  
  glEnd();
  //On dessine un carré bleu  .2yz
  glBegin(GL_QUADS);
  glNormal3f(1, 0, 0);
  glTexCoord2f(0., 0.); glVertex3f(b, d, f); 
  glTexCoord2f(0., 1.); glVertex3f(b, c, f); 
  glTexCoord2f(1., 1.);  glVertex3f(b, c, e);
  glTexCoord2f(1., 0.); glVertex3f(b, d, e);
  glEnd();
    //On dessine un carré jaune  -.2yz
  glBegin(GL_QUADS);
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0., 0.); glVertex3f(a, d, f); 
  glTexCoord2f(1., 0.); glVertex3f(a, d, e); 
  glTexCoord2f(1., 1.); glVertex3f(a, c, e);  
  glTexCoord2f(0., 1.); glVertex3f(a, c, f); 
  glEnd();
  //On dessine un carré cyan  .2xz
  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);
  glTexCoord2f(0., 0.); glVertex3f(a, d, f); 
  glTexCoord2f(0., 1.); glVertex3f(b, d, f); 
  glTexCoord2f(1., 1.); glVertex3f(b, d, e);
  glTexCoord2f(1., 0.); glVertex3f(a, d, e);
  glEnd();
  //On dessine un carré majenta -.2xz
  glBegin(GL_QUADS);
  glNormal3f(0, -1, 0);
  glTexCoord2f(0., 0.); glVertex3f(a, c, f); 
  glTexCoord2f(1., 0.); glVertex3f(a, c, e); 
  glTexCoord2f(1., 1.); glVertex3f(b, c, e); 
  glTexCoord2f(0., 1.); glVertex3f(b, c, f); 
  glEnd();                        
                        
                        
  
  
                        
  }
  
  
  
  
  

void initTexture() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(2, tex);

    // On définit la première texture
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    defTexture("texture_sol.bmp");
    // On définit la deuxième texture
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    defTexture("texture_meuble.bmp");

    // On spécifie comment les textures seront plaquées sur les facettes
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    GLenum erreur;
    if ((erreur = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "Erreur OpenGL dans setTexture : %s\n", gluErrorString(erreur));
    }

}

void defTexture(const char * filename) {
    // On fixe les paramètres de la texture,
    // i.e. comment on calcule les coordonnées pixels -> texels.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // On charge l'image qui va nous servir de texture via la SDL
    SDL_Surface* image = IMG_Load(filename);
    if(!image) {
      fprintf(stderr, "Impossible de charger l'image : %s\n", IMG_GetError());
      exit(EXIT_FAILURE);
    }

    // On verrouille l'image pendant qu'on l'utilise
    if (SDL_MUSTLOCK(image)) {
        SDL_LockSurface(image);
    }

    // On envoie le tableau contenant les texels de la texture à OpenGL
    if (image->format->BytesPerPixel == 3) {
      // L'image d'origine n'a que trois composantes
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    } else if (image->format->BytesPerPixel == 4) {
      // L'image d'origine à quatre composantes
      // (la dernière est le paramètre alpha qui va nous servir à gérer la transparence)
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    } else {
      fprintf(stderr, "Nombre de composants de l'image différent de 3 et 4\n");
      exit(EXIT_FAILURE);
    }

    // On libère les ressources occupées par l'image
    if (SDL_MUSTLOCK(image)) {
        SDL_UnlockSurface(image);
    }
    SDL_FreeSurface(image);
 }    

void sol(int x0, int y0, int x1, int y1) {
   int step = 250;
   for (int i = x0; i < x1; i+= step) {
	   for (int j = y0; j < y1; j += step) {
			  glBindTexture(GL_TEXTURE_2D, tex[0]);
			  glNormal3f(0, 0, 1);

			  glBegin(GL_QUADS);

			  glTexCoord2f(0., 0.); glVertex3f(i , j, 0.); 
              glTexCoord2f(1., 0.); glVertex3f(i + step, j,0.);
			  glTexCoord2f(1., 1.); glVertex3f(i + step , j + step, 0.);
              glTexCoord2f(0., 1.); glVertex3f(i , j + step, 0.);
			  glEnd(); 
		   
	   }
	   
   }
	   
	   



  
}