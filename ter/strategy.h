#pragma once
#include "train.h"
#include <string.h>


char pld(char field_[][10], ter N, char x, char topt) {
	if (topt > 14)topt = 14;
	for (int i = 0; i < 4; i++) {
		N.block[i].x += x;
		N.block[i].y += topt + 1;
	}
	int t = 0;
	while (1) {
		for (int i = 0; i < 4; i++) {
			if (field_[N.block[i].y - 1][N.block[i].x] || !N.block[i].y) {
				field_[N.block[0].y][N.block[0].x] = 1;
				field_[N.block[1].y][N.block[1].x] = 1;
				field_[N.block[2].y][N.block[2].x] = 1;
				field_[N.block[3].y][N.block[3].x] = 1;
				return topt + 1 - t;
			};
		}
		N.block[0].y--;
		N.block[1].y--;
		N.block[2].y--;
		N.block[3].y--;
		t++;
	}
}


int getSumHeight(char f[][10]) {
	int m = 0;
	for (int j = 0; j < 10; j++) {
		for (int i = 15; i >= 0; i--) {
			if (f[i][j]) {
				m += i;
				break;
			}
		}
	}
	return m;
}

int getDispersionX_1(char f[][10], int i) {
	int m = 0;
	char t = 1;
	for (int j = 0; j < 10; j++) {
		if (t != f[i][j]) {
			t = f[i][j];
			m++;
		}
	}
	return m + (t == 0);
}
int getDispersionY_1(char f[][10], int i, char h) {
	int m = 0;
	char t = 1;
	for (int j = h - 1; j >= 0; j--) {
		if (t != f[j][i]) {
			t = f[j][i];
			m++;
		}
	}
	return m + (t == 0);
}
char getheight_1(char f[][10], int j, int hm) {
	for (int i = hm; i >= 0; i--) {
		if (f[i][j])return i;
	}
	return -1;
}
int getUnreachable_1(char f[][10], int j, char h) {
	int m = 0;
	while (--h >= 0) {
		if (!f[h][j])m++;
	}
	return m;
}

