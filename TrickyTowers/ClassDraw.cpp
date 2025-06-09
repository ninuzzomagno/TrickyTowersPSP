#include"ClassDraw.h"
#include<math.h>



void Draw::gradientRect(int pos_x, int pos_y, int w, int h, OSL_COLOR colorTL, OSL_COLOR colorTR, OSL_COLOR colorBL, OSL_COLOR colorBR) {
	oslDrawGradientRect(pos_x, pos_y, pos_x + w, pos_y + h, colorTL, colorTR, colorBL, colorBR);
}

void Draw::gradientRect(int* pos_x, int* pos_y, int* w, int* h, OSL_COLOR colorTL, OSL_COLOR colorTR, OSL_COLOR colorBL, OSL_COLOR colorBR) {
	oslDrawGradientRect(*pos_x, *pos_y, *pos_x + *w, *pos_y + *h, colorTL, colorTR, colorBL, colorBR);
}

void Draw::fillRect(int pos_x, int pos_y, int w, int h, OSL_COLOR color) {
	oslDrawFillRect(pos_x, pos_y, pos_x + w, pos_y + h, color);
}

void Draw::fillRect(int* pos_x, int* pos_y, int* w, int* h, OSL_COLOR color) {
	oslDrawFillRect(*pos_x, *pos_y, *pos_x + *w, *pos_y + *h, color);
}

void Draw::rect(int pos_x, int pos_y, int w, int h, OSL_COLOR color) {
	oslDrawRect(pos_x, pos_y, pos_x + w, pos_y + h, color);
}

void Draw::rect(int* pos_x, int* pos_y, int* w, int* h, OSL_COLOR color) {
	oslDrawRect(*pos_x, *pos_y, *pos_x + *w, *pos_y + *h, color);
}

void Draw::line(int pos_x, int pos_y, int w, int h, OSL_COLOR color) {
	oslDrawLine(pos_x, pos_y, pos_x + w, pos_y + h, color);
}

void Draw::line(int* pos_x, int* pos_y, int* w, int* h, OSL_COLOR color) {
	oslDrawLine(*pos_x, *pos_y, *pos_x + *w, *pos_y + *h, color);
}

