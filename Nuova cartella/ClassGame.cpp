#include"ClassGame.h"

Game::Game(){
	oslInit(0);
	oslInitAudioME(OSL_FMT_MP3);
	oslSetQuitOnLoadFailure(1);

	oslInitGfx(OSL_PF_5650, true);
	oslSetDithering(true);
	oslSetBilinearFilter(1);

	oslSetVSync(0);
	oslSetFramerate(60);
	oslIntraFontInit(INTRAFONT_CACHE_ALL);

	srand(time(NULL));

	this->res.loadFont("cartoon", "resource/font/cartoon.pgf");

	this->res.loadSound("menu_theme", "resource/sound/menu_theme.mp3", OSL_FMT_STREAM);
	this->res.loadSound("control_sound", "resource/sound/control_sound.mp3", OSL_FMT_STREAM);
	this->res.loadSound("collision", "resource/sound/collision_block.mp3", OSL_FMT_STREAM);
	this->res.loadSound("counter", "resource/sound/count_timer.mp3", OSL_FMT_STREAM);

	this->res.loadImage("box2d", "resource/splash/box2d.png", OSL_IN_RAM | OSL_SWIZZLED,OSL_PF_8888);
	this->res.loadImage("logo", "resource/logo.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("gara_background0", "resource/mode/gara/background0.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("gara_background1", "resource/mode/gara/background1.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("romp_background0", "resource/mode/rompicapo/background0.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("romp_background1", "resource/mode/rompicapo/background1.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("sopr_background0", "resource/mode/sopravvivenza/background0.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("sopr_background1", "resource/mode/sopravvivenza/background1.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("next", "resource/blocks/next.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("nuvole", "resource/mode/p_sky.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("menu", "resource/menu/menu.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("controls", "resource/control/controls.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("base", "resource/mode/gara/base.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("mode", "resource/splash/select_mode.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("vita", "resource/mode/sopravvivenza/heart.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	this->res.loadImage("l1", "resource/blocks/l1.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("l2", "resource/blocks/l2.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("zd", "resource/blocks/zd.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("zs", "resource/blocks/zs.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("r", "resource/blocks/r.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("q", "resource/blocks/q.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);
	this->res.loadImage("p", "resource/blocks/p.png", OSL_IN_VRAM | OSL_SWIZZLED, OSL_PF_8888);

	oslSetFont(this->res.getFont("cartoon"));
}

void Game::splashScreen() {

	box2dSplashScreen();
	oslShowSplashScreen1();
	mySplash();
	
}

void Game::run() {

	this->splashScreen();

	playData data;
	data.diff = DIFFICULTY::EASY;
	data.num = 1;
	data.tipo = PARTITA::GARA;

	bool init = true;
	bool backToMenu = true;
	while (true) {

		if (backToMenu) {
			this->mainMenu(init);
			init = false;
		}
		backToMenu = this->torneoMenu(data) == 1 ? false : true;
		if(!backToMenu)
			this->play(data);
	}
}

void Game::play(playData&data) {

	PAUSA_STATUS pS = PAUSA_STATUS::RESUME;

	while (data.num > 0) {

		PARTITA tipo = data.tipo;

		if (tipo == PARTITA::RANDOM)
			tipo = PARTITA(int(rand() % 3));

		do {
			if (tipo == PARTITA::GARA) {
				Gara gara(this->res, data.diff);
				pS = gara.run();
			}
			else if (tipo == PARTITA::ROMPICAPO) {
				Rompicapo rompicapo(this->res, data.diff);
				pS = rompicapo.run();
			}
			else if (tipo == PARTITA::SOPRAVVIVENZA) {
				Sopravvivenza sopravvivenza(this->res, data.diff);
				pS = sopravvivenza.run();
			}

			if (pS == PAUSA_STATUS::QUIT)
				return;
		}
		while (pS == PAUSA_STATUS::RESTART);

		data.num -= 1;
	}
}

void Game::mainMenu(bool init) {

	int size = 1, SIZE = 32;

	OSL_IMAGE* scura = nullptr;

	if (init) {
		scura = oslCreateImage(480, 272, OSL_IN_RAM, OSL_PF_8888);
		oslClearImage(scura, RGBA(0, 0, 0, 255));
	}
	int alpha = 255;

	GaraCloud cloud(10, this->res.getImage("nuvole"));
	Controls controls(res);

	bool exit = false;

	float dt = 0.016f;
	timer_TimeManager timer;
	timer.timer_start();

	float pos_x = 0.f;

	oslPlaySound(this->res.getSound("menu_theme"), 1);

	OSL_IMAGE* back1 = this->res.getImage("gara_background1");

	int scelta = 0;

	int statoMenu = init ? 0 : 1;

	while (!exit) {
		this->renderer.start(RGB(0, 0, 0));

		pos_x += 50 * dt;
		if (pos_x > 480)
			pos_x = 0;

		switch (statoMenu) {
		case 0:
			if (this->updatePageInitMenu(alpha, size, SIZE, dt))
				statoMenu++;
			break;
		case 1:
			statoMenu = this->updatePageMainMenu(scelta);
			break;
		case 2:
			exit = true;
			statoMenu = 1;
			break;
		case 3:
			statoMenu = this->updatePageControlsMenu() ? 1 : 3;
			break;
		case 4:
			statoMenu = this->updatePageCreditsMenu() ? 1 : 4;
			break;
		}

		cloud.update(dt);

		oslDrawImage(this->res.getImage("gara_background0"));
		oslSetImageTile(back1, 0, 24, 480, 203);
		oslDrawImageXY(back1, 0, 92);
		oslSetImageTile(back1, 0, 0, 480, 24);
		oslDrawImageXY(back1, pos_x, 249);
		oslDrawImageXY(back1, pos_x-480, 249);

		cloud.draw();

		switch (statoMenu) {
		case 0:
			this->drawPageInitMenu(controls, alpha, SIZE, scura);
			break;
		case 1:
			this->drawPageMainMenu(controls,scelta);
			break;
		case 3:
			this->drawPageControlsMenu(controls);
			break;
		case 4:
			this->drawPageCreditsMenu(controls);
			break;
		}

		dt = this->renderer.end(timer);
	}

	oslDeleteImage(scura);

}

bool Game::updatePageControlsMenu() {
	if (osl_pad.pressed.circle)
		return true;
	return false;
}

bool Game::updatePageCreditsMenu() {
	if (osl_pad.pressed.circle)
		return true;
	return false;
}

void Game::drawPageCreditsMenu(Controls& ctrl) {

	oslIntraFontSetStyle(this->res.getFont("cartoon"), 0.6, RGB(255, 137, 0), RGB(255, 137, 0), INTRAFONT_ALIGN_CENTER);
	
	oslDrawFillRect(50, 46, 430, 196, RGB(255, 255, 255));
	oslDrawString(240, 66, "Author : Ninuzzomagno");
	oslDrawString(240, 106, "Almost all of the assets used in this");
	oslDrawString(240, 126, "project are from the original game");
	oslDrawString(240, 166, "Physic library : Box2D by Enricatto");

	oslIntraFontSetStyle(this->res.getFont("cartoon"), 1, RGB(255, 137, 0), RGB(255, 137, 0), INTRAFONT_ALIGN_CENTER);
	oslDrawFillRect(0, 240, 120, 272, RGB(255, 255, 255));
	ctrl.draw(TASTI::CIRCLE, 100, 257, 20, 20);
	oslDrawString(50, 252, "Back");
}

void Game::drawPageControlsMenu(Controls&ctrl) {
	oslDrawString(120, 50, "Shift block");
	ctrl.draw(TASTI::L, 300, 50, 31, 17);
	ctrl.draw(TASTI::R, 400, 50, 31, 17);

	oslDrawString(120, 100, "Rotate block");
	ctrl.draw(TASTI::UP, 350, 100, 20, 20);

	oslDrawString(120, 150, "Move block");
	ctrl.draw(TASTI::LEFT, 300, 150, 20, 20);
	ctrl.draw(TASTI::RIGHT, 400, 150, 20, 20);

	oslDrawFillRect(0, 240, 120, 272, RGB(255, 255, 255));
	ctrl.draw(TASTI::CIRCLE, 100, 257, 20, 20);
	oslDrawString(50, 252, "Back");
}

int Game::updatePageMainMenu(int&scelta) {
	if (osl_pad.pressed.up && scelta > 0)
		scelta--;
	else if (osl_pad.pressed.down && scelta < 2)
		scelta++;
	else if (osl_pad.pressed.cross)
		return scelta + 2;
	return 1;
}

void Game::drawPageMainMenu(Controls&ctrl,int scelta) {
	oslDrawFillRect(100, 70 + 36 * scelta, 380, 100 + 36 * scelta, RGB(255, 255, 255));
	oslDrawString(240, 80, "Play");
	oslDrawString(240, 116, "Controls");
	oslDrawString(240, 152, "Credits");
	
	oslDrawFillRect(308, 240, 480, 272, RGB(255, 255, 255));
	ctrl.draw(TASTI::CROSS, 330, 257, 20, 20);
	oslDrawString(410, 252, "Confirme");

}

void Game::drawPageInitMenu(Controls& controls, int& alpha, int SIZE, OSL_IMAGE* scura) {
	oslDrawImageXY(this->res.getImage("logo"), 157, 70);
	oslIntraFontSetStyle(this->res.getFont("cartoon"), 1, RGB(255, 137, 0), RGB(255, 137, 0), INTRAFONT_ALIGN_CENTER);
	oslDrawStringf(240, 220, "Premere     per continuare");
	controls.draw(TASTI::CROSS, 189, 224, SIZE, SIZE);

	if (alpha > 0) {
		alpha -= 3;
		oslClearImage(scura, RGBA(0, 0, 0, alpha));
		oslDrawImage(scura);
	}
}

bool Game::updatePageInitMenu(int& alpha, int& size, int& SIZE, float dt) {
	if (osl_pad.pressed.cross) {
		if (alpha > 0)
			alpha = 0;
		else
			return true;
	}

	if (SIZE == 10 || SIZE == 32)
		size = -size;
	SIZE += size;

	return false;
}

int Game::torneoMenu(playData&data) {

	int sel_X = 0, size_L = 20, size_R = 20, size_T = 20, size_D = 20;

	Controls control(this->res);

	RompicapoMeteor meteor(3, this->res.getImage("nuvole"));

	oslSetImageTile(this->res.getImage("next"), 62, 0, 262, 23);
	OSL_IMAGE* back1 = this->res.getImage("romp_background1");
	
	int sel_Y[3] = { 0,0,0 };

	int exit = 0;

	float pos_x = 0.f;

	float dt = 0.016;
	timer_TimeManager timer;
	timer.timer_start();

	while (exit==0) {
		this->renderer.start(RGB(0, 0, 0));

		if (osl_pad.pressed.cross) {
			exit = 1;
			data.diff = DIFFICULTY(sel_Y[1]);
			data.tipo = PARTITA(sel_Y[0]);
			data.num = sel_Y[2] + (sel_Y[2] + 1);
			this->renderer.end(timer);
		}
		else if (osl_pad.pressed.circle) {
			exit = -1;
			this->renderer.end(timer);
		}

		this->updateScelteTorneo(sel_X, size_L, size_R, size_T, size_D, sel_Y);

		meteor.update(dt);		

		pos_x += 50 * dt;
		if (pos_x > 480)
			pos_x = 0;

		oslDrawImage(this->res.getImage("romp_background0"));
		meteor.draw();
		oslSetImageTile(back1, 0, 24, 480, 170);
		oslDrawImageXY(back1, 0, 120);
		oslSetImageTile(back1, 0, 0, 480, 24);
		oslDrawImageXY(back1, pos_x, 248);
		oslDrawImageXY(back1, pos_x-480, 248);

		this->drawScelteTorneo(sel_X, size_L, size_R, size_T, size_D, sel_Y);

		oslDrawImageXY(this->res.getImage("next"), 140, 0);

		control.draw(TASTI::UP, 90 + 150 * sel_X, 56, size_T, size_T);
		control.draw(TASTI::RIGHT, 170 + 150 * sel_X, 136, size_R, size_R);
		control.draw(TASTI::DOWN, 90 + 150 * sel_X, 216, size_D, size_D);
		control.draw(TASTI::LEFT, 10 + 150 * sel_X, 136, size_L, size_L);

		oslDrawFillRect(0, 240, 120, 272, RGB(255, 255, 255));
		control.draw(TASTI::CIRCLE, 100, 257, 20, 20);
		oslDrawString(50, 252, "Back");

		oslDrawFillRect(308, 240, 480, 272, RGB(255, 255, 255));
		control.draw(TASTI::CROSS, 330, 257, 20, 20);
		oslDrawString(410, 252, "Continue");

		dt = this->renderer.end(timer);
	}
	back1 = nullptr;
	return exit;
}

void Game::box2dSplashScreen() {

	b2World* world = new b2World(b2Vec2(0.f, 10.f));

	OSL_IMAGE* box2d = this->res.getImage("box2d");

	struct frame_coord{ int x,y,w,h; }frame_lettera[5];

	b2Body* lettere[5];

	frame_lettera[0].x = 123;
	frame_lettera[0].y = 0;
	frame_lettera[0].w = 154;
	frame_lettera[0].h = 50;

	frame_lettera[1].x = 161;
	frame_lettera[1].y = 13;
	frame_lettera[1].w = 196;
	frame_lettera[1].h = 50;

	frame_lettera[2].x = 198;
	frame_lettera[2].y = 12;
	frame_lettera[2].w = 229;
	frame_lettera[2].h = 50;

	frame_lettera[3].x = 234;
	frame_lettera[3].y = 0;
	frame_lettera[3].w = 263;
	frame_lettera[3].h = 50;

	frame_lettera[4].x = 272;
	frame_lettera[4].y = 0;
	frame_lettera[4].w = 312;
	frame_lettera[4].h = 50;
	
	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.gravityScale = 1.f;
	bDef.enabled = true;
	
	for (int i = 0; i < 5; i++) {
		bDef.position.Set((200.f + 50 * i) / SCALE, 80.f / SCALE);
		lettere[i] = world->CreateBody(&bDef);
	}

	b2FixtureDef fDef;
	fDef.restitution = 0.5;
	fDef.density = 1.f;
	
	b2PolygonShape shapeP;
	
	b2CircleShape circle;
	circle.m_radius = 18.f / SCALE;

	fDef.shape = &circle;
	lettere[1]->CreateFixture(&fDef);

	for (int i = 0; i < 5; i++) {
		if (i != 1) {
			shapeP.SetAsBox((frame_lettera[i].w - frame_lettera[i].x) / 2.f / SCALE, (frame_lettera[i].h - frame_lettera[i].y) / 2.f / SCALE);
			fDef.shape = &shapeP;
			lettere[i]->CreateFixture(&fDef);
		}
	}

	b2Body* floor;
	bDef.type = b2_staticBody;
	bDef.position.Set(240.f / SCALE, 262.f / SCALE);

	shapeP.SetAsBox(240.f / SCALE, 10.f / SCALE);
	fDef.shape = &shapeP;
	floor = world->CreateBody(&bDef);
	floor->CreateFixture(&fDef);

	float accumulator = 0.f;
	float dt = 0.016f;
	timer_TimeManager timer;
	timer.timer_start();

	float wait = 5.f;

	while (wait>0) {
		this->renderer.start(RGB(255, 255, 255));

		if (osl_pad.pressed.cross || osl_pad.pressed.start)
			wait=0;

		accumulator += dt;
		while (accumulator > 0.f) {
			world->Step(0.016f, 8, 3);
			accumulator -= dt;
		}

		oslSetImageTile(box2d,0,0,123,136);
		oslDrawImageXY(box2d, 50, 68);

		for (int i = 0; i < 5; i++) {
			b2Vec2 pos = lettere[i]->GetPosition();
			pos.y *= SCALE;
			pos.x *= SCALE;

			float angle = lettere[i]->GetAngle() * 180.f / b2_pi;

			oslSetImageTile(box2d, frame_lettera[i].x, frame_lettera[i].y, frame_lettera[i].w, frame_lettera[i].h);
			oslImageRotMoveX(box2d, (frame_lettera[i].w - frame_lettera[i].x) / 2);
			oslImageRotMoveY(box2d, (frame_lettera[i].h - frame_lettera[i].y) / 2);
			oslSetImageRotCenter(box2d);
			box2d->angle = angle;
			oslDrawImageXY(box2d, pos.x, pos.y);
		}

		oslDrawFillRect(0, 252, 480, 272, RGB(255, 0, 0));

		dt = this->renderer.end(timer);
		wait -= dt;
	}

	box2d = nullptr;
	this->res.deleteImage("box2d");
	delete world;
}

void Game::mySplash() {
	OSL_IMAGE* scura = oslCreateImage(480, 272, OSL_IN_RAM, OSL_PF_8888);
	oslIntraFontSetStyle(this->res.getFont("cartoon"), 0.6, RGB(255, 255, 255), RGB(255, 137, 0), INTRAFONT_ALIGN_CENTER);

	timer_TimeManager timer;

	int alpha = 255;
	float time = 7;
	timer.timer_start();

	float dt = 0.016;

	while (time > 0) {
		this->renderer.start(RGB(0, 0, 0));

		if (osl_pad.pressed.cross || osl_pad.pressed.start)
			time=0;

		oslDrawString(240, 86, "The product was made without any profit. It is");
		oslDrawString(240, 106, "simply an attempt to bring the famous game");
		oslDrawString(240, 126, "Tricky Towers(officially available on PS4, SWITCH");
		oslDrawString(240, 146, "STEAM and XBOX ONE) to an equally famous old");
		oslDrawString(240, 166, "console. I hope you appreciate my work and if so,");
		oslDrawString(240, 186, "I invite you to purchase the official game :)");

		if (alpha > 0)
			alpha -= 3;
		oslClearImage(scura, RGBA(0, 0, 0, alpha));
		oslDrawImage(scura);

		dt = this->renderer.end(timer);
		time -= dt;
	}

	oslDeleteImage(scura);
}

void Game::updateScelteTorneo(int& sel_X, int& size_L, int& size_R, int& size_T, int& size_D, int* sel_Y) {
	if (osl_pad.pressed.right) {
		oslPlaySound(this->res.getSound("control_sound"), 7);
		if (sel_X == 2)
			sel_X = 0;
		else
			sel_X++;
		size_R = 30;
		size_L = size_T = size_D = 20;
	}
	else if (osl_pad.pressed.left) {
		oslPlaySound(this->res.getSound("control_sound"), 7);
		if (sel_X == 0)
			sel_X = 2;
		else
			sel_X--;
		size_L = 30;
		size_R = size_T = size_D = 20;
	}
	else if (osl_pad.pressed.up) {
		oslPlaySound(this->res.getSound("control_sound"), 7);
		if (sel_Y[sel_X] == 3)
			sel_Y[sel_X] = 0;
		else
			sel_Y[sel_X]++;
		size_T = 30;
		size_L = size_R = size_D = 20;
	}
	else if (osl_pad.pressed.down) {
		oslPlaySound(this->res.getSound("control_sound"), 7);
		if (sel_Y[sel_X] == 0)
			sel_Y[sel_X] = 3;
		else
			sel_Y[sel_X]--;
		size_D = 30;
		size_L = size_T = size_R = 20;
	}
	else
		size_T = size_D = size_R = size_L = 20;
}

void Game::drawScelteTorneo(int& sel_X, int& size_L, int& size_R, int& size_T, int& size_D,int*sel_Y) {
	////////////////////////////////////////////////////////

	oslSetImageTile(this->res.getImage("mode"), 120 * sel_Y[0], 0, 120 * (1 + sel_Y[0]), 120);
	oslImageRotMoveX(this->res.getImage("mode"), 60);
	oslImageRotMoveY(this->res.getImage("mode"), 60);
	oslSetImageRotCenter(this->res.getImage("mode"));
	if (sel_X == 0) {
		this->res.getImage("mode")->stretchX = 120;
		this->res.getImage("mode")->stretchY = 120;
		oslDrawImageXY(this->res.getImage("mode"), 90, 136);

		oslSetImageTile(this->res.getImage("mode"), 120 * (sel_Y[0] == 3 ? 0 : sel_Y[0] + 1), 0, 120 * (1 + (sel_Y[0] == 3 ? 0 : sel_Y[0] + 1)), 120);
		oslImageRotMoveX(this->res.getImage("mode"), 60);
		oslImageRotMoveY(this->res.getImage("mode"), 60);
		oslSetImageRotCenter(this->res.getImage("mode"));
		this->res.getImage("mode")->stretchX = 80;
		this->res.getImage("mode")->stretchY = 80;
		oslDrawImageXY(this->res.getImage("mode"), 90, 0);

		oslSetImageTile(this->res.getImage("mode"), 120 * (sel_Y[0] == 0 ? 3 : sel_Y[0] - 1), 0, 120 * (1 + (sel_Y[0] == 0 ? 3 : sel_Y[0] - 1)), 120);
		oslImageRotMoveX(this->res.getImage("mode"), 60);
		oslImageRotMoveY(this->res.getImage("mode"), 60);
		oslSetImageRotCenter(this->res.getImage("mode"));
		this->res.getImage("mode")->stretchX = 80;
		this->res.getImage("mode")->stretchY = 80;
		oslDrawImageXY(this->res.getImage("mode"), 90, 272);

	}
	else {
		this->res.getImage("mode")->stretchX = 100;
		this->res.getImage("mode")->stretchY = 100;
		oslDrawImageXY(this->res.getImage("mode"), 90, 136);
	}

	////////////////////////////////////////////////////////

	oslSetImageTile(this->res.getImage("mode"), 120 * sel_Y[1], 120, 120 * (1 + sel_Y[1]), 240);
	oslImageRotMoveX(this->res.getImage("mode"), 60);
	oslImageRotMoveY(this->res.getImage("mode"), 60);
	oslSetImageRotCenter(this->res.getImage("mode"));
	if (sel_X == 1) {
		this->res.getImage("mode")->stretchX = 120;
		this->res.getImage("mode")->stretchY = 120;
		oslDrawImageXY(this->res.getImage("mode"), 240, 136);

		oslSetImageTile(this->res.getImage("mode"), 120 * (sel_Y[1] == 3 ? 0 : sel_Y[1] + 1), 120, 120 * (1 + (sel_Y[1] == 3 ? 0 : sel_Y[1] + 1)), 240);
		oslImageRotMoveX(this->res.getImage("mode"), 60);
		oslImageRotMoveY(this->res.getImage("mode"), 60);
		oslSetImageRotCenter(this->res.getImage("mode"));
		this->res.getImage("mode")->stretchX = 80;
		this->res.getImage("mode")->stretchY = 80;
		oslDrawImageXY(this->res.getImage("mode"), 240, 0);

		oslSetImageTile(this->res.getImage("mode"), 120 * (sel_Y[1] == 0 ? 3 : sel_Y[1] - 1), 120, 120 * (1 + (sel_Y[1] == 0 ? 3 : sel_Y[1] - 1)), 240);
		oslImageRotMoveX(this->res.getImage("mode"), 60);
		oslImageRotMoveY(this->res.getImage("mode"), 60);
		oslSetImageRotCenter(this->res.getImage("mode"));
		this->res.getImage("mode")->stretchX = 80;
		this->res.getImage("mode")->stretchY = 80;
		oslDrawImageXY(this->res.getImage("mode"), 240, 272);

	}
	else {
		this->res.getImage("mode")->stretchX = 100;
		this->res.getImage("mode")->stretchY = 100;
		oslDrawImageXY(this->res.getImage("mode"), 240, 136);
	}

	////////////////////////////////////////////////////////

	oslSetImageTile(this->res.getImage("mode"), 120 * sel_Y[2], 240, 120 * (1 + sel_Y[2]), 360);
	oslImageRotMoveX(this->res.getImage("mode"), 60);
	oslImageRotMoveY(this->res.getImage("mode"), 60);
	oslSetImageRotCenter(this->res.getImage("mode"));
	if (sel_X == 2) {
		this->res.getImage("mode")->stretchX = 120;
		this->res.getImage("mode")->stretchY = 120;
		oslDrawImageXY(this->res.getImage("mode"), 390, 136);

		oslSetImageTile(this->res.getImage("mode"), 120 * (sel_Y[2] == 3 ? 0 : sel_Y[2] + 1), 240, 120 * (1 + (sel_Y[2] == 3 ? 0 : sel_Y[2] + 1)), 360);
		oslImageRotMoveX(this->res.getImage("mode"), 60);
		oslImageRotMoveY(this->res.getImage("mode"), 60);
		oslSetImageRotCenter(this->res.getImage("mode"));
		this->res.getImage("mode")->stretchX = 80;
		this->res.getImage("mode")->stretchY = 80;
		oslDrawImageXY(this->res.getImage("mode"), 390, 0);

		oslSetImageTile(this->res.getImage("mode"), 120 * (sel_Y[2] == 0 ? 3 : sel_Y[2] - 1), 240, 120 * (1 + (sel_Y[2] == 0 ? 3 : sel_Y[2] - 1)), 360);
		oslImageRotMoveX(this->res.getImage("mode"), 60);
		oslImageRotMoveY(this->res.getImage("mode"), 60);
		oslSetImageRotCenter(this->res.getImage("mode"));
		this->res.getImage("mode")->stretchX = 80;
		this->res.getImage("mode")->stretchY = 80;
		oslDrawImageXY(this->res.getImage("mode"), 390, 272);

	}
	else {
		this->res.getImage("mode")->stretchX = 100;
		this->res.getImage("mode")->stretchY = 100;
		oslDrawImageXY(this->res.getImage("mode"), 390, 136);
	}

	///////////////////////////////////////////////////////////
}