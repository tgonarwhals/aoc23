#include <stdio.h>

#define MAX_SIZE 141

int main (void) {
	char line[MAX_SIZE] = {0};
	char mtx[MAX_SIZE][MAX_SIZE];
	//       row       column
	FILE *fptr = fopen("d3in", "r");
	int lnct = 0;
	while (fgets(line, MAX_SIZE, fptr) && lnct <= MAX_SIZE - 1) {
		for (int i = 0; i < MAX_SIZE; i++) {
			mtx[lnct][i] = line[i];
		}
		lnct++;
	}
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			if (mtx[i][j] == 10) break;
			printf("%c", mtx[i][j]);
		}
		printf("\n");
	}
	fclose(fptr);	
	return 0;
}
