#pragma once
#include "kbd.h"

void diplayBlock(int x, int y) {
	solidrectangle(x, WINDOW_HEIGHT - y, x + PIXEL_PER_BLOCK, WINDOW_HEIGHT - (y + PIXEL_PER_BLOCK));
}
void displayTER_ALPHA(int x, int y, ter N, char degree) {
	//顺90度  x增 -> y减   y增 -> x增
	switch (degree) {
	case 0:
		diplayBlock(x + N.block[0].x * PIXEL_PER_BLOCK, y + N.block[0].y * PIXEL_PER_BLOCK);
		diplayBlock(x + N.block[1].x * PIXEL_PER_BLOCK, y + N.block[1].y * PIXEL_PER_BLOCK);
		diplayBlock(x + N.block[2].x * PIXEL_PER_BLOCK, y + N.block[2].y * PIXEL_PER_BLOCK);
		diplayBlock(x + N.block[3].x * PIXEL_PER_BLOCK, y + N.block[3].y * PIXEL_PER_BLOCK);
		break;
	case 1:
		diplayBlock(x + N.block[0].y * PIXEL_PER_BLOCK, y - N.block[0].x * PIXEL_PER_BLOCK);
		diplayBlock(x + N.block[1].y * PIXEL_PER_BLOCK, y - N.block[1].x * PIXEL_PER_BLOCK);
		diplayBlock(x + N.block[2].y * PIXEL_PER_BLOCK, y - N.block[2].x * PIXEL_PER_BLOCK);
		diplayBlock(x + N.block[3].y * PIXEL_PER_BLOCK, y - N.block[3].x * PIXEL_PER_BLOCK);
		break;
	case 2:
		diplayBlock(x - N.block[0].x * PIXEL_PER_BLOCK, y - N.block[0].y * PIXEL_PER_BLOCK);
		diplayBlock(x - N.block[1].x * PIXEL_PER_BLOCK, y - N.block[1].y * PIXEL_PER_BLOCK);
		diplayBlock(x - N.block[2].x * PIXEL_PER_BLOCK, y - N.block[2].y * PIXEL_PER_BLOCK);
		diplayBlock(x - N.block[3].x * PIXEL_PER_BLOCK, y - N.block[3].y * PIXEL_PER_BLOCK);
		break;
	case 3:
		diplayBlock(x - N.block[0].y * PIXEL_PER_BLOCK, y + N.block[0].x * PIXEL_PER_BLOCK);
		diplayBlock(x - N.block[1].y * PIXEL_PER_BLOCK, y + N.block[1].x * PIXEL_PER_BLOCK);
		diplayBlock(x - N.block[2].y * PIXEL_PER_BLOCK, y + N.block[2].x * PIXEL_PER_BLOCK);
		diplayBlock(x - N.block[3].y * PIXEL_PER_BLOCK, y + N.block[3].x * PIXEL_PER_BLOCK);
		break;
	}
}
//x,y为窗口中的坐标
void displayTER_BETA(int x, int y, char n, char degree) {
	if (n == 0)return;
	switch (n) {
	case TerT:
		setfillcolor(RGB(128, 30, 128));
		break;
	case TerI:
		setfillcolor(RGB(30, 255, 255));
		break;
	case TerO:
		setfillcolor(RGB(255, 255, 30));
		break;
	case TerS:
		setfillcolor(RGB(30, 255, 30));
		break;
	case TerZ:
		setfillcolor(RGB(255, 30, 30));
		break;
	case TerL:
		setfillcolor(RGB(255, 165, 30));
		break;
	case TerJ:
		setfillcolor(RGB(30, 30, 255));
		break;
	}
	displayTER_ALPHA(x, y, num2ter(n), degree);

}

point FieldLL = { 200,50 };
int width = 10 * PIXEL_PER_BLOCK;
int height = 20 * PIXEL_PER_BLOCK;
void drawFiled() {

	setfillstyle(SOLID_FILL);
	setfillcolor(RGB(105, 105, 105));
	solidrectangle(FieldLL.x + width + 1, WINDOW_HEIGHT - (FieldLL.y + height), FieldLL.x + width + 1 + 6 * PIXEL_PER_BLOCK, WINDOW_HEIGHT - (FieldLL.y + height - 4 * PIXEL_PER_BLOCK));
	setfillcolor(RGB(155, 155, 155));
	solidrectangle(FieldLL.x, WINDOW_HEIGHT - FieldLL.y, FieldLL.x + width, WINDOW_HEIGHT - (FieldLL.y + height));
}
point POsave = { FieldLL.x - PIXEL_PER_BLOCK * 4 , FieldLL.y + PIXEL_PER_BLOCK * 17 };
point POn0 = { FieldLL.x + PIXEL_PER_BLOCK * 12 ,FieldLL.y + PIXEL_PER_BLOCK * 17 };
point POn1 = { FieldLL.x + PIXEL_PER_BLOCK * 12 ,FieldLL.y + PIXEL_PER_BLOCK * 13 };
point POn2 = { FieldLL.x + PIXEL_PER_BLOCK * 12 ,FieldLL.y + PIXEL_PER_BLOCK * 10 };
point POn3 = { FieldLL.x + PIXEL_PER_BLOCK * 12 ,FieldLL.y + PIXEL_PER_BLOCK * 7 };
point POn4 = { FieldLL.x + PIXEL_PER_BLOCK * 12 ,FieldLL.y + PIXEL_PER_BLOCK * 4 };
point POn5 = { FieldLL.x + PIXEL_PER_BLOCK * 12 ,FieldLL.y + PIXEL_PER_BLOCK * 1 };

