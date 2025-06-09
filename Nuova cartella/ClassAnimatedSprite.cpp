#include"ClassAnimatedSprite.h"

AnimatedSprite::AnimatedSprite(OSL_IMAGE* img, std::string path) {
	this->texture = img;

	std::ifstream file(path,std::ios::in);
	this->currentFRAME_index = 0;

	file >> this->maxFrame;
	file >> this->iniFrame;
	file >> this->wait;
	this->defWait = this->wait;

	this->frames = new frame * [this->maxFrame];
	for (int i = 0; i < this->maxFrame; i++) {
		this->frames[i] = new frame;
		file >> this->frames[i]->x;
		file >> this->frames[i]->y;
		file >> this->frames[i]->w;
		file >> this->frames[i]->h;
	}
	file.close();
}

AnimatedSprite::~AnimatedSprite() {
	oslDeleteImage(this->texture);
	for (int i = 0; i < this->maxFrame; i++)
		delete this->frames[i];
	delete[]this->frames;

}

void AnimatedSprite::drawSprite(int x, int y) {
	oslImageRotMoveX(this->texture, 240);
	oslImageRotMoveY(this->texture, this->frames[this->currentFRAME_index]->h / 2);
	oslSetImageRotCenter(this->texture);
	oslSetImageTile(this->texture, this->frames[this->currentFRAME_index]->x, this->frames[this->currentFRAME_index]->y, this->frames[this->currentFRAME_index]->w, this->frames[this->currentFRAME_index]->h);
	oslDrawImageXY(this->texture, x, y);
}

void AnimatedSprite::updateSprite(float dt) {
	this->wait -= dt;
	if (this->wait < 0) {
		this->wait = this->defWait;
		this->currentFRAME_index++;
		if (this->currentFRAME_index == this->maxFrame - 1)
			this->currentFRAME_index = this->iniFrame;
	}
}