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

static Mix_Music *musique;
static Mix_Music *musique_trial;
static Mix_Music *musique_objection;
static Mix_Music *musique_cornered;
static Mix_Music *musique_moderate;
static Mix_Music *musique_allegro;
static Mix_Music *musique_foule;
static Mix_Music *musique_marteau;
static Mix_Music *musique_examination;

static Mix_Chunk *chunk;
static Mix_Chunk *musique_holdit;
static Mix_Chunk *musique_takethat;
static Mix_Chunk *musique_slam;
static Mix_Chunk *musique_payne;
static Mix_Chunk *musique_phoenix;

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
void lookwitness(void);

// Quit functions
void quit_all(void);
void GL_Quit(void);


// Partie script
typedef void *(*start_routine_type)(void *);
void *run(void);

#define SCRIPT_PATH "./text_files/script_works_until_here.txt"
#define QCM_PATH "./text_files/qcms/qcm"
#define	TESTIMONY_PATH "./text_files/testimonies/testimony"
#define	CROSS_EXAM_PATH "./text_files/cross_exams/cross_exam"
#define EVIDENCES_FILE "./text_files/evidences.txt"

static char *talking;
static char *slamming;
static char *objecting;
static int witness;
static int good_objection;
static int allegro;

struct key_value {
	char *key;
	char *value;
};

struct qcm_struct {
	char *talking;
	char *question;
	char *answer[5];
	int nb_proposition;
	struct key_value proposition_case[5];
	char *case_files[5];
};

struct evidence {
	char *evidence_name[30];
	char *evidence_type[30];
	char *evidence_other[30];
	char *evidence_description[30];
	int evidence_active[30];
	int nb_evidence;
};

struct cross_exam_struct {
	char *answer_line[15];
	int evidence_to_show;
	char *lines[20];
	char *extras[20];
	char *name;
	int current_line;
	int nb_lines;
	int nb_extras;
};

void extract_talking(char *buf);
void change_point_of_view();
void get_info_qcm(struct qcm_struct *qcm, int qcm_nb);
void do_qcm(int qcm_nb);
int do_question_menu(char *talking, char *question, struct key_value *proposition_case, int nb_proposition);
void do_answer(int qcm_nb, int choice, char **case_files);
void remove_newline(char *line);
void load_evidences(struct evidence *evidences);
void do_testimony(int testimony_nb);
void do_cross_exam(int cross_exam_nb, struct evidence *evidences);
void get_cross_exam_info(struct cross_exam_struct *cross_exam_infos, int cross_exam_nb);
int do_cross_exam_menu(struct cross_exam_struct *cross_exam_infos);
void do_hold_it(int hold_it_nb, int cross_exam_nb);
void do_extras(struct cross_exam_struct *cross_exam_infos);
int do_present_menu(struct evidence *evidences);
int objection_try(int choice, struct cross_exam_struct *cross_exam_infos);
void do_slam();
void do_objection();

#endif // COURTROOM_H_
