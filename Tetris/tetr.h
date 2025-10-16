#pragma once
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<stdio.h>
typedef struct point {
	int x;
	int y;
} point;
typedef struct ter {
	point block[4];
}ter;
#define TerT 1
#define TerI 2
#define TerO 3
#define TerS 4
#define TerZ 5
#define TerL 6
#define TerJ 7

#define GAMESTATE_MENU 0
#define GAMESTATE_PLAY 1
#define GAMESTATE_PAUSE 2

#define INITIAL_X 4
#define INITIAL_Y 20//均从0起始 
#define PIXEL_PER_BLOCK 30

#define NATRUAL_TIME_PER_DOWN 400
#define SOFT_TIME_PER_DOWN 50
#define ALLOWED_TIME 2000
#define MOVE_INTERVAL 40

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 960

typedef struct {
	char ex;
	char te;
}existence_and_texture;
existence_and_texture field[30][10] = { 0,0 };// 0 1 //1 2 3 4 5 6 7 8

unsigned long long score = 0;
short
downSpeed = NATRUAL_TIME_PER_DOWN,
holdingY;
char
gameState = GAMESTATE_MENU,
holding,//1 2 3 4 5 6 7
holdingDegree = 0,//顺 0 1 2 3
holdingX,//0 1 2 3 4 5 6 7 8 9
save = 0,//1 2 3 4 5 6 7 0
next[15] = { 0 },//1 2 3 4 5 6 7
bag[7] = { 1, 2, 3, 4, 5, 6, 7 };//用于7bag随机序列
void shuffle(long seed) {
	srand(seed);
	for (int i = 6; i > 0; i--) {
		int j = rand() % (i + 1);
		char tem = bag[i];
		bag[i] = bag[j];
		bag[j] = tem;
	}
}


ter T = { {{-1,0},{0,0},{1,0},{0,1} } };
ter I = { {{-1,0},{0,0},{1,0},{2,0} } };//
ter O = { {{0,0},{1,0},{0,1},{1,1} } };
ter S = { {{-1,0},{0,0},{0,1},{1,1} } };
ter Z = { {{0,0},{1,0},{-1,1},{0,1} } };
ter L = { {{-1,0},{0,0},{1,0},{1,1} } };
ter J = { {{-1,0},{0,0},{1,0},{-1,1} } };

ter holdingN;

ter num2ter(char n) {
	switch (n) {
	case TerT:return T;
	case TerI:return I;
	case TerO:return O;
	case TerS:return S;
	case TerZ:return Z;
	case TerL:return L;
	case TerJ:return J;
	}
}


void inherit() {
	holding = next[0];
	for (int i = 0; i < 14; i++) {
		next[i] = next[i + 1];
	}
}

void initialize() {
	save = 0;
	shuffle(time(NULL));
	for (int i = 0; i < 7; i++) {
		next[i] = bag[i];
	}
	shuffle(time(NULL));
	for (int i = 0; i < 7; i++) {
		next[i + 7] = bag[i];
	}
	inherit();
	holdingX = INITIAL_X;
	holdingY = INITIAL_Y;
	ter N = num2ter(holding);
	for (int i = 0; i < 4; i++) {
		holdingN.block[i].x = holdingX + N.block[i].x;
		holdingN.block[i].y = holdingY + N.block[i].y;
	}
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 10; j++) {
			field[i][j].ex = 0;
			field[i][j].te = 0;
		}
	}
	score = 0;
}

void spin90() {
	for (int i = 0; i < 4; i++) {
		holdingN.block[i].x -= holdingX;
		holdingN.block[i].y -= holdingY;
	}
	ter TEM = holdingN;
	for (int i = 0; i < 4; i++) {
		holdingN.block[i].x = TEM.block[i].y + holdingX;
		holdingN.block[i].y = -TEM.block[i].x + holdingY;
	}
}

void refillnext() {
	shuffle(time(NULL));
	for (int i = 0; i < 7; i++) {
		next[i + 6] = bag[i];
	}
}

