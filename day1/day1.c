#include <stdio.h>
#include <ctype.h>

int main (void) {
	FILE *fptr = fopen("d1in", "r");

	char line[1000] = {0};
	int sum = 0;
	int linecount = 0;
	while (fgets(line, 1000, fptr)) {
		linecount++;
		char num[2] = {'0', '0'};
		
		// any null values are initialized as a char with value 0, whereas any non-zero value is a valid character
		// so the first time we hit a non-zero is the first (last) index of the array

		for (int i = 0; i < 1000; i++) {
			if (isdigit(line[i])) {
				printf("line %d: leftwise num found at %d, as %c\n", linecount, i, line[i]);
				num[0] = line[i];
				break;	
			}
		}
		for (int i = 100; i >= 0; i--) {
			if (line[i] == 0) {
				//uninitialzed, break
				continue;
			} else if (line[i] >= '0' && line[i] <= '9') { // line[i] is digit?
				printf("line %d: rightwise num found at %d, as %c\n", linecount, i, line[i]);
				num[1] = line[i];
				break;
			}
		}
		printf("line: %s", line);
		printf("number: %c%c\n", num[0], num[1]);
		// the garbage truck as arrived
		for (int i = 0; i < 1000; i++) {
			line[i] = 0;
		}
		printf("---------------------------------\n");
		sum += (num[0] - '0') * 10 + (num[1] - '0');
	}
	printf("SUM IS: %d", sum);

	fclose(fptr);
	return 0;
}
