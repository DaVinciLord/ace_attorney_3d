#include "script_read.h"

void *run() {
	
	load_evidences(&evidences);

	FILE *fic = fopen(SCRIPT_PATH, "r");
	char buf[512];
	
	while (fgets(buf, 512, fic)) {
		check_line(buf);
	}
	fclose(fic);
	
	return NULL;
}

void check_line(char *buf) {
	remove_newline(buf);
	char *tmp = strdup(buf);
	if (buf[0] == '*') {
		extract_talking(tmp);
		printf("%s", talking);
		change_point_of_view();
		getchar();
	} else if(strstr(buf, "[QCM]") != NULL) {
		char* token = strtok(tmp, "->");
		token = strtok(NULL, "->");
		remove_newline(token);
		do_qcm(atoi(token));
	} else if(strstr(buf, "++") != NULL) {	
		
	} else if (strstr(buf, "[PUBLIC_TALK]") != NULL) {
		sdlevent.key.keysym.sym = SDLK_o;
		SDL_PushEvent(&sdlevent);
		sdlevent.key.keysym.sym = SDLK_v;
		SDL_PushEvent(&sdlevent);
	} else if (strstr(buf, "[JUDGE_HAMMER]") != NULL) {
		talking = "Judge";
		change_point_of_view();
		strtok(tmp, "->");
		sdlevent.key.keysym.sym = SDLK_h;
		int n = atoi(strtok(NULL, "->"));
		for(int i = 0; i < n; i++) {
			SDL_PushEvent(&sdlevent);
		}
	} else if (strstr(buf, "[START_MUSIC_TRIAL]") != NULL) {
		sdlevent.key.keysym.sym = SDLK_l;
		SDL_PushEvent(&sdlevent);
	} else if (strstr(buf, "[STOP_MUSIC]") != NULL) {
		sdlevent.key.keysym.sym = SDLK_COLON;
		SDL_PushEvent(&sdlevent);
	} else if (strstr(buf, "[WITNESS]") != NULL) {
		strtok(tmp, "->");
		witness = atoi(strtok(NULL, "->"));
		sdlevent.key.keysym.sym = SDLK_COLON;
		SDL_PushEvent(&sdlevent);
		sdlevent.key.keysym.sym = SDLK_y;
		SDL_PushEvent(&sdlevent);
	} else if (strstr(buf, "[EVIDENCE]") != NULL) {
		strtok(tmp, "->");
		int evidence_nb = atoi(strtok(NULL, "->"));
		evidences.evidence_active[evidence_nb] = !evidences.evidence_active[evidence_nb];
	} else if (strstr(buf, "[TESTIMONY]") != NULL) {
		char* token = strtok(tmp, "->");
		token = strtok(NULL, "->");
		remove_newline(token);
		do_testimony(atoi(token));
	} else if (strstr(buf, "[CROSS_EXAM]") != NULL) {
		char* token = strtok(tmp, "->");
		token = strtok(NULL, "->");
		remove_newline(token);
		do_cross_exam(atoi(token), &evidences);
	} else if (strstr(buf, "[OBJECTION_MUSIC]") != NULL) {
		sdlevent.key.keysym.sym = SDLK_EXCLAIM;
		SDL_PushEvent(&sdlevent);
	} else if (strstr(buf, "[OBJECTION_STANCE]") != NULL) {
		sdlevent.key.keysym.sym = SDLK_w;
		SDL_PushEvent(&sdlevent);
	} else if (strstr(buf, "[END_OBJECTION_STANCE]") != NULL) {
		sdlevent.key.keysym.sym = SDLK_x;
		SDL_PushEvent(&sdlevent);
	} else if (strstr(buf, "[DESK_SLAM]") != NULL) {
		sdlevent.key.keysym.sym = SDLK_c;
		SDL_PushEvent(&sdlevent);
	} else if (strstr(tmp, "[HOLD_IT]") != NULL) {
			printf("\n");
			printf("HOLD IT!");
	} else if (strstr(buf, "[OBJECTION]") != NULL) {
		strtok(tmp, "->");
		objecting = strtok(NULL, "->");
		do_objection();
	} else if (strstr(buf, "[TAKE_THAT]") != NULL) {
		sdlevent.key.keysym.sym = SDLK_f;
		SDL_PushEvent(&sdlevent);
	} else if (strstr(buf, "[ALLEGRO]") != NULL) {
		allegro = 1;
	} else if (strstr(buf, "[CORNERED]") != NULL) {
		sdlevent.key.keysym.sym = SDLK_ASTERISK;
		SDL_PushEvent(&sdlevent);
	} else if (strstr(buf, "[PAUSE_MUSIC]") != NULL) {
		sdlevent.key.keysym.sym = SDLK_COMMA;
		SDL_PushEvent(&sdlevent);
	} else if(strstr(buf, "[CASE") != NULL || strstr(buf, "++") != NULL){ 
		
	} else {
		printf("%s", buf);
		getchar();
	}
	memset(buf, 512, sizeof(char));
}

