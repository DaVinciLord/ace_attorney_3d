#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "courtroom.h"

#define SCRIPT_PATH "./text_files/testScript.txt"
#define QCM_PATH "./text_files/qcms/qcm"
#define FAIL_FILE "fail.txt"
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
	char fail_file[45];
};
char *extract_talking(char *buf);
void change_point_of_view(char *talking);
void get_info_qcm(struct qcm_struct *qcm, char *qcm_nb);
void do_qcm(char *qcm_nb);
int do_question_menu(char *talking, char *question, struct key_value *proposition_case, int nb_proposition);
void do_answer(char *qcm_nb, int choice, char **case_files);
void do_fail(char *fail_file);
void remove_newline(char *line);

int main() {

	FILE *fic = fopen(SCRIPT_PATH, "r");
	char buf[512];
	
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		if (buf[0] == '*') {
			char *tmp = strdup(buf);
			extract_talking(tmp);
			change_point_of_view(tmp);
			printf("%s", buf);
			getchar();
		} else if(strstr(buf, "[QCM]") != NULL) {
			char *tmp = strdup(buf);
			char* token = strtok(tmp, "->");
			token = strtok(NULL, "->");
			remove_newline(token);
			do_qcm(token);
		} else if(strstr(buf, "++") != NULL) {	
		
		} else {
			printf("%s", buf);
			getchar();
		}
		memset(buf, 512, sizeof(char));
	}
	fclose(fic);
	return EXIT_SUCCESS;
}

char *extract_talking(char *buf) {
	char *talking = strtok(buf, "*");
	talking = strtok(NULL, "*");
	return talking;
}

void change_point_of_view(char *talking) {
	if(strcmp(talking, "Judge") == 0) {
		lookfromjudge();
	}
}


void do_qcm(char *qcm_nb) {
	
	struct qcm_struct qcm;
	get_info_qcm(&qcm, qcm_nb);
	
	int choice;
	char choice2[10];
	do {
		choice = do_question_menu(qcm.talking, qcm.question, qcm.proposition_case, qcm.nb_proposition);
		do_answer(qcm_nb, choice - 1, qcm.case_files);
		printf("\n");
		snprintf(choice2, strlen(qcm.answer) + 1, "CASE_%d", choice);
		if(strcmp(choice2, qcm.answer) != 0) {
			do_fail(qcm.fail_file);
			printf("\n");
		}
	} while(strcmp(choice2, qcm.answer) != 0);
}

void get_info_qcm(struct qcm_struct *qcm, char *qcm_nb) {
	char qcm_file[30];
	snprintf(qcm_file, strlen(QCM_PATH) + strlen(qcm_nb) + strlen("/qcm/") + strlen(qcm_nb) + strlen(".txt") + 1, "%s%s/qcm%s.txt", QCM_PATH, qcm_nb, qcm_nb);
	
	char last_string[50];
	FILE *fic = fopen(qcm_file, "r");

	char buf[512];
	int n = 0;
	while (fgets(buf, 512, fic)) {
		if(strstr(buf, "[TALKING]") != NULL) {
			snprintf(last_string, sizeof("[TALKING]"), "%s", buf);
		} else if(strstr(buf, "[QUESTION]") != NULL) {
			snprintf(last_string, sizeof("[QUESTION]"), "%s", buf);
		} else if(strstr(buf, "[ANSWER]") != NULL) {
			snprintf(last_string, sizeof("[ANSWER]"), "%s", buf);
		} else if(strstr(buf, "[PROPOSITION]") != NULL) {
			snprintf(last_string, sizeof("[PROPOSITION]"), "%s", buf);
		} else if(strstr(buf, "__") != NULL) {
			snprintf(last_string, 1, "0");
		}
		else {
			char *tmp = strdup(buf);
			remove_newline(tmp);
			if(strstr(last_string, "[TALKING]") != NULL) {
				qcm->talking = tmp;
				snprintf(last_string, 1, "0");
			} else if(strstr(last_string, "[QUESTION]") != NULL) {
				qcm->question = tmp;
				snprintf(last_string, 1, "0");
			} else if(strstr(last_string, "[ANSWER]") != NULL) {
				qcm->answer = tmp;
				snprintf(last_string, 1, "0");
			} else if(strstr(last_string, "[PROPOSITION]") != NULL) {
				qcm->proposition_case[n].key = strtok(tmp, "->");
				qcm->proposition_case[n].value = strtok(NULL, "->");
				char *file = strtok(NULL, "->");
				remove_newline(file);
				qcm->case_files[n] = file;
				n++;
			}
		}		
		memset(buf, 512, sizeof(char));
	}

	qcm->nb_proposition = n;
	snprintf(qcm->fail_file, 2 + strlen(QCM_PATH)+  strlen(qcm_nb) + strlen(FAIL_FILE), "%s%s/%s", QCM_PATH, qcm_nb, FAIL_FILE);
	fclose(fic);
	
}

int do_question_menu(char *talking, char *question, struct key_value *proposition_case, int nb_proposition) {
	printf("%s\n", talking);
	char *tmp = strdup(question);
	printf("%s\n", strtok(tmp, "_"));
	printf("%s\n", strtok(NULL, "_"));
	
	printf("=========================\n");
	for(int i = 0; i < nb_proposition; i++) {
		printf("%d) %s\n", i + 1, proposition_case[i].value);
	}
	printf("=========================\n");
	int choice;
	do {
		printf("Make your choice : ");
		fscanf(stdin, "%d", &choice);
	} while(choice < 1 || choice > nb_proposition);
	
	
	return choice;
}

void do_answer(char *qcm_nb, int choice, char **case_files) {
	char case_path[40];
	snprintf(case_path, strlen(QCM_PATH) + strlen(qcm_nb) + strlen(case_files[choice]) + 2, "%s%s/%s", QCM_PATH, qcm_nb, case_files[choice]);
	FILE *fic = fopen(case_path, "r");

	char buf[512];
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		printf("%s\n", buf);
	}
	
	fclose(fic);
}

void do_fail(char *fail_file) {
	FILE *fic = fopen(fail_file, "r");

	char buf[512];

	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		printf("%s\n", buf);
	}
	
	fclose(fic);
}

void remove_newline(char *line) {
	line[strcspn(line, "\r\n")] = 0;
}
