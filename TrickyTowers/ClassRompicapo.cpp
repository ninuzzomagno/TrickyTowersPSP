#include"ClassLevel.h"

Rompicapo::~Rompicapo() {
	delete this->laser;
	delete this->base;
	delete this->background;
}

Rompicapo::Rompicapo(ResourceManager&res, DIFFICULTY diff) : Level(res,20.f) {
	if (diff == DIFFICULTY::RANDOM)
		diff = DIFFICULTY(int(rand() % 3));

	this->background = new BgRompicapo(res);

	this->base = new BaseRompicapo(*this->world, res, diff);

	this->laser = new Laser(*this->world);
	
	this->laserCollision = false;
}

PAUSA_STATUS Rompicapo::run() {

	float dt = 0.016f;
	timer_TimeManager timer;
	timer.timer_start();

	PAUSA_STATUS pS;

	while (!this->finish) {
		renderer.start(RGB(0, 0, 0));

		pS = this->menuPausa.update(timer);
		if (pS == PAUSA_STATUS::RESUME)
			this->update(dt);
		else if (pS != PAUSA_STATUS::PAUSED)
			this->finish = true;
		this->draw();
		this->menuPausa.draw(*this->controls);

		dt = renderer.end(timer);
	}
	return pS;
}

void Rompicapo::update(float dt) {
	this->updateBlocks(!this->laserCollision,300.f);
	this->updateWorld(dt);
	this->laserCollision = this->laser->update(this->block_deleted, dt);
	if (this->laserCollision) {
		this->startCount = true;
		this->finish=this->timer->update(dt);
	}
	else {
		this->startCount = false;
		this->timer->reset();
	}
	this->background->update(0, dt);
}

void Rompicapo::draw() {
	this->background->drawBack();
	this->laser->draw();
	this->drawBlock();
	this->base->draw();
	this->background->drawFront();
	if (this->startCount)
		this->timer->draw();
	this->drawNextBlock();
	this->drawRamStatus();
}