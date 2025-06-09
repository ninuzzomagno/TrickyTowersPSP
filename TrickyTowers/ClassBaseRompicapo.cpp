#include"OggettiPartita.h"

BaseRompicapo::BaseRompicapo(b2World& world, ResourceManager& res, DIFFICULTY diff) {
	this->texture = res.getImage("base");

	b2BodyDef bDef;
	b2FixtureDef fDef;

	bDef.allowSleep = true;
	bDef.type = b2_staticBody;
	fDef.restitution = 0.f;
	fDef.friction = 1.f;
	fDef.density = 2.0;

	b2PolygonShape shape;

	int max = 0;

	this->base_rock_h = nullptr;

	switch (diff) {
	case DIFFICULTY::EASY:
		this->base_mod_n = 5;

		this->base_mod_h = new int[5];

		for (int i = 0; i < this->base_mod_n; i++) {
			this->base_mod_h[i] = int(rand() % 7+1);
			if (max < this->base_mod_h[i])
				max = this->base_mod_h[i];
		}

		bDef.position.Set(240.f / SCALE, (259.f - max * 5) / SCALE);
		this->body = world.CreateBody(&bDef);

		for(int i=0;i<this->base_mod_n;i++){
			shape.SetAsBox((SIZE_BOX) / 2.f / SCALE, (SIZE_BOX * this->base_mod_h[i]) / 2.f / SCALE, b2Vec2((-5.f * (this->base_mod_n - 1) + 10 * i + 1.f) / SCALE, (max * 5 - SIZE_BOX * this->base_mod_h[i] * 0.5) / SCALE), 0);
			fDef.shape = &shape;
			this->body->CreateFixture(&fDef);
		}

		break;
	case DIFFICULTY::NORMAL:
		this->base_mod_n = 3;
		this->base_mod_h = new int[3];

		for (int i = 0; i < this->base_mod_n; i++) {
			this->base_mod_h[i] = int(rand() % 8);
			if (max < this->base_mod_h[i])
				max = this->base_mod_h[i];
		}

		if (max == 0) {
			this->base_mod_h[1] = 7;
			max = 7;
		}

		bDef.position.Set(240.f / SCALE, (259.f - max * 5) / SCALE);
		this->body = world.CreateBody(&bDef);

		for (int i = 0; i < this->base_mod_n; i++) {
			if (this->base_mod_h[i] != 0) {
				shape.SetAsBox((SIZE_BOX) / 2.f / SCALE, (SIZE_BOX * this->base_mod_h[i]) / 2.f / SCALE, b2Vec2((-5.f * (this->base_mod_n - 1) + 10 * i + 1.f) / SCALE, (max * 5 - SIZE_BOX * this->base_mod_h[i] * 0.5) / SCALE), 0);
				fDef.shape = &shape;
				this->body->CreateFixture(&fDef);
			}
		}

		break;
	case DIFFICULTY::HARD:
		this->base_mod_n = 1;

		this->base_mod_h = new int[1];
		this->base_mod_h[0] = 7;

		int max = 0;

		for (int i = 0; i < 2; i++) {
			this->base_rock_n[i] = int(rand() % 3 + 1);
			max += this->base_rock_n[i];
		}

		this->base_rock_h = new int[max];

		for (int i = 0; i < max; i++)
			this->base_rock_h[i] = int(rand() % 7 + 1);

		bDef.position.Set(240.f / SCALE, (259.f - this->base_mod_h[0] * 5) / SCALE);
		this->body = world.CreateBody(&bDef);

		shape.SetAsBox(SIZE_BOX / 2.f / SCALE, (SIZE_BOX * this->base_mod_h[0]) / 2.f / SCALE, b2Vec2(1.f/SCALE, (this->base_mod_h[0] * 5 - SIZE_BOX * this->base_mod_h[0] * 0.5) / SCALE), 0);
		fDef.shape = &shape;
		this->body->CreateFixture(&fDef);
		

		for (int i = 0; i < this->base_rock_n[0]; i++) {
			shape.SetAsBox(SIZE_BOX / 2.f / SCALE, SIZE_BOX / 2.f / SCALE, b2Vec2(-9.f / SCALE, (this->base_mod_h[0] * 5.f - 5.f * this->base_rock_h[i] - 5.f * (this->base_rock_h[i] - 1)) / SCALE), 0);
			fDef.shape = &shape;
			this->body->CreateFixture(&fDef);
		}

		for (int i = 0; i < this->base_rock_n[1]; i++) {
			int y = i + this->base_rock_n[0];
			shape.SetAsBox(SIZE / 2.f / SCALE, SIZE_BOX / 2.f / SCALE, b2Vec2(10.f / SCALE, (this->base_mod_h[0] * 5.f - 5.f * this->base_rock_h[y] - 5.f * (this->base_rock_h[y] - 1)) / SCALE), 0);
			fDef.shape = &shape;
			this->body->CreateFixture(&fDef);
		}
		
		break;
	}
}

void BaseRompicapo::draw() {
	if (this->base_rock_h==nullptr) {
		oslSetImageTile(this->texture, 85, 96, 95, 166);
		for (int i = 0; i < this->base_mod_n; i++) {
			if (this->base_mod_h[i] != 0)
				oslDrawImageXY(this->texture, 240 - 5 * (this->base_mod_n - 1) + 10 * i - 5, 259 - 10 * this->base_mod_h[i]);
		}
	}
	else{

		oslSetImageTile(this->texture, 85, 96, 95, 166);
		oslDrawImageXY(this->texture, 240 - 5, 259 - 10 * this->base_mod_h[0]);

		oslSetImageTile(this->texture, 85, 10, 95, 20);
		for (int i = 0; i < this->base_rock_n[0]; i++) {
			oslDrawImageXY(this->texture, 240 - 15, 259 - 10 * this->base_rock_h[i]);
		}

		for (int i = 0; i < this->base_rock_n[1]; i++) {
			oslDrawImageXY(this->texture, 240 + 5, 259 - 10 * this->base_rock_h[i + this->base_rock_n[0]]);
		}

	}
}

BaseRompicapo::~BaseRompicapo() {
	delete this->base_mod_h;
	this->texture = nullptr;
	b2World* w = this->body->GetWorld();
	w->DestroyBody(this->body);
	w = nullptr;

	if (this->base_rock_h)
		delete this->base_rock_h;
}