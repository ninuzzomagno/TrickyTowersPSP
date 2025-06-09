#include"OggettiPartita.h"

BaseGara::BaseGara(b2World&world,ResourceManager&res,DIFFICULTY diff) {

	this->texture = res.getImage("base");

	b2BodyDef bDef;
	b2FixtureDef fDef;

	bDef.allowSleep = true;
	bDef.type = b2_staticBody;
	fDef.restitution = 0.f;
	fDef.friction = 1.f;
	fDef.density = 2.0;

	b2PolygonShape shape;
	shape.SetAsBox((SIZE_BOX) / 2.f / SCALE, (SIZE_BOX) / 2.f / SCALE);
	fDef.shape = &shape;

	switch (diff) {
	case DIFFICULTY::EASY:
		this->base_mod_n = 1;
		this->base_mod_x = new int((rand() % 5) * 10);
		bDef.position.Set((float(*this->base_mod_x) + (SIZE / 2.f) + 211.f) / SCALE, 177.f / SCALE);
		world.CreateBody(&bDef)->CreateFixture(&fDef);
		break;
	case DIFFICULTY::NORMAL:
		this->base_mod_n = 2;
		this->base_mod_x = new int[2];
		this->base_mod_x[0] = (rand() % 5) * 10;
		do {
			this->base_mod_x[1] = (rand() % 5) * 10;
		} while (this->base_mod_x[1] == this->base_mod_x[0]);

		for (int i = 0; i < 2; i++) {
			bDef.position.Set((float(this->base_mod_x[i]) + (SIZE / 2.f) + 211.f) / SCALE, 177.f / SCALE);
			world.CreateBody(&bDef)->CreateFixture(&fDef);
		}
		break;
	case DIFFICULTY::HARD:
		this->base_mod_n = 3;
		this->base_mod_x = new int[3];
		this->base_mod_x[0] = (rand() % 5) * 10;
		do {
			this->base_mod_x[1] = (rand() % 5) * 10;
		} while (this->base_mod_x[1] == this->base_mod_x[0]);

		do {
			this->base_mod_x[2] = (rand() % 5) * 10;
		} while (this->base_mod_x[2] == this->base_mod_x[0] || this->base_mod_x[2] == this->base_mod_x[1]);

		for (int i = 0; i < 3; i++) {
			bDef.position.Set((float(this->base_mod_x[i]) + (SIZE / 2.f) + 211.f) / SCALE, 177.f / SCALE);
			world.CreateBody(&bDef)->CreateFixture(&fDef);
		}
		break;
	}
	
	shape.SetAsBox((SIZE * 5 + SIZE_BOX) / 2.f / SCALE, 20.f / 2.f / SCALE);
	bDef.position.Set(241.f / SCALE, 192.f / SCALE);
	this->body = world.CreateBody(&bDef);
	this->body->CreateFixture(&fDef);
	this->body->GetUserData().pointer = 0;
}

void BaseGara::draw() {
	int y = int(this->body->GetPosition().y * SCALE);

	oslSetImageTile(this->texture, 0, 0, 84, 82);
	oslDrawImageXY(this->texture, 198, y-10);

	oslSetImageTile(this->texture, 85, 0, 95, 10);
	for (int i = 0; i < this->base_mod_n; i++) {
		oslDrawImageXY(this->texture, this->base_mod_x[i] + 211, y-20);
	}
}

BaseGara::~BaseGara() {
	this->texture = nullptr;
	delete[] this->base_mod_x;
	b2World* w = this->body->GetWorld();
	w->DestroyBody(this->body);
	w = nullptr;
}

