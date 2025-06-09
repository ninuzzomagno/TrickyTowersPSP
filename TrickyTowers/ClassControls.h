#pragma once

#include<oslib/oslib.h>
#include"ClassResourceManager.h"

enum class TASTI { CROSS, SQUARE, TRIANGLE, CIRCLE, UP, DOWN, LEFT, RIGHT, L, R };

class Controls {
public:
	Controls(ResourceManager&);
	~Controls();
	void draw(TASTI, int, int, int, int);
private:
	OSL_IMAGE* texture;
};
