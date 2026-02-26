// NOTE: Part 2 needs compiled with -fno-stack-protector flag, because some weird array things are happening. The array is big enough, I promise.

#include <stdio.h>
#include <ctype.h>

#define MAX_SIZE 1000

int partTwoCleaner (char *ptr) {
	// this is text that will help us later
	// one
	// two, three
	// four, five
	// six, seven
	// eight
	// nine
	// zero
	//
	// edge cases: 
	// oneight
	// twone
	// threeight
	// fiveight
	// sevenine
	// eightwo
	// eighthree
	for (int i = 0; i < MAX_SIZE; i++) {
		switch (*(ptr + i)) {
			case 'o':
				// 'o' 'n' 'e'
				if ( ( *(ptr+i) == 'o' )&&( *(ptr+i+1) == 'n' )&&( *(ptr+i+2) == 'e' ) ) {
					*(ptr+i) = '1';
					// this is an edge case! insert an 'e' at the end, to catch a potential e for an eight
					*(ptr+i+1) = 'e';
					//everything after this index needs to shift left by 2, for the 2 characters we removed
					for (int j = 1; j < MAX_SIZE - i; j++) {
						*(ptr + i + j + 1) = *(ptr + i + j + 2);
					}
				}
				break;
			case 't':
				// 't' 'w' 'o' or 't' 'h' 'r' 'e' 'e'
				if ( ( *(ptr+i) == 't' )&&( * (ptr+i+1) == 'w')&&( * (ptr+i+2) == 'o') ) {
					*(ptr+i) = '2';
					// edge case: twone
					*(ptr+i+1) = 'o';
					for (int j = 1; j < MAX_SIZE - i; j++) {
						*(ptr+i+j+1) = *(ptr+i+j+2);
					}
				} else
					
				if ( ( *(ptr + i) == 't')&&(*(ptr+i+1)=='h')&&(*(ptr+i+2)=='r')&&(*(ptr+i+3)=='e')&&(*(ptr+i+4)=='e')) {
					*(ptr+i) = '3';
					//edge case: threeight
					*(ptr+i+1) = 'e';
					for (int j = 1; j < MAX_SIZE - i; j++) {
						*(ptr+i+j+1) = *(ptr+i+j+4);
					}
				}
				break;
			case 'f':
				// 'f' 'o' 'u' 'r' or 'f' 'i' 'v' 'e'
				if ((*(ptr+i)=='f')&&(*(ptr+i+1)=='o')&&(*(ptr+i+2)=='u')&&(*(ptr+i+3)=='r')){
					*(ptr+i)='4';
					for (int j = 1; j < MAX_SIZE - i; j++) {
						*(ptr+i+j) = *(ptr+i+j+3);
					} 
				} else
				if ((*(ptr+i)=='f')&&(*(ptr+i+1)=='i')&&(*(ptr+i+2)=='v')&&(*(ptr+i+3)=='e')) {
					*(ptr+i)='5';
					//edge case: fiveight
					*(ptr+i+1)='e';
					for (int j = 1; j < MAX_SIZE - i; j++) {
						*(ptr+i+j+1) = *(ptr+i+j+3);
					}
				}
				break;
			case 's':
				// 's' 'i' 'x' or 's' 'e' 'v' 'e' 'n'
				// lol
				if ((*(ptr+i)=='s')&&(*(ptr+i+1)=='i')&&(*(ptr+i+2))){
					*(ptr+i)='6';
					for (int j = 1; j < MAX_SIZE - i; j++) {
						*(ptr+i+j)=*(ptr+i+j+2);
					}
				} else
				if ((*(ptr+i)=='s')&&(*(ptr+i+1)=='e')&&(*(ptr+i+2)=='v')&&(*(ptr+i+3)=='e')&&(*(ptr+i+4)=='n')) {
					*(ptr+i)='7';
					//edge case: sevenine
					*(ptr+i+1)='n';
					for (int j = 1; j < MAX_SIZE - i; j++) {
						*(ptr+i+j)=*(ptr+i+j+4);
					}
				}
				break;
			case 'e':
				// 'e' 'i' 'g' 'h' 't'
				if((*(ptr+i)=='e')&&(*(ptr+i+1)=='i')&&(*(ptr+i+2)=='g')&&(*(ptr+i+3)=='h')&&(*(ptr+i+4)=='t')){
					*(ptr+i)='8';
					//edge case: eightwo, eighthree
					*(ptr+i+1)='t';
					for (int j = 1; j < MAX_SIZE - i; j++) {
						*(ptr+i+j+1)=*(ptr+i+j+4);
					}
				}
				break;
			case 'n':
				// 'n' 'i' 'n' 'e'
				if ((*(ptr+i)=='n')&&(*(ptr+i+1)=='i')&&(*(ptr+i+2)=='n')&&(*(ptr+i+3)=='e')){
					*(ptr+i)='9';
					//edge chase: nineight
					*(ptr+i+1)='e';
					for (int j = 1; j < MAX_SIZE - i; j++) {
						*(ptr+i+j+1)=*(ptr+i+j+3);
					}
				}
				break;
			case 'z':
				// 'z' 'e' 'r' 'o'
				if ((*(ptr+i)=='z')&&(*(ptr+i+1)=='e')&&(*(ptr+i+2)=='r')&&(*(ptr+i+3)=='o')){
					*(ptr+i)='0';
					for (int j = 1; j < MAX_SIZE - i; j++) {
						*(ptr+i+j)=*(ptr+i+j+3);
					}
				}
				break;
			default:
				//this means that no letters appear that need to be cleaned, so we can ignore whatever this idx is
				break;
		}
	}

	return 0;	
}	

int main (void) {
	FILE *fptr = fopen("d1in", "r");

	char line[MAX_SIZE] = {0};
	int sum = 0;
	int linecount = 0;
	while (fgets(line, MAX_SIZE, fptr)) {
		linecount++;
		char num[2] = {'0', '0'};
		
		// any null values are initialized as a char with value 0, whereas any non-zero value is a valid character
		// so the first time we hit a non-zero is the first (last) index of the array

		printf("line before: %s\n", line);
		partTwoCleaner(line);
		printf("line after: %s\n", line);

		for (int i = 0; i < MAX_SIZE; i++) {
			if (isdigit(line[i])) {
				printf("line %d: leftwise num found at %d, as %c\n", linecount, i, line[i]);
				num[0] = line[i];
				break;	
			}
		}
		for (int i = MAX_SIZE; i >= 0; i--) {
			if (line[i] == 0) {
				//uninitialzed, break
				continue;
			} else if (line[i] >= '0' && line[i] <= '9') { // line[i] is digit?
				printf("line %d: rightwise num found at %d, as %c\n", linecount, i, line[i]);
				num[1] = line[i];
				break;
			}
		}
		//printf("line: %s", line);
		//printf("number: %c%c\n", num[0], num[1]);
		// the garbage truck has arrived
		for (int i = 0; i < MAX_SIZE; i++) {
			line[i] = 0;
		}
		printf("---------------------------------\n");
		sum += (num[0] - '0') * 10 + (num[1] - '0');
	}
	printf("SUM IS: %d", sum);

	fclose(fptr);
	return 0;
}
