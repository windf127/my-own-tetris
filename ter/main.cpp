#include <stdlib.h>
#include <time.h>
#include "strategy.h"

int main() {
	ULL maxscore = 0;

	char cas = 1;
	ULL score = 0;
	char holding, next;
	char field[20][10] = { 0 };
	char isgameover = 0;
	char degree = -1;
	char x = -1;
	srand((unsigned)time(NULL));
	next = rand() % 7 + 1;
	holding = rand() % 7 + 1;

	ULL roundtimes = 0;
	//char flaghasloded = load(&holding, &next, &field[0][0], &x, &degree, &score, &maxscore, &roundtimes);

	double endtime, starttime = clock();
	while (1) {
		//system("cls");
		//displayTer(num2ter(holding));
		//displayTer(num2ter(next));
		//displayField(field);

		printf("\rround:%llu  score:%llu  maxscore:%llu  time:%.2llfs   ", roundtimes, score, maxscore, (clock() - starttime) / CLOCKS_PER_SEC);

		if (isgameover ) {
			printf("GAME OVER\n");
			holding = rand() % 7 + 1;
			next = rand() % 7 + 1;
			for (int i = 0; i < 200; i++) {
				(&field[0][0])[i] = 0;
			}
			if (score > maxscore)maxscore = score;
			score = 0;
			isgameover = 0;
			roundtimes = 0;
			starttime = clock();
			continue;
		}

		exhausion(holding, next, field, &x, &degree);
		placeDown(field, rotate(holding, (int)(degree * 90)), x);
		addscore(&score, clean(field));

		holding = next;
		next = rand() % 7 + 1;

		for (int i = 0; i < 10; i++) {
			if (field[15][i]) {
				isgameover = 1;
				break;
			}
		}
		//_sleep(200);
		roundtimes++;
	}
	return 0;
}