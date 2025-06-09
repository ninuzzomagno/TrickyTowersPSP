#include"Backgrounds.h"

Background::Background(ResourceManager& res) {
	this->next_block_icon = res.getImage("next");
	oslSetImageTile(this->next_block_icon, 0, 0, 62, 48);
	this->back = new OSL_IMAGE * [2];
}

Background::~Background() {
	this->back[0] = nullptr;
	this->back[1] = nullptr;
	delete[]this->back;
}

BgGara::BgGara(ResourceManager&res):Background(res) {
	this->back[0] = res.getImage("gara_background0");
	this->back[1] = res.getImage("gara_background1");
	this->cloud = new GaraCloud(5,res.getImage("nuvole"));
	
	this->pos_wave[0] = 0.f;
}

BgGara::~BgGara() {
	delete this->cloud;
	this->wave = nullptr;
}

void BgGara::update(int yBase,float dt) {
	this->pos_wave[0] += 50 * dt;
	this->pos_wave[1] = yBase + 57;
	if (this->pos_wave[0] > 480)
		this->pos_wave[0] = 0;

	this->cloud->update(dt);
}

void BgGara::drawBack() {

	oslDrawImageXY(this->back[0], 0, 0);
	oslSetImageTile(this->back[1], 0, 24, 480, 203);
	oslDrawImageXY(this->back[1], 0, this->pos_wave[1] - 155);

	this->cloud->draw();
}

void BgGara::drawFront() {
	oslSetImageTile(this->back[1], 0, 0, 480, 24);
	oslDrawImageXY(this->back[1], this->pos_wave[0], this->pos_wave[1]);
	oslDrawImageXY(this->back[1], this->pos_wave[0] - 480, this->pos_wave[1]);
	oslDrawImageXY(this->next_block_icon, 30, 0);
}

BgRompicapo::BgRompicapo(ResourceManager& res):Background(res) {
	this->back[0] = res.getImage("romp_background0");
	this->back[1] = res.getImage("romp_background1");

	this->meteor = new RompicapoMeteor(5, res.getImage("nuvole"));
	this->pos_wave[0] = 0;
	this->pos_wave[1] = 248;
}

BgRompicapo::~BgRompicapo() {
	delete this->meteor;
}

void BgRompicapo::update(int,float dt) {
	this->pos_wave[0] += 50 * dt;
	if (this->pos_wave[0] > 480)
		this->pos_wave[0] = 0;
	this->meteor->update(dt);
}

void BgRompicapo::drawBack() {
	oslDrawImage(this->back[0]);
	oslSetImageTile(this->back[1], 0, 24, 480, 170);
	oslDrawImageXY(this->back[1], 0, 120);

	this->meteor->draw();

	oslDrawImageXY(this->next_block_icon, 30, 0);
}

void BgRompicapo::drawFront() {
	oslSetImageTile(this->back[1], 0, 0, 480, 24);
	oslDrawImageXY(this->back[1], this->pos_wave[0], this->pos_wave[1]);
	oslDrawImageXY(this->back[1], this->pos_wave[0]-480, this->pos_wave[1]);
}

BgSopravvivenza::BgSopravvivenza(ResourceManager& res) :Background(res) {
	this->cloud = new SopravvivenzaCloud(5, res.getImage("nuvole"));

	this->back[0] = res.getImage("sopr_background0");
	this->back[1] = res.getImage("sopr_background1");
}

void BgSopravvivenza::update(int, float dt) {
	this->cloud->update(dt);
}

void BgSopravvivenza::drawBack() {
	oslDrawImage(this->back[0]);
	this->cloud->draw();
	oslDrawImageXY(this->back[1], 0, 122);
	oslDrawImageXY(this->next_block_icon, 30, 0);

}

BgSopravvivenza::~BgSopravvivenza() {
	delete this->cloud;
}

void BgSopravvivenza::drawFront(){}