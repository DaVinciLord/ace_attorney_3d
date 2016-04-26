#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include <GL/glu.h>
#include <GL/gl.h>


SDL_Window *fenetre;
SDL_GLContext context;
GLuint tex[103];
GLUquadric * quad;
void creer_phoenix();
void creer_winston();
void creer_mia();
void creer_juge();
void creer_witness_1();
void creer_witness_2();
void sol(int x0, int y0, int x1, int y1);
void defTexture(const char * filename);
void init_SDL(void);
void init_GL(void);
void GL_Quit();
void printGLInfos(void);
void display(void);
void initTexture(); 
int keyboard(SDL_Event * event);
void creer_pave_2 (float centrex, float centrey, float centrez, float hauteur,
                    float largeur, float profondeur);
void creer_murs (GLfloat centrex, GLfloat centrey, GLfloat centrez, GLfloat largeur,
                    GLfloat profondeur, GLfloat hauteur);
void creer_pave_with_texture (GLfloat centrex, GLfloat centrey, 
                            GLfloat centrez, GLfloat largeur,
                            GLfloat profondeur, GLfloat hauteur,
                           GLuint tex1, GLuint tex2, GLuint tex3, 
                           GLuint tex4, GLuint tex5, GLuint tex6);
void creer_witness_stand();

GLfloat whereiamx = 0.;
GLfloat whereiamy = 0.;
GLfloat whereiamz = 1000.;

GLfloat whereilookx = 0.;
GLfloat whereilooky = 100.;
GLfloat whereilookz = 180.;

GLdouble near = 10.;
GLdouble far = 3000.;

GLfloat matSpeculaire[4] = {1., 1., 1., 1.};
GLfloat matShininess = 50.;
GLfloat matBeige[4] = {197./255.,167./255., 147./255., 1.};
GLfloat matBrun[4] = {124./255., 64./255., 0., 1.};
GLfloat matBrunClair[4] = {240./255., 140./255., 70./255., 1.};
GLfloat matArgent[4] = {206./255., 206./255., 206./255., 1.};
GLfloat matOr[4] = {1., 215./255., 0., 1.};
GLfloat matBeigeClair[4] = {245./255., 245./255., 220/255., 1.};

  
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
    switch (event.key.keysym.sym) {
        case SDLK_KP_MINUS : 
        whereiamz += 10;
        break;
        case SDLK_KP_PLUS :
        whereiamz -= 10;
        break;
        case SDLK_UP :
        whereiamy += 10;
        break;
        case SDLK_DOWN :
        whereiamy -= 10;
        break;
        case SDLK_LEFT :
        whereiamx -= 10;
        break;
        case SDLK_RIGHT :
        whereiamx += 10;
        break;
        case SDLK_z :
        whereilooky += 10;
        break;
        case  SDLK_s :
        whereilooky -= 10;
        break;
        case SDLK_d :
        whereilookx += 10;
        break;
        case SDLK_q :
        whereilookx -= 10;
        break;
        case SDLK_a :
        whereilookz -= 10;
        break;
        case SDLK_e :
        whereilookz += 10;
        break;
        
    }
    
    display();
    
}
  GL_Quit();
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
  glEnable(GL_CULL_FACE);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHT1);
 // glEnable(GL_LIGHT2);
  GLfloat intensite[] = {0.2,0.2,0.2, 1.};

  //glLightfv(GL_LIGHT1, GL_DIFFUSE, intensite);
  glLightfv(GL_LIGHT0, GL_AMBIENT, intensite);
  //glLightfv(GL_LIGHT2, GL_DIFFUSE, intensite);
 // glLightfv(GL_LIGHT2, GL_SPECULAR, intensite);
  
 

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  quad = gluNewQuadric();
  gluQuadricOrientation(quad, GLU_OUTSIDE);
  gluQuadricNormals(quad, GLU_SMOOTH);
  gluQuadricTexture(quad, GL_TRUE);
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
  gluLookAt(whereiamx,whereiamy,whereiamz,whereilookx, whereilooky, whereilookz ,- whereiamx + whereilookx ,-whereiamy + whereilooky , whereilookz );
  GLfloat pos[] = {0, 0, 1000, 1};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
        pos[2] = -50.;
  glLightfv(GL_LIGHT1, GL_POSITION, pos);
        pos[1] = -650.;
  glLightfv(GL_LIGHT2, GL_POSITION, pos);
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrunClair);


     
     creer_pave_2(-150., 200., 50., 100., 400., 100.); // bureau du procureur
     creer_pave_2(150., 200., 50., 100., 400., 100.);  // bureau de l'avocat
     creer_pave_2(-250., 375., 50., 100., 50., 100.);  // jonction gauche
     creer_pave_2(250., 375., 50., 100., 50., 100.);   // jonction droite
     
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun); 
     creer_pave_2(-325., 50., 100., 50., 700., 200.); //Gradins hauts
     creer_pave_2(325., 50., 100., 50., 700., 200.);
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrunClair);
     creer_pave_2(-377.5, 50., 50., 55., 700., 100.); //Gradins medians
     creer_pave_2(377.5, 50., 50., 55., 700., 100.);

     creer_pave_2(-425., 50., 25., 40., 700., 50.); //Gradins bas
     creer_pave_2(425., 50., 25., 40., 700., 50.);
     
     creer_pave_2(-250., 625., 150., 200., 100., 300.); // bureaux du juge gauche
     creer_pave_2(250., 625., 150., 200., 100., 300.);  // droit
     creer_pave_2(0., 600., 150., 300., 100., 300.);    // centre
     
     creer_pave_2(-250., 712.5, 100., 200., 75., 200.);   // estrade
     creer_pave_2(250., 712.5, 100., 200., 75., 200.);
     creer_pave_2(0., 700., 100., 300., 100., 200.);
     
     
    creer_pave_2(0., 739, 350., 200., 22., 300.);  // manteau sous le blason

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBeige);
     glBindTexture(GL_TEXTURE_2D, tex[6]);  
     creer_phoenix();
     creer_winston();
     creer_mia();
     creer_juge();
