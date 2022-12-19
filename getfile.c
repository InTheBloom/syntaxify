#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fp = NULL;

	if(argc >= 2) {
		fp = fopen(argv[1], "r");
	} else {
	}

	while(1) {
		unsigned char c = fgetc(fp);
		if((char)c == EOF) {
			break;
		} else if(c >= 240) { // utf-8 3バイト文字として扱う
			printf("multi byte character\n");
			unsigned char c2 = fgetc(fp);
			unsigned char c3 = fgetc(fp);
			unsigned char s[3];
			s[0] = c;
			s[1] = c2;
			s[2] = c3;
			printf("%s", s);
		} else {
			printf("%c", c);
		}
	}

	fclose(fp);

	return 0;
}
