#include "ClassCloud.h"

Cloud::Cloud(int num,OSL_IMAGE*texture) {
	this->texture=texture;
	this->nClouds = num;
	this->p_sky_particle = new my_particle[num];
}

void Cloud::update(float dt) {
	for (int i = 0; i < this->nClouds; i++) {
		if (this->p_sky_particle[i].pos.x > 480) {
			this->p_sky_particle[i].pos.x = rand() % 481 - 500;;
			this->p_sky_particle[i].pos.y = rand() % 130;
			this->p_sky_particle[i].frame = this->p_sky_frames[rand() % 3];
		}
		this->p_sky_particle[i].pos.x += 20*dt;
	}
}

void Cloud::draw() {
	for (int i = 0; i < this->nClouds; i++) {
		this->texture->angle = 0;
		oslSetImageTile(this->texture, this->p_sky_particle[i].frame.x, this->p_sky_particle[i].frame.y, this->p_sky_particle[i].frame.w, this->p_sky_particle[i].frame.h);
		oslDrawImageXY(this->texture, this->p_sky_particle[i].pos.x, this->p_sky_particle[i].pos.y);
	}
}

Cloud::~Cloud() {
	delete[]this->p_sky_particle;
	delete[]this->p_sky_frames;
	this->texture=nullptr;
}

GaraCloud::GaraCloud(int n,OSL_IMAGE*texture):Cloud(n,texture){
	this->p_sky_frames = new rect[3];

	std::ifstream FILE("resource/mode/clouds.txt", std::ios::in);

	for (int i = 0; i < 3; i++) {
		FILE >> this->p_sky_frames[i].x;
		FILE >> this->p_sky_frames[i].y;
		FILE >> this->p_sky_frames[i].w;
		FILE >> this->p_sky_frames[i].h;
	}
	FILE.close();

	for (int i = 0; i < this->nClouds; i++) {
		this->p_sky_particle[i].pos.x = rand() % 481 - 500;
		this->p_sky_particle[i].pos.y = rand() % 130;
		this->p_sky_particle[i].angle = 0.f;
		this->p_sky_particle[i].frame = this->p_sky_frames[rand() % 3];
	}
}

SopravvivenzaCloud::SopravvivenzaCloud(int n,OSL_IMAGE*texture):Cloud(n,texture){
	
	this->p_sky_frames = new rect[3];

	std::ifstream FILE("resource/mode/dark_clouds.txt", std::ios::in);

	for (int i = 0; i < 3; i++) {
		FILE >> this->p_sky_frames[i].x;
		FILE >> this->p_sky_frames[i].y;
		FILE >> this->p_sky_frames[i].w;
		FILE >> this->p_sky_frames[i].h;
	}
	FILE.close();

	for (int i = 0; i < this->nClouds; i++) {
		this->p_sky_particle[i].pos.x = rand() % 481 - 500;
		this->p_sky_particle[i].pos.y = rand() % 220+10;
		this->p_sky_particle[i].angle = 0;
		this->p_sky_particle[i].frame = this->p_sky_frames[rand() % 2];
	}
}

void SopravvivenzaCloud::update(float dt) {
	for (int i = 0; i < this->nClouds; i++) {
		if (this->p_sky_particle[i].pos.x > 480) {
			this->p_sky_particle[i].pos.x = rand() % 481 - 500;
			this->p_sky_particle[i].pos.y = rand() % 220 + 10;
			this->p_sky_particle[i].frame = this->p_sky_frames[rand() % 3];
		}
		this->p_sky_particle[i].pos.x += 20 * dt;
	}
}

RompicapoMeteor::RompicapoMeteor(int n,OSL_IMAGE*texture):Cloud(n,texture){
	this->p_sky_frames = new rect[2];

	std::ifstream FILE("resource/mode/meteor.txt", std::ios::in);

	for (int i = 0; i < 2; i++) {
		FILE >> this->p_sky_frames[i].x;
		FILE >> this->p_sky_frames[i].y;
		FILE >> this->p_sky_frames[i].w;
		FILE >> this->p_sky_frames[i].h;
	}
	FILE.close();

	for (int i = 0; i < this->nClouds; i++) {
		this->p_sky_particle[i].pos.x = 40 + rand() % 400;
		this->p_sky_particle[i].pos.y = 250 + rand() % 80;
		this->p_sky_particle[i].angle = rand() % 360;
		this->p_sky_particle[i].delta = rand() % 5;
		this->p_sky_particle[i].frame = this->p_sky_frames[rand() % 2];
	}
}

void RompicapoMeteor::update(float dt){
	for (int i = 0; i < this->nClouds; i++) {
		if (this->p_sky_particle[i].pos.y < -70) {
			this->p_sky_particle[i].pos.x = 40 + rand() % 440;
			this->p_sky_particle[i].pos.y = 250 + rand() % 100;
			this->p_sky_particle[i].frame = this->p_sky_frames[rand() % 2];
		}
		this->p_sky_particle[i].angle += this->p_sky_particle[i].delta*dt;
		this->p_sky_particle[i].pos.y -= 100*dt;
	}
}

void RompicapoMeteor::draw() {
	for (int i = 0; i < this->nClouds; i++) {
		oslSetImageTile(this->texture, this->p_sky_particle[i].frame.x, this->p_sky_particle[i].frame.y, this->p_sky_particle[i].frame.w, this->p_sky_particle[i].frame.h);
		this->texture->angle = this->p_sky_particle[i].angle;
		oslImageRotMoveX(this->texture, this->p_sky_particle[i].frame.w / 2);
		oslImageRotMoveY(this->texture, this->p_sky_particle[i].frame.h / 2);
		oslSetImageRotCenter(this->texture);
		oslDrawImageXY(this->texture, this->p_sky_particle[i].pos.x, this->p_sky_particle[i].pos.y);
	}
}
