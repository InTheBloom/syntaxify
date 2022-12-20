#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fp = NULL;
	FILE *wr = NULL;

	if(argc >= 2) { // 引数から指定されたファイルを読み込む
		fp = fopen(argv[1], "r");
		if(fp == NULL) {
			fprintf(stderr, "file not exist!\n");
			return 0;
		}
	} else {
		fprintf(stderr, "specify a file!\n");
		return 0;
	}

	int wordlen = 0;
	for(; ; wordlen++) { // ファイル名の長さを調べる(このループを抜けたときのargv[1][wordlen]に終端文字が入る)
		if(argv[1][wordlen] == '\0') {
			break;
		}
	}

	int delim = -1;
	for(int i = wordlen; 0 <= i; i--) { // ファイル区切りの記号が存在するかどうか後ろから調査する
		if(argv[1][i] == '\\' || argv[1][i] == '/') {
			delim = i;
			fprintf(stdout, "delim is %i\n", delim);
			break;
		}
	}

	char *nf = (char *)malloc((wordlen + 5) * sizeof(char)); // 終端文字分 + .newをつける
	if(delim != -1) { // もしファイル区切りの記号が存在するなら
		for(int i = 0; delim >= i; i++) {
			nf[i] = argv[1][i];
		}
		nf[delim + 1] = '.';
		nf[delim + 2] = 'n';
		nf[delim + 3] = 'e';
		nf[delim + 4] = 'w';
		for(int i = 0; wordlen + 1 > i; i++) {
			nf[delim + 5 + i] = argv[1][delim + 1 + i];
		}
	} else {
		nf[0] = '.';
		nf[1] = 'n';
		nf[2] = 'e';
		nf[3] = 'w';
		for(int i = 0; wordlen + 1 > i; i++) {
			nf[4 + i] = argv[1][i];
		}
	}

	wr = fopen(nf, "w");
	if(wr == NULL) { // ファイルを作成できたかどうか判定
		fprintf(stderr, "failed to make new file.\npress enter to close...\n");
		getchar();
		exit(EXIT_FAILURE);
	} else {
		fprintf(stdout, "file opened\n");
	}

	free(nf); // 新規ファイル名に使ったポインタは開放しておく
	nf = NULL;

	while(1) { // 注意: バイナリファイルに関してはまともに動きません。
		unsigned char c = fgetc(fp);
		if((char)c == EOF) { // EOFの定義が-1になっているのでcharにキャスト
			break;
		} else if(c >= 224) { // 3バイト文字
			unsigned char c2 = fgetc(fp);
			unsigned char c3 = fgetc(fp);
			fprintf(wr, "%c%c%c", c, c2, c3);
		} else if(c >= 240) { // 4バイト文字
			unsigned char c2 = fgetc(fp);
			unsigned char c3 = fgetc(fp);
			unsigned char c4 = fgetc(fp);
			fprintf(wr, "%c%c%c%c", c, c2, c3, c4);
		} else {
			fprintf(wr, "%c", c);
		}
	}

	fclose(fp);
	fclose(wr);
	fprintf(stdout, "successed!\npress enter to close...\n");
	getchar();

	return 0;
}
