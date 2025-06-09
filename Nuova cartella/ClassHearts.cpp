#include"OggettiPartita.h"

Hearts::Hearts(ResourceManager& res) {
	this->texture = res.getImage("vita");
	this->current = 3;
	this->max = 3;
}

Hearts::~Hearts() {
	this->texture = nullptr;
}

bool Hearts::update(float dt,bool& del) {
	if (del) {
		del = false;
		this->current--;
		this->eff = 1;
	}
	if (this->eff > 0)
		this->eff -= dt;
	if (this->current < 1)
		return true;
	return false;
}

void Hearts::draw() {

	if (this->eff > 0)
		oslDrawFillRect(0, 0, 480, 272, RGBA(255, 0, 0, int(100 * this->eff)));

	for (int i = 0; i < 3; i++) {
		if (this->current > i) {
			oslSetImageTile(this->texture, 0, 0, 15, 14);
		}
		else {
			oslSetImageTile(this->texture, 15, 0, 30, 14);
		}
		oslDrawImageXY(this->texture, 405 + 25 * i, 10);
	}
}