#include<pspkernel.h> 
#include<pspdebug.h>

#include"ClassGame.h"


PSP_MODULE_INFO("TrickyTowersPSP", 1, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main() {
	Game game;
	game.run();
	oslQuit();
}