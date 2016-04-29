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




void *run() {
	FILE *fic = fopen(SCRIPT_PATH, "r");
	char buf[512];
	
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		if (buf[0] == '*') {
			char *tmp = strdup(buf);
			char *talking = extract_talking(tmp);
			printf("%s\n", talking);
			change_point_of_view(talking);
			getchar();
		} else if(strstr(buf, "[QCM]") != NULL) {
			char *tmp = strdup(buf);
			char* token = strtok(tmp, "->");
			token = strtok(NULL, "->");
			remove_newline(token);
			do_qcm(token);
		} else if(strstr(buf, "++") != NULL) {	
		
		} else {
			printf("%s\n", buf);
			getchar();
		}
		memset(buf, 512, sizeof(char));
	}
	fclose(fic);
	
	return NULL;
}
