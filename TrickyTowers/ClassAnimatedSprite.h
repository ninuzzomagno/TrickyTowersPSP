#pragma once

#include<string>
#include<fstream>
#include<oslib/oslib.h>

struct frame {
	int x, y, w, h;
};

class AnimatedSprite {
public:
	AnimatedSprite(OSL_IMAGE*, std::string);
	~AnimatedSprite();
protected:
	void updateSprite(float);
	void drawSprite(int, int);
private:
	frame** frames;
	OSL_IMAGE* texture;
	int currentFRAME_index, maxFrame, iniFrame;
	float wait, defWait;
};
