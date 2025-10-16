#include"display.h"

int TARGET_FPS = 60;
double TARGET_FRAME_TIME = 1000.0 / TARGET_FPS;

char kedescribe[20][30];

int main() {
	sprintf(kedescribe[0], "left: ����");
	sprintf(kedescribe[1], "right: ����");
	sprintf(kedescribe[2], "down: ��");
	sprintf(kedescribe[3], "W: ��ת180��");
	sprintf(kedescribe[4], "A: ��ת90��");
	sprintf(kedescribe[5], "D: ��ת90��");
	sprintf(kedescribe[6], "R: �ؿ�");
	sprintf(kedescribe[7], "shift: hold");
	sprintf(kedescribe[8], "space: Ӳ��");

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	time_t starttime = clock(), endtime;

	HANDLE hMsgThread = (HANDLE)_beginthreadex(NULL, 0, &kbdthread, NULL, 0, NULL);

	initialize();

	while (1) {

		if (next[6] == 0)refillnext();

		BeginBatchDraw();
		cleardevice();

		drawFiled();
		displayTer();
		preview();
		displayholding();
		displayFIELD();

		char text1[100] = { 0 };
		sprintf(text1, "score:%llu", score);
		wchar_t wcharText[100];
		MultiByteToWideChar(CP_ACP, 0, text1, -1, wcharText, 100);
		settextstyle(16, 8, _T("DE"));
		outtextxy(45, 350, wcharText);

		MultiByteToWideChar(CP_ACP, 0, text, -1, wcharText, 100);
		settextstyle(20, 10, _T("DE"));
		outtextxy(45, 380, wcharText);
		if(strlen(pctext)>3){
			MultiByteToWideChar(CP_ACP, 0, pctext, -1, wcharText, 100);
			outtextxy(45, 410, wcharText);
		}
		if (strlen(gotext) > 3) {
			MultiByteToWideChar(CP_ACP, 0, gotext, -1, wcharText, 100);
			outtextxy(45, 410, wcharText);
		}
		for (int i = 0; i < 9; i++) {
			MultiByteToWideChar(CP_ACP, 0, kedescribe[8-i], -1, wcharText, 100);
			outtextxy(720, 410-i*30, wcharText);
		}


		switch (gameState) {
		case GAMESTATE_MENU:

			break;
		case GAMESTATE_PLAY:
			break;
		case GAMESTATE_PAUSE:
			break;
		}
		EndBatchDraw();

		// ����֡��
		endtime = clock();
		int sleepTime = TARGET_FRAME_TIME - (endtime - starttime) * 1000 / CLOCKS_PER_SEC;
		if (sleepTime > 0) {
			Sleep(sleepTime);
		}
		starttime = clock();
	}

	return 0;
}