#include <stdio.h>

#define MAX_SIZE 1000


int rmChar (char *ptr, int idx) {
	for (int i = idx; i < MAX_SIZE - 1; i++) {
		*(ptr+i) = *(ptr+i+1);
	}
	return 0;
}
int wordChecker (char *ptr, int idx) {
	char red[3] = {'r', 'e', 'd'};
	char blue[4] = {'b', 'l', 'u', 'e'};
	char green[5] = {'g', 'r', 'e', 'e', 'n'};
	if (*(ptr+idx) == red[0] && *(ptr+idx+1) == red[1] && *(ptr+idx+2) == red[2]) {
		return 1;
		//case: word found at idx "red"
	}
	else if (*(ptr+idx) == blue[0] && *(ptr+idx+1) == blue[1] && *(ptr+idx+2) == blue[2] && *(ptr+idx+3) == blue[3]) {
		return 2;
		//case: word found at idx "blue"
	}
	else if (*(ptr+idx) == green[0] && *(ptr+idx+1) == green[1] && *(ptr+idx+2) == green[2] && *(ptr+idx+3) == green[3] && *(ptr+idx+4) == green[4]) {
		return 3;
		//case: word found at idx "green"
	}
	return 0;
	//case: no word found at idx
}
int main (void) {
	FILE *fptr = fopen("d2in", "r");
	char line[MAX_SIZE] = {0};
	int rmax = 12;
	int gmax = 13;
	int bmax = 14;
	int sum = 0;
	int id = 0;
	int p2s = 0;
	while (fgets(line, MAX_SIZE, fptr)) {
		int flag = 1;
		int p2r = 0;
		int p2g = 0;
		int p2b = 0;
		id++;
		printf("%s\n", line);
		while (line[0] != ':') { // 58 = ":"
			rmChar(line, 0);
		}
		rmChar(line, 0); // remove everything before the colon
		for (int i = 0; i < MAX_SIZE; i++) {
			if (line[i] == 0) break; // newline, can stop reading in the line
						 // this WAS 10, but a sentinel value is needed
						 // at the end so we can stop reading, so leave
						 // the newline indicator in the line for a break at the bottom while loop :3
			if (line[i] == 32) rmChar(line, i); // remove spaces, we dont need those
			int num[5] = {0};
			if (wordChecker(line, i) != 0) {
				// this index is a word, so all previous indices should be numbers
				for (int j = 0; j < 5; j++) {
					num[j] = 0;
				}
				int digCount = 0;
				for (int j = 0; j < 5; j++) { // surely theres no numbers above 5 digits right
					if (line[j] == ' ') {
						rmChar(line, j);
						i--;
					}
					if (line[j] >= '0' && line[j] <= '9') {

						num[j] = line[j] - '0';
						printf("%d", num[j]);
						digCount++;
					} else break;
				}
				int numComp = 0;
				if (digCount == 1) {
					numComp = num[0];
				} else if (digCount == 2) {
					numComp = num[0] * 10 + num[1];
				} else printf("oh shit oh god oh fuck\n");
				switch (wordChecker(line, i)) {
					case 1:
						if (numComp > p2r) {
							p2r = numComp;
						}
						if (numComp > rmax) {
							//invalid game, throw the whole game out
							printf("Invalid game%s", line);
							flag = 0;
						}
						break;
					case 2:
						if (numComp > p2b) {
							p2b = numComp;
						}
						if (numComp > bmax) {
							//invalid game, throw the whole game out
							printf("Invalid game: %s", line);
							flag = 0;
						}
						break;
					case 3:
						if (numComp > p2g) {
							p2g = numComp;
						}
						if (numComp > gmax) {
							//invalid game, throw the whole game out
							printf("Invalid game: %s", line);
							flag = 0;
						}
						break;
					default:
						//how did we get here?
						break;
				} // end switch
				printf("value: %d, color: %d\n", numComp, wordChecker(line, i));
				while (line[0] != ';' || line[0] != ',') {
					if (line[0] == 10) {
						i = 1000;
						break;
					} else if (line[0] == ';') {
						break;
					} else if (line[0] == ',') {
						break;
					}
					printf("removing character: %c\n", line[0]);
					rmChar(line, 0);
				}
				printf("sentinel detected, continuing:\n");
				rmChar(line, 0);
				if (i != 1000)
					i = 0;
			} // end word logic
		}
		if (flag) {
			printf("Game %d: success!\n", id);
			sum += id;
		} else {
			printf("Game %d: failed\n", id);
		}
		p2s += p2r * p2b * p2g;
		printf("part 2 sum: %d, %d, %d", p2r, p2b, p2g);
		printf("\n%s", line);
		printf("\n\n");
		for (int i = 0; i < MAX_SIZE; i++) {
			line[i] = 0;
		}
	}
	printf("%d\n", sum);
	printf("part 2: %d\n", p2s);

	return 0;
}
