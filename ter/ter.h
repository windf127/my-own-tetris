#pragma once
#define ULL unsigned long long

typedef struct point {
	char x;
	char y;
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
ter T[4] = {
	{{{0,0},{1,0},{2,0},{1,1}}},
	{{{0,0},{0,1},{1,1},{0,2}}},
	{{{1,0},{0,1},{1,1},{2,1}}},
	{{{1,0},{0,1},{1,1},{1,2}}}
};
ter I[2] = {
	{{{0,0},{1,0},{2,0},{3,0}}} ,
	{{{0,0},{0,1},{0,2},{0,3}}}
};
ter O = { {{0,0},{1,0},{0,1},{1,1}} };
ter S[2] = {
	{{{0,0},{1,0},{1,1},{2,1}}},
	{{{1,0},{0,1},{1,1},{0,2}}}
};
ter Z[2] = {
	{{{1,0},{2,0},{0,1},{1,1}}},
	{{{0,0},{0,1},{1,1},{1,2}}}
};
ter L[4] = {
	{{{0,0},{1,0},{2,0},{2,1}}},
	{{{0,0},{1,0},{0,1},{0,2}}},
	{{{0,0},{0,1},{1,1},{2,1}}},
	{{{1,0},{1,1},{0,2},{1,2}}}
};
ter J[4] = {
	{{{0,0},{1,0},{2,0},{0,1}}},
	{{{0,0},{0,1},{0,2},{1,2}}},
	{{{2,0},{0,1},{1,1},{2,1}}},
	{{{0,0},{1,0},{1,1},{1,2}}}
};

ter num2ter(char n) {
	switch (n) {
	case TerT:
		return T[0];
		break;
	case TerI:
		return I[0];
		break;
	case TerO:
		return O;
		break;
	case TerS:
		return S[0];
		break;
	case TerZ:
		return Z[0];
		break;
	case TerL:
		return L[0];
		break;
	case TerJ:
		return J[0];
		break;
	}
}
char char2num(char m) {
	switch (m) {
	case 'T':
		return 1;
		break;
	case 'I':
		return 2;
		break;
	case 'O':
		return 3;
		break;
	case 'S':
		return 4;
		break;
	case 'Z':
		return 5;
		break;
	case 'L':
		return 6;
		break;
	case 'J':
		return 7;
		break;
	case 'X':
		return 0;
		break;
	case 'E':
		return 8;
		break;
	}
}
ter rotate(char n, int degree) {
	switch (n) {
	case TerT:
		return T[degree / 90];
		break;
	case TerI:
		return I[(degree / 90) % 2];
		break;
	case TerO:
		return O;
		break;
	case TerS:
		return S[(degree / 90) % 2];
		break;
	case TerZ:
		return Z[(degree / 90) % 2];
		break;
	case TerL:
		return L[degree / 90];
		break;
	case TerJ:
		return J[degree / 90];
		break;
	}
}
ter placeDown(char f[][10], ter N, /*int*/char x) {
	for (int i = 0; i < 4; i++) {
		N.block[i].x += x;
		N.block[i].y += 15;
	}
	while (1) {
		for (int i = 0; i < 4; i++) {
			if (f[N.block[i].y - 1][N.block[i].x] || !N.block[i].y) {
				for (int i = 0; i < 4; i++) {
					f[N.block[i].y][N.block[i].x] = 1;
				}
				return N;
			}
		}
		for (int i = 0; i < 4; i++) {
			N.block[i].y--;
		}
	}
}
char gettop(char f[][10]) {
	for (int i = 15; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (f[i][j])return i;
		}
	}
	return -1;
}
char gettopbyh(char h[10]) {
	int max = h[0];
	for (int i = 1; i < 10; i++) {
		if (h[i] > max)max = h[i];
	}
	return max;
}
char linefull(char* f) {
	for (int i = 0; i < 10; i++) {
		if (!f[i])return 0;
	}
	return 1;
}
char  clean(char f[][10]) {
	char howmanylines = 0,t=14;
	for (int i = 0; i <= t;) {
		if (linefull(f[i])) {
			for (int j = i; j <= 17; j++) {
				for (int k = 0; k < 10; k++) {
					f[j][k] = f[j + 1][k];
				}
			}
			howmanylines++;
			t--;
		}
		else i++;
	}
	return howmanylines;
}
void addscore(ULL* score, char howmanylines) {
	switch (howmanylines) {
	case 1:
		*score += 100;
		break;
	case 2:
		*score += 300;
		break;
	case 3:
		*score += 500;
		break;
	case 4:
		*score += 800;
		break;
	}
}