char whereAngleStarts(char h) {
	switch (h) {
	case TerT:
		return 0;
		break;
	case TerI:
		return 2;
		break;
	case TerO:
		return 3;
		break;
	case TerS:
		return 2;
		break;
	case TerZ:
		return 2;
		break;
	case TerL:
		return 0;
		break;
	case TerJ:
		return 0;
		break;
	}
}
char whereXends(ter N) {
	int x = 9;
	for (int i = 0; i < 4; i++) {
		int t = 9 - N.block[i].x;
		if (t < x)x = t;
	}
	return x;
}
void getDeltaDispersionDirectWhenNoClearExist(ter N, char x, char lift, int* deltax, int* deltay, char field[][10]) {
	int xt = 0, yt = 0;
	for (int i = 0; i < 4; i++) {
		N.block[i].x += x;
		N.block[i].y += lift;
		field[N.block[i].y][N.block[i].x]++;//0 1 2
	}
	for (int i = 0; i < 4; i++) {
		if (N.block[i].x == 0) {
			xt--;
			switch (field[N.block[i].y][N.block[i].x + 1]) {
			case 0:
				xt++;
				break;
			case 1:
				xt--;
				break;
			}
		}
		else if (N.block[i].x == 9) {
			xt--;
			switch (field[N.block[i].y][N.block[i].x - 1]) {
			case 0:
				xt++;
				break;
			case 1:
				xt--;
				break;
			}
		}
		else
		{
			switch (field[N.block[i].y][N.block[i].x - 1]) {
			case 0:
				xt++;
				break;
			case 1:
				xt--;
				break;
			}
			switch (field[N.block[i].y][N.block[i].x + 1]) {
			case 0:
				xt++;
				break;
			case 1:
				xt--;
				break;
			}
		}
		if (N.block[i].y)
		{
			switch (field[N.block[i].y - 1][N.block[i].x]) {
			case 0:
				yt++;
				break;
			case 1:
				yt--;
				break;
			}
			switch (field[N.block[i].y + 1][N.block[i].x]) {
			case 0:
				yt++;
				break;
			}

		}
	}
	for (int i = 0; i < 4; i++) {
		field[N.block[i].y][N.block[i].x]--;//0 1
	}
	*deltax += xt;
	*deltay += yt;
}
char getDeltaUnreachableDirectWhenNoClearExist(ter N, char x, char lift, char field[][10]) {
	int xt = 0, yt = 0, m = 0;
	for (int i = 0; i < 4; i++) {
		N.block[i].x += x;
		N.block[i].y += lift;
		for (int j = N.block[i].y - 1; j >= 0; j--) {
			if (field[j][N.block[i].x]) {
				break;
			}
			m++;
		}
	}
	return m;
}
void add2choice(int choiceRemained[][40], int sims1, int ii, int jj, int* end) {
	for (int i = 0; i < 40; i++) {
		if (choiceRemained[2][i] < sims1) {
			for (int j = *end; j > i; j--) {
				choiceRemained[0][j] = choiceRemained[0][j - 1];
				choiceRemained[1][j] = choiceRemained[1][j - 1];
				choiceRemained[2][j] = choiceRemained[2][j - 1];
			}
			choiceRemained[2][i] = sims1;
			choiceRemained[0][i] = ii;
			choiceRemained[1][i] = jj;
			(*end)++;
			return;
		}
	}
}
void exhausion(char holding, char next, char field[][10], char* x1, char* degree1) {

	int simscore = -2000000;
	int dpX0[20] = { 0 };
	int dpY0[10];
	int unrea0[10];
	char h0[10];
	char h2[10];

	for (int ii = 0; ii < 10; ii++) {
		h0[ii] = getheight_1(field, ii, 14);
		unrea0[ii] = getUnreachable_1(field, ii, h0[ii]);
		dpY0[ii] = getDispersionY_1(field, ii, h0[ii]);
	}
	memcpy(h2, h0, 10);
	for (int ii = 0; ii < 15; ii++) {
		dpX0[ii] = getDispersionX_1(field, ii);
	}
	char top0 = gettopbyh(h0);


	int k1 = top0 / 2;
	int k2 = 5;
	int k3 = 6 + top0 / 5;
	int k4 = 4 - top0 / 5;
	int k5 = 1;

	int choiceRemained[3][40] = { 0 };//i j sims1
	choiceRemained[2][0] = -22222222;
	int end = 1;
	for (int i = whereAngleStarts(holding); i < 4; i++) {
		ter N1 = rotate(holding, i * 90);
		char t1 = whereXends(N1);
		for (int j = 0; j <= t1; j++) {

			char h1[10];
			memcpy(h1, h0, 10);

			char _field[20][10] = { 0 };
			memcpy(_field, field, 150);
			char lift1 = pld(_field, N1, j, top0);
			int sims1 = clean(_field);

			int deltaDispersionX = 0,
				deltaDispersionY = 0,
				deltaUnreachable = 0,
				deltah = 0;
			char top1, topt, deltaTop;
			char lineIncluded[20] = { 0 }, columnIncluded[10] = { 0 };
			if (sims1) {
				for (int ii = 0; ii < 4; ii++) {
					lineIncluded[N1.block[ii].y + lift1]++;
				}
				for (int ii = 0; ii <= 9; ii++) {
					h1[ii] = getheight_1(_field, ii, top0 + 4 > 14 ? 14 : top0 + 4);
					deltah += h1[ii] - h0[ii];
					deltaUnreachable += getUnreachable_1(_field, ii, h1[ii]) - unrea0[ii];
					deltaDispersionY += getDispersionY_1(_field, ii, h1[ii]) - dpY0[ii];
				}
				top1 = gettopbyh(h1);
				deltaTop = top1 - top0;
				topt = deltaTop > 0 ? top1 : top0;
				int ii = 0;
				for (; ii <= topt; ii++) {
					if (lineIncluded[ii])break;
				}
				for (; ii <= topt; ii++) {
					deltaDispersionX += getDispersionX_1(_field, ii) - dpX0[ii];
				}
			}
			else {
				for (int ii = 0; ii < 4; ii++) {
					columnIncluded[N1.block[ii].x + j]++;
				}
				for (int ii = 0; ii < 10; ii++) {
					if (columnIncluded[ii]) {
						h1[ii] = getheight_1(_field, ii, 14);
						deltah += h1[ii] - h0[ii];
					}
				}
				top1 = gettopbyh(h1);
				deltaTop = top1 - top0;
				getDeltaDispersionDirectWhenNoClearExist(N1, j, lift1, &deltaDispersionX, &deltaDispersionY, _field);
				deltaUnreachable += getDeltaUnreachableDirectWhenNoClearExist(N1, j, lift1, _field);
			}
			switch (sims1) {
			case 1:sims1 = 3; break;
			case 2:sims1 = 12; break;
			case 3:sims1 = 28; break;
			case 4:sims1 = 44; break;
			case 5:sims1 = 111; break;
			case 6:sims1 = 170; break;
			case 7:sims1 = 210; break;
			case 8:sims1 = 250; break;
			}
			if (top1 >= 15)sims1 -= 500000;
			sims1 -= deltaTop * k1 + deltaUnreachable * k2 + deltaDispersionX * k3 + deltaDispersionY * k4 + deltah * k5;

			if (top0 < 5 && j == 0)sims1 -= 50000;
			if (top0 == 6 && j == 0)sims1 -= 35;
			if (top0 == 7 && j == 0)sims1 -= 25;

			add2choice(choiceRemained, sims1, i, j, &end);
		}
	}
	//for (int i = whereAngleStarts(holding); i < 4; i++) {
	//	ter N1 = rotate(holding, i * 90);
	//	char t1 = whereXends(N1);
	//	for (int j = 0; j <= t1; j++) {
	for(int s=0;s<10;s++){
		int i = choiceRemained[0][s];
		int j = choiceRemained[1][s];
		ter N1 = rotate(holding, i * 90);
			char columnIncluded[10] = { 0 };
			char lineIncluded[20] = { 0 };

			char _field[20][10] = { 0 };
			memcpy(_field, field, 150);

			char lift1 = pld(_field, N1, j, top0);
			int tem1 = clean(_field);
			if (
				(lift1 + N1.block[0].y - tem1 >= 15) +
				(lift1 + N1.block[1].y - tem1 >= 15) +
				(lift1 + N1.block[2].y - tem1 >= 15) +
				(lift1 + N1.block[3].y - tem1 >= 15)
				)continue;




			//剪枝
			char flag1 = 0;
			int temh1 = 0, temunrea1 = 0;
			for (int ii = 0; ii < 4; ii++) {
				columnIncluded[N1.block[ii].x + j]++;
			}
			for (int ii = 0; ii < 10; ii++) {
				if (columnIncluded[ii]) {
					temh1 = getheight_1(_field, ii, top0 + 4 > 14 ? 14 : top0 + 4);
					if (temh1 > top0) {
						temunrea1 = getUnreachable_1(_field, ii, temh1);
						if (temunrea1 > unrea0[ii]) {
							flag1 = 1;
							break;
						}
					}
				}
			}
			if (flag1) continue;


			for (int k = whereAngleStarts(next); k < 4; k++) {
				ter N2 = rotate(next, k * 90);
				char t2 = whereXends(N2);
				for (int l = 0; l <= t2; l++) {

					char field_[20][10] = { 0 };
					memcpy(field_, _field, 150);

					char wstpsbdmh;
					switch (holding) {
					case TerT:
						wstpsbdmh = k % 2 ? 3 : 2;
						break;
					case TerI:
						wstpsbdmh = k % 2 ? 4 : 1;
						break;
					case TerO:
						wstpsbdmh = 2;
						break;
					case TerS:
						wstpsbdmh = k % 2 ? 3 : 2;
						break;
					case TerZ:
						wstpsbdmh = k % 2 ? 3 : 2;
						break;
					case TerL:
						wstpsbdmh = k % 2 ? 3 : 2;
						break;
					case TerJ:
						wstpsbdmh = k % 2 ? 3 : 2;
						break;
					}


					char lift2 = pld(field_, N2, l, top0 + wstpsbdmh);//应该改成局部最高
					int cln2 = clean(field_);
					int tem2 = tem1 + cln2;
					if (simscore > -50000 &&
						(lift2 + N2.block[0].y - cln2 >= 15) +
						(lift2 + N2.block[1].y - cln2 >= 15) +
						(lift2 + N2.block[2].y - cln2 >= 15) +
						(lift2 + N2.block[3].y - cln2 >= 15)
						)continue;

					int deltaDispersionX = 0,
						deltaDispersionY = 0,
						deltaUnreachable = 0,
						deltah = 0;


					switch (tem2) {
					case 1:
						tem2 = 3;
						break;
					case 2:
						tem2 = 12;
						break;
					case 3:
						tem2 = 28;
						break;
					case 4:
						tem2 = 44;
						break;
					case 5:
						tem2 = 111;
						break;
					case 6:
						tem2 = 170;
						break;
					case 7:
						tem2 = 210;
						break;
					case 8:
						tem2 = 250;
						break;
					}

					char top2, topt, deltaTop;

					if (tem2) {
						for (int ii = 0; ii < 4; ii++) {
							lineIncluded[N1.block[ii].y + lift1]++;
							lineIncluded[N2.block[ii].y + lift2]++;
						}
						for (int ii = 0; ii <= 9; ii++) {
							h2[ii] = getheight_1(field_, ii, top0 + 8 > 14 ? 14 : top0 + 8);
							deltah += h2[ii] - h0[ii];
							deltaUnreachable += getUnreachable_1(field_, ii, h2[ii]) - unrea0[ii];
							deltaDispersionY += getDispersionY_1(field_, ii, h2[ii]) - dpY0[ii];
						}
						top2 = gettopbyh(h2);
						deltaTop = top2 - top0;
						topt = deltaTop > 0 ? top2 : top0;

						int ii = 0;
						for (; ii <= topt; ii++) {
							if (lineIncluded[ii])break;
						}

						for (; ii <= topt; ii++) {
							deltaDispersionX += getDispersionX_1(field_, ii) - dpX0[ii];
						}
					}
					else {
						for (int ii = 0; ii < 4; ii++) {
							//columnIncluded[N1.block[ii].x + j]++;
							columnIncluded[N2.block[ii].x + l]++;
							//lineIncluded[N1.block[ii].y + lift1]++;
							//lineIncluded[N2.block[ii].y + lift2]++;
						}
						for (int ii = 0; ii < 10; ii++) {
							if (columnIncluded[ii]) {
								h2[ii] = getheight_1(field_, ii, 14);
								//deltaUnreachable += getUnreachable_1(field_, ii, h2[ii]) - unrea0[ii];
								//deltaDispersionY += getDispersionY_1(field_, ii, h2[ii]) - dpY0[ii];
								deltah += h2[ii] - h0[ii];
							}
						}
						top2 = gettopbyh(h2);
						deltaTop = top2 - top0;/*
						topt = deltaTop > 0 ? top2 : top0;

						for (int ii = 0; ii <= topt; ii++) {
							if (lineIncluded[ii]) {
								deltaDispersionX += getDispersionX_1(field_, ii) - dpX0[ii];
							}
						}*/
						getDeltaDispersionDirectWhenNoClearExist(N1, j, lift1, &deltaDispersionX, &deltaDispersionY, _field);
						getDeltaDispersionDirectWhenNoClearExist(N2, l, lift2, &deltaDispersionX, &deltaDispersionY, field_);
						deltaUnreachable += getDeltaUnreachableDirectWhenNoClearExist(N1, j, lift1, _field);
						deltaUnreachable += getDeltaUnreachableDirectWhenNoClearExist(N2, l, lift2, field_);
					}




					if (top2 >= 15)tem2 -= 500000;
					tem2 -=
						deltaTop * k1
						+ deltaUnreachable * k2
						+ deltaDispersionX * k3
						+ deltaDispersionY * k4
						+ deltah * k5
						;

					if (tem2 > simscore) {
						simscore = tem2;
						*x1 = j;
						*degree1 = i;
					}
				}
			}
		}
	//}
}