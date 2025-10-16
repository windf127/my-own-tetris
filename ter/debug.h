#pragma once
#include <stdio.h>
#include "ter.h"

void displayTer(ter N) {
	char temp[2][5];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			temp[i][j] = '-';
		}
		temp[i][4] = '\0';
	}
	for (int i = 0; i < 4; i++) {
		temp[N.block[i].y][N.block[i].x] = 'O';
	}
	for (int i = 1; i >= 0; i--) {
		puts(temp[i]);
	}
	putchar('\n');
}
void displayAllKindsOfTer() {
	for (int i = 0; i < 4; i++) {
		displayTer(T[i]);
	}
	for (int i = 0; i < 2; i++) {
		displayTer(I[i]);
	}
	displayTer(O);
	for (int i = 0; i < 2; i++) {
		displayTer(S[i]);
	}
	for (int i = 0; i < 2; i++) {
		displayTer(Z[i]);
	}
	for (int i = 0; i < 4; i++) {
		displayTer(L[i]);
	}
	for (int i = 0; i < 4; i++) {
		displayTer(J[i]);
	}
}
void displayField(char f[][10]) {
	for (int i = 19; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (f[i][j]) {
				putchar('O');
			}
			else {
				putchar('-');
			}
			putchar(' ');
		}
		printf("%02d\n", i);
	}
	printf("0 1 2 3 4 5 6 7 8 9\n");
}
char f_[25] = { 0 };
void compressField(char* f) {
	int now = 0;
	for (int i = 0; i < 25; i++) {
		f_[i] = 0;
		for (int j = 0; j < 8; j++) {
			f_[i] |= f[now] << j;
			now++;
		}
	}
}
void decompressField(char* fc, char* f) {
	int now = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 8; j++) {
			f[now] = fc[i] & (char)(1 << j);
			now++;
		}
	}
}
void saveGmaeData(char* holding, char* next, char* f, char* x, char* degree, ULL* score, ULL* maxscore, ULL* roundtimes) {
	compressField(f);
	FILE* fp = fopen("game_data.bin", "wb");
	fwrite(holding, sizeof(char), 1, fp);
	fwrite(next, sizeof(char), 1, fp);
	fwrite(f_, sizeof(char), 25, fp);
	fwrite(x, sizeof(char), 1, fp);
	fwrite(degree, sizeof(char), 1, fp);
	fwrite(score, sizeof(ULL), 1, fp);
	fwrite(maxscore, sizeof(ULL), 1, fp);
	fwrite(roundtimes, sizeof(ULL), 1, fp);
	fclose(fp);
	fp = fopen("game_data_backup.bin", "wb");
	fwrite(holding, sizeof(char), 1, fp);
	fwrite(next, sizeof(char), 1, fp);
	fwrite(f_, sizeof(char), 25, fp);
	fwrite(x, sizeof(char), 1, fp);
	fwrite(degree, sizeof(char), 1, fp);
	fwrite(score, sizeof(ULL), 1, fp);
	fwrite(maxscore, sizeof(ULL), 1, fp);
	fwrite(roundtimes, sizeof(ULL), 1, fp);
	fclose(fp);
}
void printGameData() {
	char holding, next, fc[25] = { 0 }, x, degree; ULL score;
	FILE* fp = fopen("game_data.bin", "rb");
	fread(&holding, 1, 1, fp);
	fread(&next, 1, 1, fp);
	fread(fc, 1, 25, fp);
	fread(&x, 1, 1, fp);
	fread(&degree, 1, 1, fp);
	fread(&score, 8, 1, fp);
	fclose(fp);
	char f[20][10] = { 0 };
	decompressField(fc, &f[0][0]);
	printf("%hhd %hhd\n", holding, next);
	displayField(f);
	printf("%hhd %hhd \n%llu\n", x, degree, score);
}
char load(char* holding, char* next, char* f, char* x, char* degree, ULL* score, ULL* maxscore, ULL* roundtimes) {
	FILE* fp = fopen("game_data.bin", "rb");
	if (feof(fp)) {
		fclose(fp);
		return 0;
	}
	char fc[25] = { 0 };
	fread(holding, 1, 1, fp);
	fread(next, 1, 1, fp);
	fread(fc, 1, 25, fp);
	fread(x, 1, 1, fp);
	fread(degree, 1, 1, fp);
	fread(score, 8, 1, fp);
	fread(maxscore, 8, 1, fp);
	fread(roundtimes, 8, 1, fp);
	fclose(fp);
	decompressField(fc, f);
	return 1;
}