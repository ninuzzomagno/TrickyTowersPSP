#include"ClassLevel.h"

Gara::~Gara() {
	delete this->flag;
	delete this->base;
	delete this->background;
}

Gara::Gara(ResourceManager&res,DIFFICULTY diff) : Level(res,160.f){
	if (diff == DIFFICULTY::RANDOM)
		diff = DIFFICULTY(int(rand() % 3));

	this->background = new BgGara(res);
	this->base = new BaseGara(*this->world, res, diff);
	this->flag = new Flag(*this->world, diff);
}

PAUSA_STATUS Gara::run() {

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

void Gara::update(float dt) {
	this->updateBlocks(true,this->base->getY()+100.f);
	this->updateWorld(dt);

	int y = this->base->getY();

	this->background->update(y,dt);
	this->startCount = this->flag->update(y, dt);
	if (this->startCount)
		this->finish = this->timer->update(dt);
	else
		this->timer->reset();
}

void Gara::draw() {
	this->background->drawBack();
	this->flag->draw();
	this->drawBlock();
	this->base->draw();
	this->background->drawFront();
	if (this->startCount)
		this->timer->draw();
	this->drawNextBlock();
	this->drawRamStatus();
}
