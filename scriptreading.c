#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SCRIPT_PATH "scriptPR.txt"


int main() {

	FILE *fic = fopen(SCRIPT_PATH, "r");
	char buf[BUFSIZ];
	
	while (fgets(buf, BUFSIZ, fic)) {
		int i = 1;
		if (buf[0] == '-') {
			while (buf[i] != ' ') {
				printf("%c", buf[i]);
				i++;
			}
			printf(" dit :");
		}
		while (buf[i] != '\n') {
			printf("%c", buf[i]);
			i++;
		}
		
			
		
		printf("%s", buf);
		
	}
	return EXIT_SUCCESS;
}
