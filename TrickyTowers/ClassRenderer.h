#pragma once

#include<oslib/oslib.h>
#include"timeManager.h"

class Renderer {
public:
	Renderer();
	void start(const OSL_COLOR&);
	float end(timer_TimeManager&);
private:
	int currentFrame;
	int lastFrame;
};

