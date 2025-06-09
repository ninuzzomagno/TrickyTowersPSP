#pragma once
#include<oslib/oslib.h>

class Draw {
public:
	//RECT

	//x,y,w,h,color
	static void fillRect(int, int, int, int, OSL_COLOR);
	//x,y,w,h,color
	static void fillRect(int*, int*, int*, int*, OSL_COLOR);
	//x,y,w,h,color
	static void rect(int, int, int, int, OSL_COLOR);
	//x,y,w,h,color
	static void rect(int*, int*, int*, int*, OSL_COLOR);
	//x,y,w,h,cTL,cTR,cBL,cBR
	static void gradientRect(int, int, int, int, OSL_COLOR, OSL_COLOR, OSL_COLOR, OSL_COLOR);
	//x,y,w,h,cTL,cTR,cBL,cBR
	static void gradientRect(int*, int*, int*, int*, OSL_COLOR, OSL_COLOR, OSL_COLOR, OSL_COLOR);
	//LINE

	//x,y,w,h,color
	static void line(int*, int*, int*, int*, OSL_COLOR);
	//x,y,w,h,color
	static void line(int, int, int, int, OSL_COLOR);
};