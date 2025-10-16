#pragma once
#include <windows.h>
#include <process.h>
#include "tetr.h"
#include <conio.h>
#include <string.h>

#define KPT_THRESHOLD 200
char text[100] = { 0 };
char gotext[40] = {0};
char pctext[30] = { 0 };
char spinflag = 0;
void buildtext(char clean) {
	switch (holding) {
	case TerT:sprintf(text, "T "); break;
	case TerI:sprintf(text, "I "); break;
	case TerO:sprintf(text, "O "); break;
	case TerS:sprintf(text, "S "); break;
	case TerZ:sprintf(text, "Z "); break;
	case TerL:sprintf(text, "L "); break;
	case TerJ:sprintf(text, "J "); break;
	}
	if (spinflag) {
		strcat(text, "SPIN ");
	}

	switch (clean) {
	case 1:
		strcat(text, "SINGLE");
		break;
	case 2:
		strcat(text, "DOUBLE");
		break;
	case 3:
		strcat(text, "TRIPLE");
		break;
	case 4:
		strcat(text, "TETRIS");
		break;
	}
}
char keystate(char key, char* state) {
	if (GetKeyState(key) & 0x8000 && !*state) {
		*state = 1;
		return -1;//按下
	}
	if (!(GetKeyState(key) & 0x8000) && *state) {
		*state = 0;
		return 1;//抬起
	}
	return 0;
}
unsigned __stdcall kbdthread(void* data) {
	char
		stateA = 0,
		stateR = 0,
		stateW = 0,
		stateD = 0,
		stateSHIFT = 0,
		stateSPACE = 0,
		stateLEFT = 0,
		stateDOWN = 0,
		stateRIGHT = 0;
	time_t timeleftdown = 0, timerightdown = 0;
	time_t lastfall = 0;
	time_t lastmoveL = 0, lastmoveR = 0;
	while (1) {
		printf("\r%d %d\r", holdingN.block[0].x, holdingN.block[0].y);
		
		
		double now = clock();
		if ((now - lastfall) / CLOCKS_PER_SEC * 1000 > downSpeed) {
			if (!(holdingN.block[0].y == 0 ||
				holdingN.block[1].y == 0 ||
				holdingN.block[2].y == 0 ||
				holdingN.block[3].y == 0))
			{
				if (!(field[holdingN.block[0].y - 1][holdingN.block[0].x].ex == 1 ||
					field[holdingN.block[1].y - 1][holdingN.block[1].x].ex == 1 ||
					field[holdingN.block[2].y - 1][holdingN.block[2].x].ex == 1 ||
					field[holdingN.block[3].y - 1][holdingN.block[3].x].ex == 1)) {
					lastfall = clock();
					for (int i = 0; i < 4; i++) {
						holdingN.block[i].y--;
					}
					holdingY--;
					falltime_sp++;
				}

			}

		}
		if (holdingN.block[0].y == 0 ||
			holdingN.block[1].y == 0 ||
			holdingN.block[2].y == 0 ||
			holdingN.block[3].y == 0) {
			if ((now - lastfall) / CLOCKS_PER_SEC * 1000 > ALLOWED_TIME) {
				field[holdingN.block[0].y][holdingN.block[0].x].ex = 1;
				field[holdingN.block[1].y][holdingN.block[1].x].ex = 1;
				field[holdingN.block[2].y][holdingN.block[2].x].ex = 1;
				field[holdingN.block[3].y][holdingN.block[3].x].ex = 1;
				field[holdingN.block[0].y][holdingN.block[0].x].te = holding;
				field[holdingN.block[1].y][holdingN.block[1].x].te = holding;
				field[holdingN.block[2].y][holdingN.block[2].x].te = holding;
				field[holdingN.block[3].y][holdingN.block[3].x].te = holding;


				char clea = clean();
				addscore(clea);
				buildtext(clea);

				inherit();
				holdingX = INITIAL_X;
				holdingY = INITIAL_Y;
				ter N = num2ter(holding);
				for (int i = 0; i < 4; i++) {
					holdingN.block[i].x = holdingX + N.block[i].x;
					holdingN.block[i].y = holdingY + N.block[i].y;
					holdingDegree = 0;
				}

				sprintf(pctext, " ");
				if (isempty()) {
					sprintf(pctext, "PERFECT CLEAR");
					score += 2000;
				}
				sprintf(gotext, " ");
				for (int i = 0; i < 10; i++) {
					if (field[20][i].ex) {
						initialize();
						sprintf(gotext, "GAME OVER");
						sprintf(text, " ");
					}
				}
			}
		}
		else if (field[holdingN.block[0].y - 1][holdingN.block[0].x].ex == 1 ||
			field[holdingN.block[1].y - 1][holdingN.block[1].x].ex == 1 ||
			field[holdingN.block[2].y - 1][holdingN.block[2].x].ex == 1 ||
			field[holdingN.block[3].y - 1][holdingN.block[3].x].ex == 1) {
			if ((now - lastfall) / CLOCKS_PER_SEC * 1000 > ALLOWED_TIME) {
				field[holdingN.block[0].y][holdingN.block[0].x].ex = 1;
				field[holdingN.block[1].y][holdingN.block[1].x].ex = 1;
				field[holdingN.block[2].y][holdingN.block[2].x].ex = 1;
				field[holdingN.block[3].y][holdingN.block[3].x].ex = 1;
				field[holdingN.block[0].y][holdingN.block[0].x].te = holding;
				field[holdingN.block[1].y][holdingN.block[1].x].te = holding;
				field[holdingN.block[2].y][holdingN.block[2].x].te = holding;
				field[holdingN.block[3].y][holdingN.block[3].x].te = holding;


				char clea = clean();
				addscore(clea);
				buildtext(clea);

				inherit();
				holdingX = INITIAL_X;
				holdingY = INITIAL_Y;
				ter N = num2ter(holding);
				for (int i = 0; i < 4; i++) {
					holdingN.block[i].x = holdingX + N.block[i].x;
					holdingN.block[i].y = holdingY + N.block[i].y;
					holdingDegree = 0;
				}

				sprintf(pctext, " ");
				if (isempty()) {
					sprintf(pctext, "PERFECT CLEAR");
					score += 2000;
				}
				sprintf(gotext, " ");
				for (int i = 0; i < 10; i++) {
					if (field[20][i].ex) {
						initialize();
						sprintf(gotext, "GAME OVER");
						sprintf(text, " ");
					}
				}
			}
		}
		char kestatLEFT = keystate(VK_LEFT, &stateLEFT);
		char kestatRIGHT = keystate(VK_RIGHT, &stateRIGHT);
		char kestatDOWN = keystate(VK_DOWN, &stateDOWN);
		char kestatA = keystate('A', &stateA);
		char kestatR = keystate('R', &stateR);
		char kestatD = keystate('D', &stateD);
		char kestatW = keystate('W', &stateW);
		char kestatSHIFT = keystate(VK_SHIFT, &stateSHIFT);
		char kestatSPACE = keystate(VK_SPACE, &stateSPACE);
		//left
		if (kestatLEFT == -1) {
			for (int i = 0; i < 4; i++) {
				holdingN.block[i].x--;
			}
			holdingX--;
			if (isleagal()) {
				if (isblocked()) {
					for (int i = 0; i < 4; i++) {
						holdingN.block[i].x++;
					}
					holdingX++;
				}
			}
			else {
				for (int i = 0; i < 4; i++) {
					holdingN.block[i].x++;
				}
				holdingX++;
			}
			timeleftdown = now;
		}
		if (kestatLEFT == 1) {
			timeleftdown = 0;
			lastmoveL = 0;
		}
		if (timeleftdown && (now - timeleftdown) / CLOCKS_PER_SEC * 1000 > KPT_THRESHOLD) {
			if ((now - lastmoveL) / CLOCKS_PER_SEC * 1000 > MOVE_INTERVAL) {
				lastmoveL = clock();
				for (int i = 0; i < 4; i++) {
					holdingN.block[i].x--;
				}
				holdingX--;
				if (isleagal()) {
					if (isblocked()) {
						for (int i = 0; i < 4; i++) {
							holdingN.block[i].x++;
						}
						holdingX++;
					}
				}
				else {
					for (int i = 0; i < 4; i++) {
						holdingN.block[i].x++;
					}
					holdingX++;
				}
			}
		}
		//right
		if (kestatRIGHT == -1) {
			for (int i = 0; i < 4; i++) {
				holdingN.block[i].x++;
			}
			holdingX++;
			if (isleagal()) {
				if (isblocked()) {
					for (int i = 0; i < 4; i++) {
						holdingN.block[i].x--;
					}
					holdingX--;
				}
			}
			else {
				for (int i = 0; i < 4; i++) {
					holdingN.block[i].x--;
				}
				holdingX--;
			}
			timerightdown = now;
		}
		if (kestatRIGHT == 1) {
			timerightdown = 0;
			lastmoveR = 0;
		}
		if (timerightdown && (now - timerightdown) / CLOCKS_PER_SEC * 1000 > KPT_THRESHOLD) {
			if ((now - lastmoveR) / CLOCKS_PER_SEC * 1000 > MOVE_INTERVAL) {
				lastmoveR = clock();
				for (int i = 0; i < 4; i++) {
					holdingN.block[i].x++;
				}
				holdingX++;
				if (isleagal()) {
					if (isblocked()) {
						for (int i = 0; i < 4; i++) {
							holdingN.block[i].x--;
						}
						holdingX--;
					}
				}
				else {
					for (int i = 0; i < 4; i++) {
						holdingN.block[i].x--;
					}
					holdingX--;
				}
			}
		}
		//down
		if (kestatDOWN == -1) {
			downSpeed = SOFT_TIME_PER_DOWN;
		}
		if (kestatDOWN == 1) {
			downSpeed = NATRUAL_TIME_PER_DOWN;
		}
		//
		if (kestatA == -1) {
			spin90();
			spin90();
			spin90();
			if (isleagal()) {//合法 用isblocked之前必须判断是否合法，否则可越界
				if (isblocked()) {//被占位
					if (!findfit()) {
						spin90();
					}
					else {
						holdingDegree = (holdingDegree + 3) % 4;
						falltime_sp = 0;
					}

				}
				else {
					holdingDegree = (holdingDegree + 3) % 4;
					falltime_sp = 0;
				}
			}
			else {
				if (!findfit()) {
					spin90();
				}
				else {
					holdingDegree = (holdingDegree + 3) % 4;
					falltime_sp = 0;
				}

			}
		}
		if (kestatW == -1) {
			spin90();
			spin90();
			if (isleagal()) {//合法 用isblocked之前必须判断是否合法，否则可越界
				if (isblocked()) {//被占位
					if (!findfit()) {
						spin90();
						spin90();
					}
					else {
						holdingDegree = (holdingDegree + 2) % 4;
						falltime_sp = 0;
					}

				}
				else {
					holdingDegree = (holdingDegree + 2) % 4;
					falltime_sp = 0;
				}
			}
			else {
				if (!findfit()) {
					spin90();
					spin90();
				}
				else {
					holdingDegree = (holdingDegree + 2) % 4;
					falltime_sp = 0;
				}

			}
		}
		if (kestatD == -1) {
			spin90();
			if (isleagal()) {//合法 用isblocked之前必须判断是否合法，否则可越界
				if (isblocked()) {//被占位
					if (!findfit()) {
						spin90();
						spin90();
						spin90();
					}
					else {
						holdingDegree = (holdingDegree + 1) % 4;
						falltime_sp = 0;
					}

				}
				else {
					holdingDegree = (holdingDegree + 1) % 4;
					falltime_sp = 0;
				}
			}
			else {
				if (!findfit()) {
					spin90();
					spin90();
					spin90();
				}
				else {
					holdingDegree = (holdingDegree + 1) % 4;
					falltime_sp = 0;
				}

			}
		}
		if (kestatSHIFT == -1) {
			if (save == 0) {
				save = holding;
				inherit();
			}
			else {
				char tem = save;
				save = holding;
				holding = tem;
			}
			holdingX = INITIAL_X;
			holdingY = INITIAL_Y;
			ter N = num2ter(holding);
			for (int i = 0; i < 4; i++) {
				holdingN.block[i].x = holdingX + N.block[i].x;
				holdingN.block[i].y = holdingY + N.block[i].y;
				holdingDegree = 0;
			}
		}
		if (kestatR == -1) {
			initialize();
			sprintf(text, " ");
		}
		if (kestatSPACE == -1) {


			spinflag = 0;
			if (falltime_sp == 0) {
				if ((holdingN.block[0].y == 0 ||
					holdingN.block[1].y == 0 ||
					holdingN.block[2].y == 0 ||
					holdingN.block[3].y == 0))
				{
					spinflag = 1;
				}
				else if ((field[holdingN.block[0].y - 1][holdingN.block[0].x].ex == 1 ||
					field[holdingN.block[1].y - 1][holdingN.block[1].x].ex == 1 ||
					field[holdingN.block[2].y - 1][holdingN.block[2].x].ex == 1 ||
					field[holdingN.block[3].y - 1][holdingN.block[3].x].ex == 1)) {
					spinflag = 1;
				}
			}


			while (1) {
				for (int i = 0; i < 4; i++) {
					holdingN.block[i].y--;
				}
				if (!isleagal()) {
					for (int i = 0; i < 4; i++) {
						holdingN.block[i].y++;
					}
					break;
				}
				if (isblocked()) {
					for (int i = 0; i < 4; i++) {
						holdingN.block[i].y++;
					}
					break;
				}
			}
			field[holdingN.block[0].y][holdingN.block[0].x].ex = 1;
			field[holdingN.block[1].y][holdingN.block[1].x].ex = 1;
			field[holdingN.block[2].y][holdingN.block[2].x].ex = 1;
			field[holdingN.block[3].y][holdingN.block[3].x].ex = 1;
			field[holdingN.block[0].y][holdingN.block[0].x].te = holding;
			field[holdingN.block[1].y][holdingN.block[1].x].te = holding;
			field[holdingN.block[2].y][holdingN.block[2].x].te = holding;
			field[holdingN.block[3].y][holdingN.block[3].x].te = holding;


			char clea = clean();
			addscore(clea);
			buildtext(clea);

			inherit();
			holdingX = INITIAL_X;
			holdingY = INITIAL_Y;
			ter N = num2ter(holding);
			for (int i = 0; i < 4; i++) {
				holdingN.block[i].x = holdingX + N.block[i].x;
				holdingN.block[i].y = holdingY + N.block[i].y;
				holdingDegree = 0;
			}

			sprintf(pctext, " ");
			if (isempty()) {
				sprintf(pctext, "PERFECT CLEAR");
				score += 2000;
			}
			sprintf(gotext, " ");
			for (int i = 0; i < 10; i++) {
				if (field[20][i].ex) {
					initialize();
					sprintf(gotext, "GAME OVER");
					sprintf(text, " ");
				}
			}
			
			

		}
	}
	return 0;
}