char isleagal() {
	return holdingN.block[0].x <= 9
		&& holdingN.block[1].x <= 9
		&& holdingN.block[2].x <= 9
		&& holdingN.block[3].x <= 9
		&& holdingN.block[0].x >= 0
		&& holdingN.block[1].x >= 0
		&& holdingN.block[2].x >= 0
		&& holdingN.block[3].x >= 0
		&& holdingN.block[0].y >= 0
		&& holdingN.block[1].y >= 0
		&& holdingN.block[2].y >= 0
		&& holdingN.block[3].y >= 0
		&& holdingN.block[0].y <= 29
		&& holdingN.block[1].y <= 29
		&& holdingN.block[2].y <= 29
		&& holdingN.block[3].y <= 29;
}

char isblocked() {
	return field[holdingN.block[0].y][holdingN.block[0].x].ex
		| field[holdingN.block[1].y][holdingN.block[1].x].ex
		| field[holdingN.block[2].y][holdingN.block[2].x].ex
		| field[holdingN.block[3].y][holdingN.block[3].x].ex;
}

char findfit() {//spin和遇墙旋转的基础

	for (int i = 0; i < 4; i++) {//左
		holdingN.block[i].x--;
	}
	holdingX--;
	if (isleagal()) {
		if (!isblocked())return 5;
	}

	for (int i = 0; i < 4; i++) {//右
		holdingN.block[i].x += 2;
	}holdingX += 2;
	if (isleagal()) {
		if (!isblocked())return 6;
	}
	for (int i = 0; i < 4; i++) {//下
		holdingN.block[i].y--;
		holdingN.block[i].x--;
	}holdingY--;
	holdingX--;
	if (isleagal()) {
		if (!isblocked())return 1;
	}

	for (int i = 0; i < 4; i++) {//左下
		holdingN.block[i].x--;
	}holdingX--;
	if (isleagal()) {
		if (!isblocked())return 2;
	}

	for (int i = 0; i < 4; i++) {//右下
		holdingN.block[i].x += 2;
	}holdingX += 2;
	if (isleagal()) {
		if (!isblocked())return 3;
	}

	for (int i = 0; i < 4; i++) {//下下
		holdingN.block[i].x--;
		holdingN.block[i].y--;
	}holdingX--;
	holdingY--;
	if (isleagal()) {
		if (!isblocked())return 9;
	}

	for (int i = 0; i < 4; i++) {//左下下
		holdingN.block[i].x--;
	}holdingX--;
	if (isleagal()) {
		if (!isblocked())return 10;
	}

	for (int i = 0; i < 4; i++) {//右下下
		holdingN.block[i].x += 2;
	}holdingX += 2;
	if (isleagal()) {
		if (!isblocked())return 11;
	}
	for (int i = 0; i < 4; i++) {//上
		holdingN.block[i].y += 3;
		holdingN.block[i].x--;
	}holdingY += 3;
	holdingX--;
	if (isleagal()) {
		if (!isblocked())return 4;
	}



	for (int i = 0; i < 4; i++) {//左上
		holdingN.block[i].x--;
	}
	holdingX--;
	if (isleagal()) {
		if (!isblocked())return 7;
	}

	for (int i = 0; i < 4; i++) {//右上
		holdingN.block[i].x += 2;
	}holdingX += 2;
	if (isleagal()) {
		if (!isblocked())return 8;
	}



	for (int i = 0; i < 4; i++) {
		holdingN.block[i].x--;
		holdingN.block[i].y--;
	}holdingX--;
	holdingY--;
	return 0;
}

char islinefull(int y) {
	for (int i = 0; i < 10; i++) {
		if (!field[y][i].ex)return 0;
	}
	return 1;
}

char clean() {
	int m = 0;
	for (int i = 0; i < 29; ) {
		if (islinefull(i)) {
			m++;
			for (int j = 0; j < 10; j++) {
				for (int k = i; k < 29; k++) {
					field[k][j].ex = field[k + 1][j].ex;
					field[k][j].te = field[k + 1][j].te;
				}
			}
		}
		else i++;
	}
	return m;
}


char falltime_sp = 0;

void addscore(char l) {
	switch (l) {
	case 1:
		score += 100 * (1 + (!falltime_sp) * 2);
		break;
	case 2:
		score += 300 * (1 + (!falltime_sp) * 2);
		break;
	case 3:
		score += 500 * (1 + (!falltime_sp) * 2);
		break;
	case 4:
		score += 800 * (1 + (!falltime_sp) * 2);
		break;
	}
}

char isempty() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 10; j++) {
			if (field[i][j].ex)return 0;
		}
	}
	return 1;
}