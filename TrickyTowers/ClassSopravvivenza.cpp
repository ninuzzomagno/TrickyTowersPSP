#include"ClassLevel.h"

Sopravvivenza::Sopravvivenza(ResourceManager& res, DIFFICULTY diff) :Level(res, 160.f) {
	if (diff == DIFFICULTY::RANDOM)
		diff = DIFFICULTY(int(rand() % 3));

	switch (diff) {
	case DIFFICULTY::EASY:
		this->num_block = 20;
		break;
	case DIFFICULTY::NORMAL:
		this->num_block = 40;
		break;
	case DIFFICULTY::HARD:
		this->num_block = 40;
		break;
	}

	this->base = new BaseSopravvivenza(*this->world, res);
	this->background = new BgSopravvivenza(res);
	this->hearts = new Hearts(res);
}

Sopravvivenza::~Sopravvivenza() {
	delete this->base;
	delete this->background;
	delete this->hearts;
}

PAUSA_STATUS Sopravvivenza::run() {

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

void Sopravvivenza::update(float dt) {
	this->updateBlocks(!this->startCount, this->base->getY() + 100.f);
	this->updateWorld(dt);
	this->startCount = this->hearts->update(dt,this->block_deleted);
	if (this->block_placed) {
		this->num_block--;
		this->block_placed = false;
	}
	if (this->num_block == 0)
		this->startCount = true;
	int y = this->base->getY();
	this->background->update(y, dt);
	if (this->startCount) {
		this->finish = this->timer->update(dt);
	}
	else {
		this->startCount = false;
		this->timer->reset();
	}
}

void Sopravvivenza::draw() {
	this->background->drawBack();
	this->drawBlock();
	this->base->draw();
	this->background->drawFront();
	this->hearts->draw();
	if (this->startCount)
		this->timer->draw();
	this->drawNextBlock();
	oslDrawStringf(80, 40, "%i", this->num_block);
	this->drawRamStatus();
}