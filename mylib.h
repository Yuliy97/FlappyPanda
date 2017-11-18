#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define OFFSET(r, c, rowlen) ((c) + (rowlen)*(r)) 
#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define WHITE COLOR(31,31,31)
#define RED COLOR(31, 0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK 0

#define NCOL 5
#define SPEED 1
#define WIDTH 20
#define TOPROW 0
#define PSPD -2


#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130

#define SCANLINECOUNTER *(volatile short *)0x4000006
extern const unsigned char fontdata_6x8[12288];
extern unsigned short *videoBuffer;
typedef unsigned short u16;
// typedef struct ball {
// 	int row;
// 	int col;
// 	int rd;
// 	int cd;
// 	int size;
// 	unsigned short color;
// } BALL;

typedef struct panda {
	int row;
	int col;
	int spd;
	int size;
	//unsigned short color;
} PANDA;

typedef struct column {
	int row;
	int col;
	int spd;
	int width;
	int height;
	unsigned short color;
} COLUMN;
// Prototypes
void setPixel(int row, int col, unsigned short );
void drawRect(int row, int col, int height, int width, unsigned short color);
void delay(int n);
void waitForVblank();
void drawImage3 (int r, int c, int width, int height, const u16* image);
int rand();
int snfprintf(char* s, size_t n, const char * format, ...);
void* malloc (size_t size);
int random(int min, int max);
void drawChar(int row, int col, char ch, u16 color);
void drawString(int row, int col, char *str, u16 color);