#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SCRIPT_PATH "scriptPR.txt"

   int traitementdialogue(char buf[]);
int main() {

	FILE *fic = fopen(SCRIPT_PATH, "r");
	char buf[BUFSIZ];
	
	while (fgets(buf, BUFSIZ, fic)) {
		int i = 0;
		
		/*if (buf[0] == '*' && buf[1] != '*') {
			while (buf[i+1] != '*') {
			printf("%c", buf[i+1]);
			i++;
		}
		}*/
		
		if (buf[0] == '-') {
			i = traitementdialogue(buf);

		}
		
		while (buf[i] != '\0') {
			printf("%c", buf[i]);
			i++;
		}
		
			
		
		
		
	}
	return EXIT_SUCCESS;
}

int traitementdialogue(char buf[]) {
	int i = 1;
	while (buf[i] != '\n') {
		printf("%c", buf[i]);
		i++;
	}
	printf(" dit :\n");
	return (i+1);
 }