void load_evidences(struct evidence *evidences) {
	FILE *fic = fopen(EVIDENCES_FILE, "r");
	char buf[512];
	
	int i = 0;
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		char *tmp = strdup(buf);
		evidences->evidence_name[i] = strtok(tmp, ">");
		evidences->evidence_type[i] = strtok(NULL, ">");
		evidences->evidence_other[i] = strtok(NULL, ">");
		evidences->evidence_description[i] = strtok(NULL, ">");
		char *token = strtok(NULL, ">");
		evidences->evidence_active[i] = atoi(token);
		memset(buf, 512, sizeof(char));
		i++;
	}
	evidences->nb_evidence = i;
	fclose(fic);
}


void extract_talking(char *buf) {
	talking = buf + 1;
}

void change_point_of_view() {
	if(strcmp(talking, "Judge") == 0) {
		sdlevent.key.keysym.sym = SDLK_u;
	} else if(strcmp(talking, "Payne") == 0) {
		sdlevent.key.keysym.sym = SDLK_i;
	} else if (strcmp(talking, "Phoenix") == 0) {
		sdlevent.key.keysym.sym = SDLK_p;
	} else if (strcmp(talking, "Mia") == 0) {
		sdlevent.key.keysym.sym = SDLK_m;
	} else if (strcmp(talking, "Butz") == 0 || strcmp(talking, "Sahwit") == 0){
		sdlevent.key.keysym.sym = SDLK_y;
	}
	SDL_PushEvent(&sdlevent);
}

void do_qcm(int qcm_nb) {
	
	struct qcm_struct qcm;
	get_info_qcm(&qcm, qcm_nb);

	int choice;
	char choice2[10];
	int good_answer = 0;
	do {
		choice = do_question_menu(qcm.talking, qcm.question, qcm.proposition_case, qcm.nb_proposition);
		do_answer(qcm_nb, choice - 1, qcm.case_files);
		printf("\n");
		snprintf(choice2, strlen(qcm.answer[0]) + 1, "CASE_%d", choice);
		printf("\n");
		int i = 0;
		while(qcm.answer[i] != NULL) {
			if(strcmp(choice2, qcm.answer[i]) == 0) {
				good_answer = 1;
				break;
			}
			i++;
		}
	} while(good_answer == 0);
}

void get_info_qcm(struct qcm_struct *qcm, int qcm_nb) {
	char qcm_file[30];
	int nb_digits = floor(log10(abs(qcm_nb))) + 1;
	snprintf(qcm_file, strlen(QCM_PATH) + nb_digits + strlen("/qcm/") + nb_digits + strlen(".txt") + 1, "%s%d/qcm%d.txt", QCM_PATH, qcm_nb, qcm_nb);
	
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
				if(strstr(tmp, "&") != NULL) {
					int i = 0;
					char *token = strtok(tmp, "&");
					qcm->answer[i] = token;
					i++;
					while(token != NULL) {
						token = strtok(NULL, "&");
						qcm->answer[i] = token;
						i++;
					}
				} else {
					qcm->answer[0] = tmp;
				}
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
	fclose(fic);
	
}

int do_question_menu(char *talking, char *question, struct key_value *proposition_case, int nb_proposition) {
	printf("%s", talking + 1);
	getchar();
	if(strstr(question, "_") != NULL) {
		char *tmp = strdup(question);
		printf("%s", strtok(tmp, "_"));
		getchar();
		printf("%s\n", strtok(NULL, "_"));
	} else {
		printf("%s\n", question);
	}
	getchar();
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

void do_answer(int qcm_nb, int choice, char **case_files) {
	printf("\n");
	char case_path[40];
	int nb_digits = floor(log10(abs(qcm_nb))) + 1;
	snprintf(case_path, strlen(QCM_PATH) + nb_digits + strlen(case_files[choice]) + 2, "%s%d/%s", QCM_PATH, qcm_nb, case_files[choice]);
	FILE *fic = fopen(case_path, "r");

	char buf[512];
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		check_line(buf);
	}
	fclose(fic);
}

void do_slam() {
	if(strcmp(slamming, "Phoenix Wright") == 0) {
		sdlevent.key.keysym.sym = SDLK_c;
	}
	SDL_PushEvent(&sdlevent);
}

void do_objection() {
	if(strcmp(objecting, "Payne") == 0) {
		sdlevent.key.keysym.sym = SDLK_g;
	} else if (strcmp(objecting, "Phoenix") == 0) {
		sdlevent.key.keysym.sym = SDLK_n;
	}
	SDL_PushEvent(&sdlevent);
}

