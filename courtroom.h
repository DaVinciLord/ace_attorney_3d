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

// Partie Graphique

// Global variables
static SDL_Window *fenetre;
static SDL_GLContext context;
static GLuint tex[122];
static GLUquadric * quad;

static GLfloat whereiamx;
static GLfloat whereiamy;
static GLfloat whereiamz;

static GLfloat whereilookx;
static GLfloat whereilooky;
static GLfloat whereilookz;

static GLdouble near;
static GLdouble far;
static int lock;
static int deskslaming;
static int noding;
static int langledubrasdephoenixwright;
static int mouvementmarteau;

static SDL_Event sdlevent;

// Constant varaibles
const GLfloat matSpeculaire[4] = {1., 1., 1., 1.};
const GLfloat matShininess = 50.;
const GLfloat matBeige[4] = {197./255.,167./255., 147./255., 1.};
const GLfloat matBrun[4] = {124./255., 64./255., 0., 1.};
const GLfloat matBrunClair[4] = {240./255., 140./255., 70./255., 1.};
const GLfloat matArgent[4] = {206./255., 206./255., 206./255., 1.};
const GLfloat matOr[4] = {1., 215./255., 0., 1.};
const GLfloat matBeigeClair[4] = {245./255., 245./255., 220/255., 1.};

// Init functions
void init(void);
void init_globals(void);
void init_SDL(void);
void init_GL(void);
void GL_Quit(void);
void printGLInfos(void);
void initTexture(void); 
void defTexture(const char * filename);
void creer_marteau();
void draw_support();
// Main functions
void game_loop(void);
int keyboard(SDL_Event * event);

// Draw functions
void display(void);
void creer_phoenix(void);
void creer_winston(void);
void creer_mia(void);
void creer_juge(void);
void creer_witness_1(void);
void creer_witness_2(void);
void creer_public(void);
void creer_arcade(void);
void sol(int x0, int y0, int x1, int y1);
void creer_pave_2 (float centrex, float centrey, float centrez, float hauteur,
                    float largeur, float profondeur);
void creer_murs (GLfloat centrex, GLfloat centrey, GLfloat centrez, GLfloat largeur,
                    GLfloat profondeur, GLfloat hauteur);
void creer_pave_with_texture (GLfloat centrex, GLfloat centrey, 
                            GLfloat centrez, GLfloat largeur,
                            GLfloat profondeur, GLfloat hauteur,
                           GLuint tex1, GLuint tex2, GLuint tex3, 
                           GLuint tex4, GLuint tex5, GLuint tex6);
void creer_witness_stand(void);

// Characters actions
void anim_bras_pw(int sens);
void desk_slaming_pw();
void public_noding();
void anim_marteau();

// Camera functions
void lookfromjudge(void);
void lookphoenix(void);
void lookpublic(void);
void lookpayne(void);
void look_mia_from_phoenix(void);
void lookjudge(void);

// Quit functions
void quit_all(void);
void GL_Quit(void);


// Partie script
typedef void *(*start_routine_type)(void *);
void *run(void);

#define SCRIPT_PATH "./text_files/testScript.txt"
#define QCM_PATH "./text_files/qcms/qcm"
#define FAIL_FILE "fail.txt"


static char *talking;

struct key_value {
	char *key;
	char *value;
};

struct qcm_struct {
	char *talking;
	char *question;
	char *answer;
	int nb_proposition;
	struct key_value proposition_case[5];
	char *case_files[5];
};
void extract_talking(char *buf);
void change_point_of_view();
void get_info_qcm(struct qcm_struct *qcm, char *qcm_nb);
void do_qcm(char *qcm_nb);
int do_question_menu(char *talking, char *question, struct key_value *proposition_case, int nb_proposition);
void do_answer(char *qcm_nb, int choice, char **case_files);
void remove_newline(char *line);


#endif // COURTROOM_H_
