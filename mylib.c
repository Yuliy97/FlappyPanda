#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mylib.h"
#include "DMA.h"


unsigned short* videoBuffer =  (unsigned short *)0x6000000;


// setPixel -- set the pixel at (row, col) to color
void setPixel(int row, int col, unsigned short color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color) {
	for(int r=0; r<height; r++) {
	/*	for(int c = 0; c<width; c++) {
			setPixel(row+r, col+c, color);
		}
	*/
	DMA[3].src = &color;
	//DMA[3].dst = videoBuffer + (r + row) * 240 + col;
	DMA[3].dst = &videoBuffer[OFFSET(row + r, col, 240)];
	DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}
void drawImage3 (int r, int c, int width, int height, const u16* image) {
	for (int row = 0; row < height; row++) {
		DMA[3].src = &image[(row) * width];
		DMA[3].dst = &videoBuffer[(r + row) * 240 + c];;
		DMA[3].cnt = DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | width | DMA_ON;
	}	
}
int random(int min, int max) {
	return (rand() % (max - min)) + min;
}

void delay(int n) {
	volatile int x = 0;
	for(int i=0; i<n*8000; i++) {
		x++;
	}
}

void waitForVblank() {
	while(SCANLINECOUNTER > 160)
		;
	while(SCANLINECOUNTER<160)
		;
}
void drawChar(int row, int col, char ch, u16 color) {
	for(int r = 0; r < 8; r++) {
		for (int c = 0; c < 6; c++) {
			if (fontdata_6x8[OFFSET(r, c, 6) + ch*48]) {
				setPixel(row + r, col + c, color);
			}
		}
	}
}
void drawString(int row, int col, char *str, u16 color) {
	while(*str) {
		drawChar(row, col, *str++, color);
		col += 6;
	}
}