//creer_witness_1();
     
     creer_witness_2();
     
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matOr);
     glBindTexture(GL_TEXTURE_2D, tex[4]);  
     creer_pave_2(-125.,725.,350.,50.,50.,300.);  //montants derriere le juge
     creer_pave_2(125.,725.,350.,50.,50.,300.);
     creer_pave_2(0., 718., 475., 200., 20., 50.); //revetement derriere le juge 
    
     creer_witness_stand();
    
    
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBeigeClair);
     glBindTexture(GL_TEXTURE_2D, tex[5]);
     creer_murs(0., 0., 500, 1000., 1500., 1000.);

     
    
    glBindTexture(GL_TEXTURE_2D, tex[1]); 
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun);
  glTranslatef(0., 730., 500.);
  glRotatef(90., 1., 0., 0.); 
  gluDisk(quad, 0., 150., 20., 1.);  //cercle bois situé derriere le juge
  glPopMatrix();
  
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun);
  glTranslatef(0., 750., 500.);
  glRotatef(-90., 1., 0., 0.); 
  gluDisk(quad, 0., 150., 20., 1.);  //cercle bois situé derriere le juge -- coté mur
  glPopMatrix();
  
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun);
  glTranslatef(0., 750., 500.);
  glRotatef(90., 1., 0., 0.); 
  gluCylinder(quad,    150.,    150.,    20.,    20.,    1.); // cylindre reliant les deux cercles 
  glPopMatrix();
  
  
  
  
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[3]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matArgent);
  glTranslatef(0., 710., 550.);
  glRotatef(90., 1., 0., 0.); 
  gluDisk(quad, 0., 50., 20., 1.);  //blason coté face
  glPopMatrix();
  
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[2]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matArgent);
  glTranslatef(0., 730., 550.);
  glRotatef(-90., 1., 0., 0.); 
  gluDisk(quad, 0., 50., 20., 1.);   //blason coté mur
  glPopMatrix();
  
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matArgent);
  glTranslatef(0., 730., 550.);
  glRotatef(90., 1., 0., 0.); 
  gluCylinder(quad,    50.,    50.,    20.,    20.,    1.); // tranche du blason
  glPopMatrix();
  
 
 
 
 
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

  
  
  
  
  

