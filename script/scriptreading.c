#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SCRIPT_PATH "testScript.txt"

struct key_value {
	char *key;
	char *value;
}
void do_qcm(char *qcm_nb);
int main() {

	FILE *fic = fopen(SCRIPT_PATH, "r");
	char buf[512];
	
	while (fgets(buf, 512, fic)) {
		if (buf[0] == '*') {
			printf("%s", buf);
		} else if(strstr(buf, "[QCM]") != NULL) {
			char *tmp = strdup(buf);
			char* token = strtok(tmp, "->");
			token = strtok(NULL, "->");
			do_qcm(token);
		} else if(strstr(buf, "++") != NULL) {	
		
		} else {
			printf("%s", buf);
		}
		memset(buf, 512, sizeof(char));
	}
	return EXIT_SUCCESS;
}

void do_qcm(char *qcm_nb) {
	char qcm_file[5];
	qcm_nb[strcspn(qcm_nb, "\r\n")] = 0;
	snprintf(qcm_file, strlen(qcm_nb) + strlen("QCM") + strlen(".txt") + 1, "QCM%s.txt", qcm_nb);

	char last_string[50];
	FILE *fic = fopen(qcm_file, "r");
	char buf[512];
	char question[512];
	char answer[25];
	
	struct prop_case pc[5];
	int n_prop_case = 0;
	while (fgets(buf, 512, fic)) {
		if(strstr(last_string, "[TALKING]") != NULL) {
			printf("%s", buf);
			snprintf(last_string, 1, "0");
		} else if(strstr(last_string, "[QUESTION]") != NULL) {
			snprintf(question, sizeof(buf), "%s", question);
			snprintf(last_string, 1, "0");
		} else if(strstr(last_string, "[ANSWER]") != NULL) {
			snprintf(answer, sizeof(buf), "%s", answer);
			snprintf(last_string, 1, "0");
		} else if(strstr(last_string, "[PROPOSITION]") != NULL) {
			char *tmp = strdup(buf);
			pc[n_prop_case].key = strtok(tmp, "->");
			pc[n_prop_case].value = strtok(NULL, "->");
		} else if(strstr(last_string, "[CASE]") != NULL) {
			printf("%s", buf);
		}
		else {
			if (buf[0] == '*') {
				printf("%s", buf);
			} else if(strstr(buf, "[TALKING]") != NULL) {
				snprintf(last_string, sizeof("[TALKING]"), "%s", buf);
			} else if(strstr(buf, "[QUESTION]") != NULL) {
				snprintf(last_string, sizeof("[QUESTION]"), "%s", buf);
			} else if(strstr(buf, "[ANSWER]") != NULL) {
				snprintf(last_string, sizeof("[ANSWER]"), "%s", buf);
			} else if(strstr(buf, "[PROPOSITION]") != NULL) {
				snprintf(last_string, sizeof("[PROPOSITION]"), "%s", buf);
			} else if(strstr(buf, "[CASE]") != NULL) {
				snprintf(last_string, sizeof(buf), "%s", buf);
			}
		}
		memset(buf, 512, sizeof(char));
	}
}
