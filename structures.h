#ifndef STRUCTURES_H_
#define STRUCTURES_H_

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
#endif // STRUCTURES_H_
