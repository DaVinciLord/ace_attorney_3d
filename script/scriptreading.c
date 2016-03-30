#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SCRIPT_PATH "scriptPR.txt"

int traitementdialogue(char buf[]);
int main() {

	FILE *fic = fopen(SCRIPT_PATH, "r");
	char *buf = malloc(512 * sizeof(char));
	
	while (fgets(buf, 512, fic)) {
		
		printf("%s", buf);
		memset(buf, 512, sizeof(char));
		
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
