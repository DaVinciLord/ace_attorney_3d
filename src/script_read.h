#ifndef SCRIPT_READ_H_
#define SCRIPT_READ_H_

#include "globals.h"
#include "constants.h"
#include "structures.h"

// Partie script
typedef void *(*start_routine_type)(void *);
void *run(void);

void check_line(char *buf);
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

#endif // SCRIPT_READ_H_
