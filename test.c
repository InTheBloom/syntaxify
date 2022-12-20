#include <stdio.h>
#include <stdlib.h>

int main(void) {
	unsigned char a0 = 130;
	unsigned char a1 = 160;
	printf("%c%c\n", a0, a1);
	printf("utf-8のマルチバイト文字をchcpコマンドで表示できるってマジ？\n");
	return 0;
}
