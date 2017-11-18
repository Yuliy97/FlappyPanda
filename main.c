#include <stdio.h>
#include "mylib.h"
#include "start.h"
#include "background.h"
#include "end.h"
#include "face.h"


// #define NCOL 5
// #define SPEED 1
// #define WIDTH 20
// #define TOPROW 0
// #define PSPD -2

enum State {
	START,
	START_NODRAW,
	GAME,
	OVER,
	RESET,
};
int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	COLUMN columnsTop[NCOL];
	COLUMN columnsBot[NCOL];
	COLUMN oldColumnTop[NCOL];
	COLUMN oldColumnBot[NCOL];
	//char num = 85;
	//char* numChar = &num;
	int highestPoint = 0;
	int points = 0;
	int distR;
	int botHeightR;
	PANDA panda;
	PANDA oldPanda;
	panda.row = 70;
	panda.col = 30;
	panda.spd = PSPD;
	panda.size = 10;
	oldPanda.row = panda.row;
	oldPanda.col = panda.col;
	oldPanda.spd = panda.spd;
	oldPanda.size = panda.size;
	int dist;
	int botHeight;
	for(int i = 0; i < NCOL; i++) {
		dist = random(5, 20);
		columnsTop[i].row = TOPROW;
		columnsTop[i].col = (i + 1) * 50 + dist;
		columnsTop[i].spd = SPEED;
		columnsTop[i].width = WIDTH;
		columnsTop[i].height = random(50, 70);
		columnsTop[i].color =  GREEN;

		botHeight = random(90, 120);
		columnsBot[i].row = botHeight;
		columnsBot[i].col = (i + 1) * 50 + dist;
		columnsBot[i].spd = SPEED;
		columnsBot[i].width = WIDTH;
		columnsBot[i].height = botHeight;
		columnsBot[i].color = GREEN;

		oldColumnBot[i] = columnsBot[i];
		oldColumnTop[i] = columnsTop[i];
	
	}

	//BALL balls[NBALLS];

	// int nballs = sizeof(balls) / sizeof(balls[0]);
	// BALL oldballs[NBALLS];
	// int size = 5;
	// int deltas[] = { -3, -2, -1, 1, 2, 3 };
	// int ndeltas = sizeof(deltas) / sizeof(deltas[0]);
	// int colors[] = { RED, BLUE, GREEN, YELLOW, CYAN, MAGENTA, WHITE };
	//int ncolors = sizeof(colors) / sizeof(colors[0]);
	enum State state = START;
	while(1) {
		waitForVblank();
		switch(state) {
			case START:
				drawImage3(0, 0, START_WIDTH, START_HEIGHT, start);
	// 				for (int i = 0; i < NCOL; i++) {
	// 	struct column *columnT = &oldColumnTop[i];
	// 				drawRect(columnT->row, columnT->col, columnT->height, columnT->width, GREEN);
	// 				struct column *columnB = &oldColumnBot[i];
	// 				drawRect(columnB->row, columnB->col, columnB->height, columnB->width, GREEN);
	// }		

				drawString(140, 130, "Press A to Start", WHITE);
				state = START_NODRAW;
				break;
			case START_NODRAW:
				if(KEY_DOWN_NOW(BUTTON_A)) {
					state = RESET;
				}
				break;
			case GAME:
				//drawImage3(0, 0, 240, 160, BLACK);

				
				while(1) {
					if (panda.row <= 0 || (panda.row + panda.size) >= 160) {
						state = OVER;
						break;
					}
					for(int i = 0; i < NCOL - 1; i++) {
						if (panda.row <= (columnsTop[i].height + columnsTop[i].row)) {
							if ((panda.col + panda.size) >= columnsTop[i].col) {
								state = OVER;
								break;
							}

						} 
						if ((panda.row + panda.size) >= columnsBot[i].height) {
						 	if ((panda.col + panda.size) >= columnsBot[i].col) {
								state = OVER;
								break;
							}
						}

						if(panda.col == columnsBot[i].col + columnsBot[i].width){

							points += 1;
						}
						
					}


					for(int i = 0; i < NCOL; i++) {
						struct column *columnT = &columnsTop[i];
						struct column *columnB = &columnsBot[i];
						oldColumnTop[i].row = columnT->row;
						oldColumnTop[i].col = columnT->col;
						oldColumnTop[i].spd = columnT->spd;
						oldColumnTop[i].width = columnT->width;
						oldColumnTop[i].height = columnT->height;
						oldColumnBot[i].row = columnB->row;
						oldColumnBot[i].col = columnB->col;
						oldColumnBot[i].spd = columnB->spd;
						oldColumnBot[i].width = columnB->width;
						oldColumnBot[i].height = columnB->height;
						columnsTop[i].col = columnT->col - columnT->spd;
						columnsBot[i].col = columnB->col - columnB->spd;
						if(columnT->col < 0 && columnB->col < 0) {
							columnT->col = 240;
							columnB->col = 240;
						}
					}
					waitForVblank();

					for(int i = 0; i < NCOL; i++) {
							
						struct column *oldColumnT = &oldColumnTop[i];
						struct column *oldColumnB = &oldColumnBot[i];
						//delete top cols
						drawRect(oldColumnT->row, oldColumnT->col + oldColumnT->width -1, oldColumnT->height+1, 1, BLACK);
						//delete bot cols
						drawRect(oldColumnB->row-1, oldColumnB->col + oldColumnT->width, oldColumnB->height, 1, BLACK);
						//drawString(0, 0, "Score: " + points, WHITE);
					}	
					for(int j = 0; j < NCOL; j++) {
						struct column *columnT = &columnsTop[j];
						struct column *columnB = &columnsBot[j];
						drawRect(columnT->row, columnT->col -1, columnT->height, 1, GREEN);
						drawRect(columnB->row, columnB->col -1, columnB->height, 1, GREEN);
						//drawString(0, 0, "Score: " + points, WHITE);
						oldColumnTop[j] = columnsTop[j];
						oldColumnBot[j] = columnsBot[j];
					}
					// numChar = intToString(points, numChar);
					// drawString(70, 135,""+numChar[2],WHITE);
					// drawString(70, 140, "" + numChar[1], WHITE);
					
					drawString(70, 120, "Score:", WHITE);
					drawRect(70, 170, 10, 10, BLACK);
					drawChar(70, 170, 48 +points+0, WHITE);
					if (KEY_DOWN_NOW(BUTTON_UP)) {
						
						drawRect(oldPanda.row, oldPanda.col, oldPanda.size, oldPanda.size, BLACK);

						//if (panda.spd < 0) {
						panda.spd  = PSPD;
						panda.row = panda.row + panda.spd;
						drawImage3(panda.row, panda.col, panda.size, panda.size, face);
						//drawRect(panda.row, panda.col, panda.size, panda.size, WHITE);
						//drawString(0, 0, "Score: " + points, WHITE);
						oldPanda.row = panda.row;
						oldPanda.spd = panda.spd;
					} else {
						panda.spd = 1;
						panda.row = panda.row + panda.spd;
						drawRect(oldPanda.row, oldPanda.col, oldPanda.size, oldPanda.size, BLACK);
						drawImage3(panda.row, panda.col, panda.size, panda.size, face);
						//drawRect(panda.row, panda.col, panda.size, panda.size, WHITE);
						//drawString(0, 0, "Score: " + points, WHITE);
						oldPanda.row = panda.row;
						oldPanda.spd = panda.spd;
					}
					if(state == OVER){
						break;
					}
					if (KEY_DOWN_NOW(BUTTON_SELECT)) {
						state = START;
						break;
					}
				}

			break;

			case OVER:
				if (points > highestPoint) {
					highestPoint = points;
				}
				waitForVblank();
				drawImage3(0, 0, END_WIDTH, END_HEIGHT, end);
				drawString(150, 0, "High Score:", WHITE);
				drawChar(150, 70, 48 +highestPoint+0, WHITE);
				drawString(150, 130, "Press B to Start", WHITE);
				
				if (KEY_DOWN_NOW(BUTTON_B)) {
					for(int i = 0; i < NCOL; i++) {
						distR = random(5, 20);
						columnsTop[i].row = TOPROW;
						columnsTop[i].col = (i + 1) * 50 + distR;
						columnsTop[i].spd = SPEED;
						columnsTop[i].width = WIDTH;
						columnsTop[i].height = random(50, 70);
						columnsTop[i].color =  GREEN;

						botHeightR = random(90, 120);
						columnsBot[i].row = botHeightR;
						columnsBot[i].col = (i + 1) * 50 + distR;
						columnsBot[i].spd = SPEED;
						columnsBot[i].width = WIDTH;
						columnsBot[i].height = botHeightR;
						columnsBot[i].color = GREEN;

						oldColumnBot[i] = columnsBot[i];
						oldColumnTop[i] = columnsTop[i];
					}
					panda.row = 70;
					panda.col = 30;
					panda.spd = PSPD;
					panda.size = 10;
					oldPanda.row = panda.row;
					oldPanda.col = panda.col;
					oldPanda.spd = panda.spd;
					oldPanda.size = panda.size;
	
					state = START;
					break;
				}

				break;

			case RESET:
				drawRect(0, 0, 160, 240, BLACK);
				
				// for(int i = 0; i < NCOL; i++) {
				// 	struct column *columnT = &oldColumnTop[i];
				// 	drawRect(columnT->row, columnT->col, columnT->height, columnT->width, GREEN);
				// 	struct column *columnB = &oldColumnBot[i];
				// 	drawRect(columnB->row, columnB->col, columnB->height, columnB->width, GREEN);
				// }
				// drawImage3(panda.row, panda.col, panda.size, panda.size, face);
				drawRect(panda.row, panda.col, panda.size, panda.size, WHITE);
				points = 0;

				//drawString(70, 120, "Score: ", WHITE);
				drawString(80, 100, "Press up to Start", WHITE);
				if (KEY_DOWN_NOW(BUTTON_UP)) {
					drawString(80, 100, "Press up to Start", BLACK);
					state = GAME;
					break;
				}
				break;
	
		}		
		
	}


}