void initTexture() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(103, tex);

    // On définit la première texture
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    defTexture("texture_sol.bmp");
    // On définit la deuxième texture
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    defTexture("texture_meuble.bmp");

    glBindTexture(GL_TEXTURE_2D, tex[2]);
    defTexture("argent.bmp");
    
    glBindTexture(GL_TEXTURE_2D, tex[3]);
    defTexture("argent_balance.bmp");
    
    glBindTexture(GL_TEXTURE_2D, tex[4]);
    defTexture("gold.png");
        glBindTexture(GL_TEXTURE_2D, tex[5]);
    defTexture("wall.bmp");
    glBindTexture(GL_TEXTURE_2D, tex[6]);
    defTexture("phoenix.bmp");
    glBindTexture(GL_TEXTURE_2D, tex[7]);
    defTexture("face_pw.png");
    glBindTexture(GL_TEXTURE_2D, tex[8]);
    defTexture("face_arriere_pw.png");
    glBindTexture(GL_TEXTURE_2D, tex[9]);
    defTexture("face_dessous_pw.png");
    glBindTexture(GL_TEXTURE_2D, tex[10]);
    defTexture("face_dessus_pw.png");
    glBindTexture(GL_TEXTURE_2D, tex[11]);
    defTexture("face_droit_pw.png");
    glBindTexture(GL_TEXTURE_2D, tex[12]);
    defTexture("face_gauche_pw.png");
    glBindTexture(GL_TEXTURE_2D, tex[13]);
    defTexture("corps_arriere_pw.png");
    glBindTexture(GL_TEXTURE_2D, tex[14]);
    defTexture("corps_pw.png");
    glBindTexture(GL_TEXTURE_2D, tex[15]);
    defTexture("corps_cote_pw.png");
    glBindTexture(GL_TEXTURE_2D, tex[16]);
    defTexture("corps_haut_pw.png");
    glBindTexture(GL_TEXTURE_2D, tex[17]);
    defTexture("corps_bas_pw.png");
        glBindTexture(GL_TEXTURE_2D, tex[18]);
    defTexture("bras_pw.png");
        glBindTexture(GL_TEXTURE_2D, tex[19]);
    defTexture("main_pw.png");
        glBindTexture(GL_TEXTURE_2D, tex[20]);
    defTexture("jambe_dessus_pw.png");
        glBindTexture(GL_TEXTURE_2D, tex[21]);
    defTexture("jambe_pw.png");
        glBindTexture(GL_TEXTURE_2D, tex[22]);
    defTexture("pied_pw.png"); 
    glBindTexture(GL_TEXTURE_2D, tex[23]);
    defTexture("face_wp.png");
    glBindTexture(GL_TEXTURE_2D, tex[24]);
    defTexture("face_arriere_wp.png");
    glBindTexture(GL_TEXTURE_2D, tex[25]);
    defTexture("face_dessous_wp.png");
    glBindTexture(GL_TEXTURE_2D, tex[26]);
    defTexture("face_dessus_wp.png");
    glBindTexture(GL_TEXTURE_2D, tex[27]);
    defTexture("face_droit_wp.png");
    glBindTexture(GL_TEXTURE_2D, tex[28]);
    defTexture("face_gauche_wp.png");
    glBindTexture(GL_TEXTURE_2D, tex[29]);
    defTexture("corps_arriere_wp.png");
    glBindTexture(GL_TEXTURE_2D, tex[30]);
    defTexture("corps_wp.png");
    glBindTexture(GL_TEXTURE_2D, tex[31]);
    defTexture("corps_cote_wp.png");
    glBindTexture(GL_TEXTURE_2D, tex[32]);
    defTexture("corps_haut_wp.png");
    glBindTexture(GL_TEXTURE_2D, tex[33]);
    defTexture("corps_bas_wp.png");
        glBindTexture(GL_TEXTURE_2D, tex[34]);
    defTexture("bras_wp.png");
        glBindTexture(GL_TEXTURE_2D, tex[35]);
    defTexture("main_wp.png");
        glBindTexture(GL_TEXTURE_2D, tex[36]);
    defTexture("jambe_dessus_wp.png");
        glBindTexture(GL_TEXTURE_2D, tex[37]);
    defTexture("jambe_wp.png");
        glBindTexture(GL_TEXTURE_2D, tex[38]);
    defTexture("pied_wp.png"); 
    glBindTexture(GL_TEXTURE_2D, tex[39]);
    defTexture("face_mia.png");
    glBindTexture(GL_TEXTURE_2D, tex[40]);
    defTexture("face_arriere_mia.png");
    glBindTexture(GL_TEXTURE_2D, tex[41]);
    defTexture("face_dessous_mia.png");
    glBindTexture(GL_TEXTURE_2D, tex[42]);
    defTexture("face_dessus_mia.png");
    glBindTexture(GL_TEXTURE_2D, tex[43]);
    defTexture("face_droit_mia.png");
    glBindTexture(GL_TEXTURE_2D, tex[44]);
    defTexture("face_gauche_mia.png");
    glBindTexture(GL_TEXTURE_2D, tex[45]);
    defTexture("corps_arriere_mia.png");
    glBindTexture(GL_TEXTURE_2D, tex[46]);
    defTexture("corps_mia.png");
    glBindTexture(GL_TEXTURE_2D, tex[47]);
    defTexture("corps_cote_mia.png");
    glBindTexture(GL_TEXTURE_2D, tex[48]);
    defTexture("corps_haut_mia.png");
    glBindTexture(GL_TEXTURE_2D, tex[49]);
    defTexture("corps_bas_mia.png");
        glBindTexture(GL_TEXTURE_2D, tex[50]);
    defTexture("bras_mia.png");
        glBindTexture(GL_TEXTURE_2D, tex[51]);
    defTexture("main_mia.png");
        glBindTexture(GL_TEXTURE_2D, tex[52]);
    defTexture("jambe_dessus_mia.png");
        glBindTexture(GL_TEXTURE_2D, tex[53]);
    defTexture("jambe_mia.png");
        glBindTexture(GL_TEXTURE_2D, tex[54]);
    defTexture("pied_mia.png");  
    glBindTexture(GL_TEXTURE_2D, tex[55]);
    defTexture("face_j.png");
    glBindTexture(GL_TEXTURE_2D, tex[56]);
    defTexture("face_arriere_j.png");
    glBindTexture(GL_TEXTURE_2D, tex[57]);
    defTexture("face_dessous_j.png");
    glBindTexture(GL_TEXTURE_2D, tex[58]);
    defTexture("face_dessus_j.png");
    glBindTexture(GL_TEXTURE_2D, tex[59]);
    defTexture("face_droit_j.png");
    glBindTexture(GL_TEXTURE_2D, tex[60]);
    defTexture("face_gauche_j.png");
    glBindTexture(GL_TEXTURE_2D, tex[61]);
    defTexture("corps_arriere_j.png");
    glBindTexture(GL_TEXTURE_2D, tex[62]);
    defTexture("corps_j.png");
    glBindTexture(GL_TEXTURE_2D, tex[63]);
    defTexture("corps_cote_j.png");
    glBindTexture(GL_TEXTURE_2D, tex[64]);
    defTexture("corps_haut_j.png");
    glBindTexture(GL_TEXTURE_2D, tex[65]);
    defTexture("corps_bas_j.png");
        glBindTexture(GL_TEXTURE_2D, tex[66]);
    defTexture("bras_j.png");
        glBindTexture(GL_TEXTURE_2D, tex[67]);
    defTexture("main_j.png");
        glBindTexture(GL_TEXTURE_2D, tex[68]);
    defTexture("jambe_dessus_j.png");
        glBindTexture(GL_TEXTURE_2D, tex[69]);
    defTexture("jambe_j.png");
        glBindTexture(GL_TEXTURE_2D, tex[70]);
    defTexture("pied_j.png"); 
        glBindTexture(GL_TEXTURE_2D, tex[71]);
    defTexture("face_lb.png");
    glBindTexture(GL_TEXTURE_2D, tex[72]);
    defTexture("face_arriere_lb.png");
    glBindTexture(GL_TEXTURE_2D, tex[73]);
    defTexture("face_dessous_lb.png");
    glBindTexture(GL_TEXTURE_2D, tex[74]);
    defTexture("face_dessus_lb.png");
    glBindTexture(GL_TEXTURE_2D, tex[75]);
    defTexture("face_droit_lb.png");
    glBindTexture(GL_TEXTURE_2D, tex[76]);
    defTexture("face_gauche_lb.png");
    glBindTexture(GL_TEXTURE_2D, tex[77]);
    defTexture("corps_arriere_lb.png");
    glBindTexture(GL_TEXTURE_2D, tex[78]);
    defTexture("corps_lb.png");
    glBindTexture(GL_TEXTURE_2D, tex[79]);
    defTexture("corps_cote_lb.png");
    glBindTexture(GL_TEXTURE_2D, tex[80]);
    defTexture("corps_haut_lb.png");
    glBindTexture(GL_TEXTURE_2D, tex[81]);
    defTexture("corps_bas_lb.png");
        glBindTexture(GL_TEXTURE_2D, tex[82]);
    defTexture("bras_lb.png");
        glBindTexture(GL_TEXTURE_2D, tex[83]);
    defTexture("main_lb.png");
        glBindTexture(GL_TEXTURE_2D, tex[84]);
    defTexture("jambe_dessus_lb.png");
        glBindTexture(GL_TEXTURE_2D, tex[85]);
    defTexture("jambe_lb.png");
        glBindTexture(GL_TEXTURE_2D, tex[86]);
    defTexture("pied_lb.png"); 
            glBindTexture(GL_TEXTURE_2D, tex[87]);
    defTexture("face_yg.png");
    glBindTexture(GL_TEXTURE_2D, tex[88]);
    defTexture("face_arriere_yg.png");
    glBindTexture(GL_TEXTURE_2D, tex[89]);
    defTexture("face_dessous_yg.png");
    glBindTexture(GL_TEXTURE_2D, tex[90]);
    defTexture("face_dessus_yg.png");
    glBindTexture(GL_TEXTURE_2D, tex[91]);
    defTexture("face_droit_yg.png");
    glBindTexture(GL_TEXTURE_2D, tex[92]);
    defTexture("face_gauche_yg.png");
    glBindTexture(GL_TEXTURE_2D, tex[93]);
    defTexture("corps_arriere_yg.png");
    glBindTexture(GL_TEXTURE_2D, tex[94]);
    defTexture("corps_yg.png");
    glBindTexture(GL_TEXTURE_2D, tex[95]);
    defTexture("corps_cote_yg.png");
    glBindTexture(GL_TEXTURE_2D, tex[96]);
    defTexture("corps_haut_yg.png");
    glBindTexture(GL_TEXTURE_2D, tex[97]);
    defTexture("corps_bas_yg.png");
        glBindTexture(GL_TEXTURE_2D, tex[98]);
    defTexture("bras_yg.png");
        glBindTexture(GL_TEXTURE_2D, tex[99]);
    defTexture("main_yg.png");
        glBindTexture(GL_TEXTURE_2D, tex[100]);
    defTexture("jambe_dessus_yg.png");
        glBindTexture(GL_TEXTURE_2D, tex[101]);
    defTexture("jambe_yg.png");
        glBindTexture(GL_TEXTURE_2D, tex[102]);
    defTexture("pied_yg.png"); 
                
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
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

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
   
