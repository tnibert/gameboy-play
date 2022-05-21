#include "Intellisense.h"
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t         u8;
typedef int8_t          s8;
typedef uint16_t        u16;
typedef int16_t         s16;
typedef uint32_t        u32;
typedef int32_t         s32;

//\ Volatile variables
//\ The volatile key word indicates to the compiler, and the programmer. That these variables may have their values
//\ altered by an external factor, this could be a hardware switch, or some external program that can access the 
//\ memory location of the variable.
//\===========================================================================================================
typedef volatile uint8_t                vu8;
typedef volatile int8_t                 vs8;
typedef volatile uint16_t               vu16;
typedef volatile int16_t                vs16;
typedef volatile uint32_t               vu32;
typedef volatile int32_t                vs32;


#define REG_DISPCNT *((vu32*)(0x04000000))
#define VIDEOMODE_3 0x0003
#define BG_ENABLE2 0x0400

#define SCREENBUFFER ((vu16*)(0x06000000))
#define SCREEN_W 240
#define SCREEN_H 160

u16 setColor(u8 red, u8 green, u8 blue) {
	return (red & 0x1F) | (green & 0x1F) << 5 | (blue & 0x1F) << 10;
}

void plotPixel(s32 x, s32 y, u16 color) {
	SCREENBUFFER[y * SCREEN_W + x] = color;
}

void drawRect(s32 left, s32 top, s32 width, s32 height, u16 color) {
	for(s32 y = 0; y < height; ++y) {
		for(s32 x = 0; x < width; ++x) {
			plotPixel(left + x, top + y, color);
		}
	}
}

void testScreenFrame(s32 t) {
	s32 x,y;
	for(x = 0; x < SCREEN_W; ++x){
		for( y = 0; y < SCREEN_H; ++y){
			plotPixel(x, y, setColor((x&y)+t*5, (x&y)+t*3, (x&y)+t));
		}
	}
}

int main()
{
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPCNT = VIDEOMODE_3 | BG_ENABLE2;

	s32 t = 0;
	while(1){
		testScreenFrame(t);
		++t;
	}
	return 0;
}