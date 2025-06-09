#include"ClassControls.h"

Controls::Controls(ResourceManager&res) {
	this->texture = res.getImage("controls");
}

void Controls::draw(TASTI tasto,int x, int y, int w, int h) {
	this->texture->angle = 0;
	switch (tasto) {
	case TASTI::CROSS:
		oslSetImageTile(this->texture, 64, 32, 96, 64);
		this->texture->stretchX = w;
		this->texture->stretchY = h;
		oslImageRotMoveX(this->texture, 16);
		oslImageRotMoveY(this->texture, 16);
		oslSetImageRotCenter(this->texture);
		break;
	case TASTI::SQUARE:
		oslSetImageTile(this->texture, 64, 0, 32, 33);
		this->texture->stretchX = w;
		this->texture->stretchY = h;
		oslImageRotMoveX(this->texture, 16);
		oslImageRotMoveY(this->texture, 16);
		oslSetImageRotCenter(this->texture);
		break;
	case TASTI::CIRCLE:
		oslSetImageTile(this->texture, 0, 0, 32, 33);
		this->texture->stretchX = w;
		this->texture->stretchY = h;
		oslImageRotMoveX(this->texture, 16);
		oslImageRotMoveY(this->texture, 16);
		oslSetImageRotCenter(this->texture);
		break;
	case TASTI::TRIANGLE:
		oslSetImageTile(this->texture, 32, 0, 32, 33);
		this->texture->stretchX = w;
		this->texture->stretchY = h;
		oslImageRotMoveX(this->texture, 16);
		oslImageRotMoveY(this->texture, 16);
		oslSetImageRotCenter(this->texture);
		break;
	case TASTI::UP:
		oslSetImageTile(this->texture, 32, 33, 64, 66);
		this->texture->stretchX = w;
		this->texture->stretchY = h;
		oslImageRotMoveX(this->texture, 16);
		oslImageRotMoveY(this->texture, 16);
		oslSetImageRotCenter(this->texture);
		break;
	case TASTI::DOWN:
		oslSetImageTile(this->texture, 32, 33, 64, 66);
		this->texture->stretchX = w;
		this->texture->stretchY = h;
		oslImageRotMoveX(this->texture, 16);
		oslImageRotMoveY(this->texture, 16);
		this->texture->angle = 180;
		oslSetImageRotCenter(this->texture);
		break;
	case TASTI::LEFT:
		oslSetImageTile(this->texture, 32, 33, 64, 66);
		this->texture->stretchX = w;
		this->texture->stretchY = h;
		oslImageRotMoveX(this->texture, 16);
		oslImageRotMoveY(this->texture, 16);
		this->texture->angle = -90;
		oslSetImageRotCenter(this->texture);
		break;
	case TASTI::RIGHT:
		oslSetImageTile(this->texture, 32, 33, 64, 66);
		this->texture->stretchX = w;
		this->texture->stretchY = h;
		oslImageRotMoveX(this->texture, 16);
		oslImageRotMoveY(this->texture, 16);
		this->texture->angle = 90;
		oslSetImageRotCenter(this->texture);
		break;
	case TASTI::L:
		oslSetImageTile(this->texture, 0, 33, 32, 50);
		this->texture->stretchX = w;
		this->texture->stretchY = h;
		oslImageRotMoveX(this->texture, 16);
		oslImageRotMoveY(this->texture, 16);
		oslSetImageRotCenter(this->texture);
		break;
	case TASTI::R:
		oslSetImageTile(this->texture, 0, 50, 32, 69);
		this->texture->stretchX = w;
		this->texture->stretchY = h;
		oslImageRotMoveX(this->texture, 16);
		oslImageRotMoveY(this->texture, 16);
		oslSetImageRotCenter(this->texture);
		break;
	}

	oslDrawImageXY(this->texture, x, y);
}

Controls::~Controls() {
	this->texture = nullptr;
}