#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fp = NULL;
	FILE *wr = NULL;

	if(argc >= 2) { // 引数から指定されたファイルを読み込む
		fp = fopen(argv[1], "r");
		if(fp == NULL) {
			printf("file not exist!\n");
			return 0;
		}
	} else {
		printf("specify a file!\n");
		return 0;
	}

	int wordlen = 0;
	for(; ; wordlen++) { // ファイル名の長さを調べる(このループを抜けたときのargv[1][wordlen]に終端文字が入る)
		if(argv[1][wordlen] == '\0') {
			break;
		}
	}

	char *nf = (char *)malloc((wordlen + 5) * sizeof(char)); // 終端文字分 + .newをつける
	nf[0] = '.';
	nf[1] = 'n';
	nf[2] = 'e';
	nf[3] = 'w';
	for(int i = 0; wordlen + 1 > i; i++) {
		nf[4 + i] = argv[1][i];
	}

	wr = fopen(nf, "w");
	if(wr == NULL) { // ファイルを作成できたかどうか判定
		printf("don't include '\\' in file name!\n");
		exit(EXIT_FAILURE);
	} else {
		printf("file opened\n");
	}

	free(nf); // 新規ファイル名に使ったポインタは開放しておく
	nf = NULL;

	while(1) { // 注意: バイナリファイルに関してはまともに動きません。
		unsigned char c = fgetc(fp);
		if((char)c == EOF) {
			break;
		} else if(c >= 240) { // utf-8 3バイト文字として扱う(イレギュラーな奴には対応できません)
			printf("multi byte character\n");
			unsigned char c2 = fgetc(fp);
			unsigned char c3 = fgetc(fp);
			fprintf(wr, "%c%c%c", c, c2, c3);
		} else {
			fprintf(wr, "%c", c);
		}
	}

	fclose(fp);
	fclose(wr);
	printf("successed!\n");

	return 0;
}
