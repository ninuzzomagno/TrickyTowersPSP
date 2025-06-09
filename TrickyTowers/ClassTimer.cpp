#include"OggettiPartita.h"

Timer::Timer(OSL_SOUND*s) {
	this->reset();
	this->sound = s;
}

Timer::~Timer() {
	this->sound = nullptr;
}

bool Timer::update(float dt) {
	this->wait -= dt;
	if (this->wait < 0.f) {
		oslPlaySound(this->sound, 3);
		this->wait = 1.f;
		this->counter--;
	}
	if (this->counter == 0)
		return true;
	return false;
}

void Timer::draw() {
	oslDrawStringf(240, 50, "%i", this->counter);
}

void Timer::reset() {
	this->counter = 3;
	this->wait = 1.f;
}