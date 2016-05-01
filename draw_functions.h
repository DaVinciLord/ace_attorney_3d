#ifndef DRAW_FUNCTIONS_H_
#define DRAW_FUNCTIONS_H_

#include "globals.h"
#include "constants.h"

// Draw functions
void display(void);

void creer_marteau(const GLfloat matOr[]);
void draw_support(const GLfloat matOr[]);
void creer_phoenix(void);
void creer_winston(void);
void creer_mia(void);
void creer_juge(void);
void creer_witness_1(void);
void creer_witness_2(void);
void creer_public(void);
void creer_arcade(const GLfloat matBrun[], const GLfloat matBeigeClair[]);
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
void creer_witness_stand(const GLfloat matBrun[]);

#endif // DRAW_FUNCTIONS_H_
