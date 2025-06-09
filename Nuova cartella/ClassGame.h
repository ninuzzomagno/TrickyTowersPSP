#pragma once

#include<oslib/oslib.h>

#include"timeManager.h"

#include"ClassResourceManager.h"
#include"ClassRenderer.h"
#include"ClassLevel.h"
#include"ClassControls.h"

struct playData {
	DIFFICULTY diff;
	PARTITA tipo;
	int num;
};

class Game {
public:
	Game();
	void run();
private:
	int torneoMenu(playData&);
	void splashScreen();
	void mainMenu(bool);
	void box2dSplashScreen();
	void mySplash();

	void play(playData&);

	void drawScelteTorneo(int&, int&, int&, int&, int&, int*);
	void updateScelteTorneo(int&, int&, int&, int&, int&, int*);

	void drawPageInitMenu(Controls&, int&, int, OSL_IMAGE*);
	bool updatePageInitMenu(int&, int&, int&, float);

	int updatePageMainMenu(int&);
	void drawPageMainMenu(Controls&,int);

	bool updatePageControlsMenu();
	void drawPageControlsMenu(Controls&);

	bool updatePageCreditsMenu();
	void drawPageCreditsMenu(Controls&);

	ResourceManager res;

	Renderer renderer;
};