void creer_pave_2 (GLfloat centrex, GLfloat centrey, GLfloat centrez, GLfloat largeur,
                    GLfloat profondeur, GLfloat hauteur) {
              
	GLfloat cx = centrex;
	GLfloat cy = centrey;
	GLfloat cz = centrez;
	GLfloat h = hauteur / 2;
	GLfloat l = largeur / 2;
	GLfloat p = profondeur / 2; 

  // On dessine un carré sur le plan -z
  glBegin(GL_QUADS);
  glNormal3f(0, 0, -1);
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz - h); 
  glTexCoord2f(0., 1.); glVertex3f(cx - l, cy + p, cz - h); 
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz - h);
  glTexCoord2f(1., 0.); glVertex3f(cx + l, cy - p, cz - h);
  glEnd();
  // On dessine un carré sur le plan z
  glBegin(GL_QUADS);
  glNormal3f(0, 0, 1);
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz + h); 
  glTexCoord2f(0., 1.); glVertex3f(cx + l, cy - p, cz + h); 
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz + h);
  glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz + h);
  glEnd();
  //On dessine un carré sur le plan x
  glBegin(GL_QUADS);
  glNormal3f(1, 0, 0);
  glTexCoord2f(0., 0.); glVertex3f(cx + l, cy - p, cz + h); 
  glTexCoord2f(1., 0.); glVertex3f(cx + l, cy - p, cz - h); 
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz - h);
  glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz + h);
  glEnd();
 //On dessine un carré sur le plan -x
  glBegin(GL_QUADS);
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy + p, cz + h); 
  glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz - h); 
  glTexCoord2f(1., 1.); glVertex3f(cx - l, cy - p, cz - h);
  glTexCoord2f(0., 1.); glVertex3f(cx - l, cy - p, cz + h);
  glEnd();
  //On dessine un carré sur le plan y
  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);
  glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz + h); 
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz - h); 
  glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz - h);
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy + p, cz + h);
  glEnd();
  //On dessine un carré sur le plan -y
  glBegin(GL_QUADS);
  glNormal3f(0, -1, 0);
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz - h); 
  glTexCoord2f(0., 1.); glVertex3f(cx + l, cy - p, cz - h); 
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy - p, cz + h);
  glTexCoord2f(1., 0.); glVertex3f(cx - l, cy - p, cz + h);
  glEnd();                    
                        
                        
  
  
                        
  }
  
    