void displayTer() {
	displayTER_BETA(POsave.x, POsave.y, save, 0);
	displayTER_BETA(POn0.x, POn0.y, next[0], 0);
	displayTER_BETA(POn1.x, POn1.y, next[1], 0);
	displayTER_BETA(POn2.x, POn2.y, next[2], 0);
	displayTER_BETA(POn3.x, POn3.y, next[3], 0);
	displayTER_BETA(POn4.x, POn4.y, next[4], 0);
	displayTER_BETA(POn5.x, POn5.y, next[5], 0);
}

void displayholding() {
	int x = FieldLL.x + holdingX * PIXEL_PER_BLOCK,
		y = FieldLL.y + holdingY * PIXEL_PER_BLOCK;
	switch (holding) {
	case TerT:
		setfillcolor(RGB(128, 30, 128));
		break;
	case TerI:
		setfillcolor(RGB(30, 255, 255));
		break;
	case TerO:
		setfillcolor(RGB(255, 255, 30));
		break;
	case TerS:
		setfillcolor(RGB(30, 255, 30));
		break;
	case TerZ:
		setfillcolor(RGB(255, 30, 30));
		break;
	case TerL:
		setfillcolor(RGB(255, 165, 30));
		break;
	case TerJ:
		setfillcolor(RGB(30, 30, 255));
		break;
	}
	for (int i = 0; i < 4; i++) {
		diplayBlock(FieldLL.x + holdingN.block[i].x * PIXEL_PER_BLOCK, FieldLL.y + holdingN.block[i].y * PIXEL_PER_BLOCK);
	}
	setfillcolor(RGB(240, 240, 240));
	solidrectangle(x + PIXEL_PER_BLOCK / 2 - 3, WINDOW_HEIGHT - (y + PIXEL_PER_BLOCK / 2 - 3), x + PIXEL_PER_BLOCK / 2 + 3, WINDOW_HEIGHT - (3 + y + PIXEL_PER_BLOCK / 2));
}

void displayFIELD() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 10; j++) {
			if (field[i][j].ex) {
				switch (field[i][j].te) {
				case TerT:
					setfillcolor(RGB(128, 90, 128));
					break;
				case TerI:
					setfillcolor(RGB(90, 255, 255));
					break;
				case TerO:
					setfillcolor(RGB(255, 255, 90));
					break;
				case TerS:
					setfillcolor(RGB(90, 255, 90));
					break;
				case TerZ:
					setfillcolor(RGB(255, 90, 90));
					break;
				case TerL:
					setfillcolor(RGB(255, 165, 90));
					break;
				case TerJ:
					setfillcolor(RGB(90, 90, 255));
					break;
				}
				diplayBlock(FieldLL.x + j * PIXEL_PER_BLOCK, FieldLL.y + i * PIXEL_PER_BLOCK);

			}
		}
	}
}

void preview() {
	ter TEM = holdingN;
	while (1) {
		for (int i = 0; i < 4; i++) {
			TEM.block[i].y--;
		}
		if (!(TEM.block[0].x <= 9
			&& TEM.block[1].x <= 9
			&& TEM.block[2].x <= 9
			&& TEM.block[3].x <= 9
			&& TEM.block[0].x >= 0
			&& TEM.block[1].x >= 0
			&& TEM.block[2].x >= 0
			&& TEM.block[3].x >= 0
			&& TEM.block[0].y >= 0
			&& TEM.block[1].y >= 0
			&& TEM.block[2].y >= 0
			&& TEM.block[3].y >= 0
			&& TEM.block[0].y <= 29
			&& TEM.block[1].y <= 29
			&& TEM.block[2].y <= 29
			&& TEM.block[3].y <= 29)) {
			for (int i = 0; i < 4; i++) {
				TEM.block[i].y++;
			}
			break;
		}
		if (field[TEM.block[0].y][TEM.block[0].x].ex
			| field[TEM.block[1].y][TEM.block[1].x].ex
			| field[TEM.block[2].y][TEM.block[2].x].ex
			| field[TEM.block[3].y][TEM.block[3].x].ex) {
			for (int i = 0; i < 4; i++) {
				TEM.block[i].y++;
			}
			break;
		}
	}
	setfillcolor(RGB(200, 200, 200));
	for (int i = 0; i < 4; i++) {
		diplayBlock(FieldLL.x + TEM.block[i].x * PIXEL_PER_BLOCK, FieldLL.y + TEM.block[i].y * PIXEL_PER_BLOCK);
	}
}

