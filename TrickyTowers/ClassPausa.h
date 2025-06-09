#pragma once

#include<oslib/oslib.h>
#include"ClassControls.h"
#include"timeManager.h"

enum class PAUSA_STATUS{ PAUSED, RESUME, RESTART, QUIT };

class MenuPausa {
public:
	MenuPausa();
	PAUSA_STATUS update(timer_TimeManager&);
	void draw(Controls&);
private:
	int hoverIndex;
	PAUSA_STATUS pS;
};