void creer_pave_with_texture (GLfloat centrex, GLfloat centrey, 
                            GLfloat centrez, GLfloat largeur,
                            GLfloat profondeur, GLfloat hauteur,
                           GLuint tex1, GLuint tex2, GLuint tex3, 
                           GLuint tex4, GLuint tex5, GLuint tex6) {
              
	GLfloat cx = centrex;
	GLfloat cy = centrey;
	GLfloat cz = centrez;
	GLfloat h = hauteur / 2;
	GLfloat l = largeur / 2;
	GLfloat p = profondeur / 2; 

  // On dessine un carré sur le plan -z
  glBindTexture(GL_TEXTURE_2D, tex1);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, -1);
  glTexCoord2f(0., 1.); glVertex3f(cx - l, cy - p, cz - h); 
  glTexCoord2f(1., 1.); glVertex3f(cx - l, cy + p, cz - h); 
  glTexCoord2f(1., 0.); glVertex3f(cx + l, cy + p, cz - h);
  glTexCoord2f(0., 0.); glVertex3f(cx + l, cy - p, cz - h);
  glEnd();
  // On dessine un carré sur le plan z
  glBindTexture(GL_TEXTURE_2D, tex2);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, 1);
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz + h); 
  glTexCoord2f(0., 1.); glVertex3f(cx + l, cy - p, cz + h); 
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz + h);
  glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz + h);
  glEnd();
  //On dessine un carré sur le plan x
  glBindTexture(GL_TEXTURE_2D, tex4);
  glBegin(GL_QUADS);
  glNormal3f(1, 0, 0);
  glTexCoord2f(1., 0.); glVertex3f(cx + l, cy - p, cz + h); 
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy - p, cz - h); 
  glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz - h);
  glTexCoord2f(0., 0.); glVertex3f(cx + l, cy + p, cz + h);
  glEnd();
 //On dessine un carré sur le plan -x
  glBindTexture(GL_TEXTURE_2D, tex3);
  glBegin(GL_QUADS);
  glNormal3f(-1, 0, 0);
  glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz + h); 
  glTexCoord2f(1., 1.); glVertex3f(cx - l, cy + p, cz - h); 
  glTexCoord2f(0., 1.); glVertex3f(cx - l, cy - p, cz - h);
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz + h);
  glEnd();
  //On dessine un carré sur le plan y
  glBindTexture(GL_TEXTURE_2D, tex6);
  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);
  glTexCoord2f(0., 0.); glVertex3f(cx + l, cy + p, cz + h); 
  glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz - h); 
  glTexCoord2f(1., 1.); glVertex3f(cx - l, cy + p, cz - h);
  glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz + h);
  glEnd();
  //On dessine un carré sur le plan -y
  glBindTexture(GL_TEXTURE_2D, tex5);
  glBegin(GL_QUADS);
  glNormal3f(0, -1, 0);
  glTexCoord2f(0., 1.); glVertex3f(cx - l, cy - p, cz - h); 
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy - p, cz - h); 
  glTexCoord2f(1., 0.); glVertex3f(cx + l, cy - p, cz + h);
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz + h);
  glEnd();                    
                        
                        
  
  
                        
  }
  
  
  void creer_murs (GLfloat centrex, GLfloat centrey, GLfloat centrez, GLfloat largeur,
                    GLfloat profondeur, GLfloat hauteur) {
              
	GLfloat cx = centrex;
	GLfloat cy = centrey;
	GLfloat cz = centrez;
	GLfloat h = hauteur / 2;
	GLfloat l = largeur / 2;
	GLfloat p = profondeur / 2; 



  //On dessine un carré sur le plan x
  glBegin(GL_QUADS);
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0., 0.); glVertex3f(cx + l, cy - p, cz + h);
  glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz + h); 
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz - h);
  glTexCoord2f(1., 0.); glVertex3f(cx + l, cy - p, cz - h);
  glEnd();
 //On dessine un carré sur le plan -x
  glBegin(GL_QUADS);
  glNormal3f(1, 0, 0);
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy + p, cz + h);
  glTexCoord2f(0., 1.); glVertex3f(cx - l, cy - p, cz + h); 
  glTexCoord2f(1., 1.); glVertex3f(cx - l, cy - p, cz - h);
  glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz - h); 
  glEnd();
  //On dessine un carré sur le plan y
  glBegin(GL_QUADS);
  glNormal3f(0, -1, 0);
  glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz + h); 
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy + p, cz + h);
  glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz - h);
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz - h);
  glEnd();
  //On dessine un carré sur le plan -y
  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);
  glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz - h); 
  glTexCoord2f(1., 0.); glVertex3f(cx - l, cy - p, cz + h);
  glTexCoord2f(1., 1.); glVertex3f(cx + l, cy - p, cz + h);
  glTexCoord2f(0., 1.); glVertex3f(cx + l, cy - p, cz - h);
  glEnd();                    
                        
                        
                  
                        
  
                        
  }
  
  void creer_witness_stand() {
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun);
      glBindTexture(GL_TEXTURE_2D, tex[1]);
      
      for (float c = 0.; c <= 1.1; c += 0.1) {
         float x = 100. * cos(3.14 * c);
         creer_pave_2(x, (sqrt(10000. - x * x) - 300.), 55., 10., 10., 110.);
      }

      
      for (int i = 110; i < 130; i++) {
      glPushMatrix();
      glTranslatef(0., -300., i);
      gluPartialDisk(quad, 90., 110., 20., 1., -93., 186.);   
      glPopMatrix();

      glPushMatrix();
      glTranslatef(0., -300., i);
      glRotatef(180.,0.,1.,0.);
      gluPartialDisk(quad, 90., 110., 20., 1., -93., 186.);   
      glPopMatrix();
      }
  
  
  }
  
    void creer_phoenix() { // centre de pw 250 100 90
        creer_pave_with_texture(230., 90., 40., 10., 10., 80., tex[22], tex[20], tex[21], tex[21], tex[21], tex[21]); //jg
        creer_pave_with_texture(230., 110., 40., 10., 10., 80., tex[22], tex[20], tex[21], tex[21], tex[21], tex[21]); //jd
        creer_pave_with_texture(230., 100., 120., 10., 40., 80., tex[17], tex[16], tex[14], tex[13], tex[15], tex[15]); //corps
        creer_pave_with_texture(230., 100., 170., 20., 20.,20., tex[9], tex[10], tex[7], tex[8], tex[12], tex[11]); //tete
        
        
        glPushMatrix();
        for (int i = 0; i < 50; i++) {
        glRotatef(i,0.,1.,0.);
        creer_pave_with_texture(230., 125., 120., 10., 10., 80., tex[19], tex[20], tex[18], tex[18], tex[18], tex[18]); // bd
        }
        glPopMatrix();
        
        
        creer_pave_with_texture(230., 75., 120., 10., 10., 80., tex[19], tex[20], tex[18], tex[18], tex[18], tex[18]);  //bg
    }
        void creer_mia() { // centre de pw 250 100 90
        creer_pave_with_texture(230., 190., 40., 10., 10., 80., tex[54], tex[52], tex[53], tex[53], tex[53], tex[53]); //jg
        creer_pave_with_texture(230., 210., 40., 10., 10., 80., tex[54], tex[52], tex[53], tex[53], tex[53], tex[53]); //jd
        creer_pave_with_texture(230., 200., 120., 10., 40., 80., tex[19], tex[48], tex[46], tex[45], tex[47], tex[47]); //corps
        creer_pave_with_texture(230., 200., 170., 20., 20.,20., tex[41], tex[42], tex[39], tex[40], tex[44], tex[43]); //tete
        creer_pave_with_texture(230., 225., 120., 10., 10., 80., tex[51], tex[52], tex[50], tex[50], tex[50], tex[50]); // bd
        creer_pave_with_texture(230., 175., 120., 10., 10., 80., tex[51], tex[52], tex[50], tex[50], tex[50], tex[50]);  //bg
    }
        void creer_winston() { // centre de pw 250 100 90
        creer_pave_with_texture(-230., 90., 40., 10., 10., 80., tex[38], tex[36], tex[37], tex[37], tex[37], tex[37]); //jg
        creer_pave_with_texture(-230., 110., 40., 10., 10., 80., tex[38], tex[36], tex[37], tex[37], tex[37], tex[37]); //jd
        creer_pave_with_texture(-230., 100., 120., 10., 40., 80., tex[33], tex[32], tex[29], tex[30], tex[31], tex[31]); //corps
        creer_pave_with_texture(-230., 100., 170., 20., 20.,20., tex[25], tex[26], tex[24], tex[23], tex[27], tex[28]); //tete
        creer_pave_with_texture(-230., 125., 120., 10., 10., 80., tex[35], tex[36], tex[34], tex[34], tex[34], tex[34]); // bd
        creer_pave_with_texture(-230., 75., 120., 10., 10., 80., tex[35], tex[36], tex[34], tex[34], tex[34], tex[34]);  //bg
    }
    
    void creer_juge() { // centre de juge 0., 700., 100.
        creer_pave_with_texture(-10., 680., 240., 10., 10., 80., tex[70], tex[68], tex[69], tex[69], tex[69], tex[69]); //jg
        creer_pave_with_texture(10., 680., 240., 10., 10., 80., tex[70], tex[68], tex[69], tex[69], tex[69], tex[69]); //jd
        creer_pave_with_texture(0., 680., 320., 40., 10., 80., tex[65], tex[64], tex[63], tex[63], tex[62], tex[61]); //corps
        creer_pave_with_texture(0., 680., 370., 20., 20.,20., tex[57], tex[58], tex[59], tex[60], tex[55], tex[56]); //tete
        creer_pave_with_texture(25., 680., 320., 10., 10., 80., tex[67], tex[68], tex[66], tex[66], tex[66], tex[66]); // bd
        creer_pave_with_texture(-25., 680., 320., 10., 10., 80., tex[67], tex[68], tex[66], tex[66], tex[66], tex[66]);  //bg
    }
    
        void creer_witness_1() { // centre de juge 0., 700., 100.
        creer_pave_with_texture(-10., -280., 40., 10., 10., 80., tex[86], tex[84], tex[85], tex[85], tex[85], tex[85]); //jg
        creer_pave_with_texture(10., -280., 40., 10., 10., 80., tex[86], tex[84], tex[85], tex[85], tex[85], tex[85]); //jd
        creer_pave_with_texture(0., -280., 120., 40., 10., 80., tex[81], tex[81], tex[79], tex[79], tex[77], tex[78]); //corps
        creer_pave_with_texture(0., -280., 170., 20., 20.,20., tex[73], tex[74], tex[75], tex[76], tex[72], tex[71]); //tete
        creer_pave_with_texture(25., -280., 120., 10., 10., 80., tex[83], tex[84], tex[82], tex[82], tex[82], tex[82]); // bd
        creer_pave_with_texture(-25., -280., 120., 10., 10., 80., tex[83], tex[84], tex[82], tex[82], tex[82], tex[82]);  //bg
    }
    
            void creer_witness_2() { // centre de juge 0., 700., 100.
        creer_pave_with_texture(-10., -280., 40., 10., 10., 80., tex[102], tex[100], tex[101], tex[101], tex[101], tex[101]); //jg
        creer_pave_with_texture(10., -280., 40., 10., 10., 80., tex[102], tex[100], tex[101], tex[101], tex[101], tex[101]); //jd
        creer_pave_with_texture(0., -280., 120., 40., 10., 80., tex[97], tex[96], tex[95], tex[95], tex[93], tex[94]); //corps
        creer_pave_with_texture(0., -280., 170., 20., 20.,20., tex[89], tex[90], tex[91], tex[92], tex[88], tex[87]); //tete
        creer_pave_with_texture(25., -280., 120., 10., 10., 80., tex[99], tex[100], tex[98], tex[98], tex[98], tex[98]); // bd
        creer_pave_with_texture(-25., -280., 120., 10., 10., 80., tex[99], tex[100], tex[98], tex[98], tex[98], tex[98]);  //bg
    }

void GL_Quit() {
  gluDeleteQuadric(quad);
}

