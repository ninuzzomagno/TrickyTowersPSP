#include"OggettiPartita.h"

Laser::Laser(b2World& world) : AnimatedSprite(oslLoadImageFilePNG(const_cast<char*>("resource/mode/rompicapo/laser.png"), OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888), "resource/mode/rompicapo/laser.txt") {
	this->world = &world;
	this->yLaser = 136.f;
	this->aabb.lowerBound.Set(190.f / SCALE, this->yLaser / SCALE);
	this->aabb.upperBound.Set(320.f / SCALE, (this->yLaser + 2) / SCALE);
}

bool Laser::update(bool&del,float dt) {
	if (del) {
		del = false;
		this->yLaser += 10;
		this->aabb.lowerBound.Set(220.f / SCALE, this->yLaser / SCALE);
		this->aabb.upperBound.Set(280.f / SCALE, (this->yLaser + 2) / SCALE);
	}
	this->updateSprite(dt);
	this->world->QueryAABB(&this->queryCB, this->aabb);
	if (this->queryCB.found)
		return true;
	return false;
}

void Laser::draw() {
	this->drawSprite(240, this->yLaser);
}

Laser::~Laser() {
	this->world = nullptr;
}