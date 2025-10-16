#pragma once
#include "debug.h"
#include <stdlib.h>

// 记住输出的角度是0 1 2 3而不是0 90 180 270
void out(char* x, char* degree) {

	/*FILE* fp = fopen("decision.bin", "rb");
	fread(x, 1, 1, fp);
	fread(degree, 1, 1, fp);
	fclose(fp);*/

	//scanf("%hhd%hhd", x, degree);

	*x= rand() % 9 + 0;
	*degree= rand() % 3 + 0;
}

//void saveTrainData(char* holding, char* next, char f[][10], char* x, char* degree, int* score) {
//	compressField(&f[0][0]);
//	FILE* fp = fopen("train_data.bin", "ab");
//	fwrite(holding, sizeof(char), 1, fp);
//	fwrite(next, sizeof(char), 1, fp);
//	fwrite(f_, sizeof(char), 25, fp);
//	char top = gettop(&f[0][0]);
//	ter N=placeDown(f, rotate(*holding, (int)(*degree * 90)), (int)(*x));
//	char thisscore = addscore(score, clean(f));//0 1 3 5 8
//	if (!thisscore) {
//		if (gettop(&f[0][0]) - top > 0)thisscore = -1;
//		for (int i = 0; i < 4; i++) {
//			if (f[N.block[i].y - 1][N.block[i].x] == 0) { thisscore = -4; break; }
//		}
//	}
//	fwrite(x, sizeof(char), 1, fp);
//	fwrite(degree, sizeof(char), 1, fp);
//	fwrite(&thisscore, sizeof(char), 1, fp);
//	fclose(fp);
//}
void printASetOfTrainData(int n) {
	char holding, next, fc[25] = { 0 }, x, degree, thisscore;
	FILE* fp = fopen("train_data.bin", "rb");
	fseek(fp, 30 * n, SEEK_SET);
	fread(&holding, 1, 1, fp);
	fread(&next, 1, 1, fp);
	fread(fc, 1, 25, fp);
	fread(&x, 1, 1, fp);
	fread(&degree, 1, 1, fp);
	fread(&thisscore, 1, 1, fp);
	fclose(fp);
	char f[20][10] = { 0 };
	decompressField(fc, &f[0][0]);
	printf("%hhd %hhd\n", holding, next);
	displayField(f);
	printf("%hhd %hhd \n%hhd\n", x, degree, thisscore);
}
void svaeCurrent(char* holding, char* next, char f[][10]) {
	compressField(&f[0][0]);
	FILE* fp = fopen("current.bin", "wb");
	fwrite(holding, sizeof(char), 1, fp);
	fwrite(next, sizeof(char), 1, fp);
	fwrite(f_, sizeof(char), 25, fp);
	fclose(fp);
}