void do_testimony(int testimony_nb) {
	
	printf("\nWitness Testimony\n");
	char testimony_path[70];
	int nb_digits = floor(log10(abs(testimony_nb))) + 1;
	snprintf(testimony_path, strlen(TESTIMONY_PATH) + nb_digits + strlen(".txt") + 1, "%s%d.txt", TESTIMONY_PATH, testimony_nb);
	
	FILE *fic = fopen(testimony_path, "r");

	char buf[512];
	sdlevent.key.keysym.sym = SDLK_DOLLAR;
	SDL_PushEvent(&sdlevent);
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		check_line(buf);
		if(Mix_PlayingMusic() == 0) {
			sdlevent.key.keysym.sym = SDLK_SEMICOLON;
			SDL_PushEvent(&sdlevent);
		}
	}
	fclose(fic);
	
}

void do_cross_exam(int cross_exam_nb, struct evidence *evidences) {
	printf("\n");
	
	struct cross_exam_struct cross_exam_infos;
	get_cross_exam_info(&cross_exam_infos, cross_exam_nb);
	
	good_objection = 0;
	cross_exam_infos.current_line = 0;
	char *line;
	char *token;
	int choice;
	printf("CROSS EXAMINATION\n-- %s --\n", cross_exam_infos.name);
	sdlevent.key.keysym.sym = SDLK_DOLLAR;
	SDL_PushEvent(&sdlevent);
	getchar();
	if(allegro) {
		sdlevent.key.keysym.sym = SDLK_t;
	} else {
		sdlevent.key.keysym.sym = SDLK_SEMICOLON;	
	}
	SDL_PushEvent(&sdlevent);

	do {
		line = cross_exam_infos.lines[cross_exam_infos.current_line];
		token = strdup(line);
		token = strtok(token, "_");
		talking = token + 1;
		getchar();
		printf("%s", talking);
		change_point_of_view();
		getchar();

		while(token != NULL) {
			token = strtok(NULL, "_");
			if (token != NULL)  {
				printf("%s", token);
			}
			getchar();
		}
		
		choice = do_cross_exam_menu(&cross_exam_infos);
		
		switch(cross_exam_infos.current_line) {
			case 0:
				switch(choice) {
					case 1:
						cross_exam_infos.current_line++;
						printf("\n");
					break;
					case 2:
						do_hold_it(cross_exam_infos.current_line + 1, cross_exam_nb);
						cross_exam_infos.current_line++;
						printf("\n");
					break;
					case 3:
						printf("\n");
						choice = do_present_menu(evidences);
						if(choice != 0) {
							good_objection = objection_try(choice - 1 , &cross_exam_infos);
							objecting = "Phoenix";
							do_objection();
						}
						printf("\n");
					break;
				}
			break;
			
			default:
				switch(choice) {
					case 1:
						cross_exam_infos.current_line--;
						printf("\n");
					break;
					case 2:
						cross_exam_infos.current_line++;
						if(cross_exam_infos.current_line + 1 > cross_exam_infos.nb_lines) {
							do_extras(&cross_exam_infos);
						}
						printf("\n");
					break;
					case 3:
						do_hold_it(cross_exam_infos.current_line + 1, cross_exam_nb);
						cross_exam_infos.current_line++;
						if(cross_exam_infos.current_line + 1 > cross_exam_infos.nb_lines) {
							do_extras(&cross_exam_infos);
						}
						printf("\n");
					break;
					case 4:
						printf("\n");
						choice = do_present_menu(evidences);
						if(choice != 0) {
							good_objection = objection_try(choice - 1, &cross_exam_infos);
							objecting = "Phoenix";
							do_objection();
						}
						printf("\n");
					break;
				}
			break;
		}
		
	} while(good_objection == 0);	
}

void get_cross_exam_info(struct cross_exam_struct *cross_exam_infos, int cross_exam_nb) {
	char cross_exam_path[70];
	int nb_digits = floor(log10(abs(cross_exam_nb))) + 1;
	snprintf(cross_exam_path, strlen(CROSS_EXAM_PATH) + nb_digits + strlen("/cross_exam/") + nb_digits + strlen(".txt") + 1, "%s%d/cross_exam%d.txt", CROSS_EXAM_PATH, cross_exam_nb, cross_exam_nb);
	
	FILE *fic = fopen(cross_exam_path, "r");

	char buf[512];
	int i = 0;
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		char *tmp = strdup(buf);
		if (strstr(buf, "[NAME]") != NULL) {
			strtok(tmp, "->");
			cross_exam_infos->name = strtok(NULL, "->");
		} else if (strstr(buf, "[ANSWER]") != NULL) {
			if(strstr(tmp, "&") != NULL) {
					strtok(tmp, ">");
					int i = 0;
					char *token = strtok(NULL, "&");
					cross_exam_infos->answer_line[i] = token;
					i++;
					while(token != NULL) {
						token = strtok(NULL, "&");
						cross_exam_infos->answer_line[i] = token;
						i++;
					}
				} else {
					strtok(tmp, ">");
					cross_exam_infos->answer_line[0] = strtok(NULL, ">");
					cross_exam_infos->answer_line[1] = NULL;
				}
		} else if (strstr(buf, "[EVIDENCE]") != NULL) {
			strtok(tmp, "->");
			cross_exam_infos->evidence_to_show = atoi(strtok(NULL, "->"));
		} else if (strstr(buf, "[LINE") != NULL) {
			strtok(tmp, ">");
			cross_exam_infos->lines[i] = strtok(NULL, ">");
			i++;
		} else if (strstr(buf, "++") != NULL) {
			cross_exam_infos->nb_lines = i;
			i = 0;
		} else if (strstr(buf, "[EXTRA") != NULL) {
			strtok(tmp, ">");
			cross_exam_infos->extras[i] = strtok(NULL, ">");
			i++;
		} else if (strstr(buf, "__") != NULL) {
			cross_exam_infos->nb_extras = i;
			i = 0;
		}
	}
	fclose(fic);
}

int do_cross_exam_menu(struct cross_exam_struct *cross_exam_infos) {
	int nb_proposition;
	printf("=========================\n");
	switch(cross_exam_infos->current_line)  {
		case 0:
				nb_proposition = 3;
				printf("1) %s\n", "Next");
				printf("2) %s\n", "Press");
				printf("3) %s\n", "Present");
		break;
		default:
			nb_proposition = 4;
			printf("1) %s\n", "Previous");
			printf("2) %s\n", "Next");
			printf("3) %s\n", "Press");
			printf("4) %s\n", "Present");
		break;
	}
	
	printf("=========================\n");
	int choice;
	do {
		printf("Make your choice : ");
		fscanf(stdin, "%d", &choice);
	} while(choice < 1 || choice > nb_proposition);
	
	printf("\n");
	return choice;
}

void do_hold_it(int hold_it_nb, int cross_exam_nb) {
	sdlevent.key.keysym.sym = SDLK_r;
	SDL_PushEvent(&sdlevent);
	char hold_it_path[70];
	int nb_digits_1 = floor(log10(abs(hold_it_nb))) + 1;
	int nb_digits_2 = floor(log10(abs(cross_exam_nb))) + 1;
	snprintf(hold_it_path, strlen(CROSS_EXAM_PATH) + nb_digits_1 + strlen("/holdit/") + nb_digits_2 + strlen(".txt") + 1, "%s%d/holdit%d.txt", CROSS_EXAM_PATH, cross_exam_nb, hold_it_nb);
	FILE *fic = fopen(hold_it_path, "r");

	char buf[512];
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		check_line(buf);		
	}
	fclose(fic);
}

void do_extras(struct cross_exam_struct *cross_exam_infos) {
	char *extra;
	char *token;
	for (int i = 0; i < cross_exam_infos->nb_extras; i++) {
		extra = cross_exam_infos->extras[i];
		token = strdup(extra);
		token = strtok(token, "_");
		talking = token + 1;
		getchar();
		printf("%s", talking);
		getchar();
		while(token != NULL) {
			token = strtok(NULL, "_");
			if (token != NULL)  {
				printf("%s", token);
			}
			getchar();
		}
	}
	cross_exam_infos->current_line = 0;
}

int do_present_menu(struct evidence *evidences) {
	printf("=========================\n");
	printf("0) Cancel\n");
	for(int i = 0; i < evidences->nb_evidence; i++) {
		printf("%d) %s\n", i + 1, evidences->evidence_name[i]);
	}
	printf("=========================\n");
	int choice;
	do {
		printf("Select evidence : ");
		fscanf(stdin, "%d", &choice);
	} while(choice < 1 || choice > evidences->nb_evidence);
	
	
	return choice;
}

int objection_try(int choice, struct cross_exam_struct *cross_exam_infos) {
	char try_answer[8];
	int nb_digits = floor(log10(abs(cross_exam_infos->current_line))) + 1;
	snprintf(try_answer, strlen("LINE_") + nb_digits + 1, "LINE_%d", cross_exam_infos->current_line + 1);
	int i = 0;
	while(cross_exam_infos->answer_line[i] != NULL) {
		printf("%s\t%s\n", try_answer, cross_exam_infos->answer_line[i]);
		if(strcmp(try_answer, cross_exam_infos->answer_line[i]) == 0 && choice == cross_exam_infos->evidence_to_show) {
			return 1;
		}
		i++;
	}
	return 0;
}

void remove_newline(char *line) {
	line[strcspn(line, "\r\n")] = 0;
}
