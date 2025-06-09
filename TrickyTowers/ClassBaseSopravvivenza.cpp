#include"OggettiPartita.h"

BaseSopravvivenza::BaseSopravvivenza(b2World&world,ResourceManager&res){
	this->texture = res.getImage("base");

	b2BodyDef bDef;
	bDef.type = b2_staticBody;
	bDef.position.Set(239.f / SCALE, 230.f / SCALE);

	this->body = world.CreateBody(&bDef);

	b2FixtureDef fDef;

	b2PolygonShape shape;

	fDef.restitution = 0.f;

	shape.SetAsBox(60.f / 2.f / SCALE, 44.f / 2.f / SCALE, b2Vec2(2.f, -10.f / SCALE), 0.f);
	fDef.shape = &shape;
	this->body->CreateFixture(&fDef);

	shape.SetAsBox(SIZE_BOX / 2.f / SCALE, SIZE_BOX / 2.f / SCALE, b2Vec2(-24.f / SCALE, -37.f / SCALE), 0.f);
	fDef.shape = &shape;
	this->body->CreateFixture(&fDef);

	shape.SetAsBox(SIZE_BOX / 2.f / SCALE, SIZE_BOX / 2.f / SCALE, b2Vec2(27.f / SCALE, -37.f / SCALE), 0.f);
	fDef.shape = &shape;
	this->body->CreateFixture(&fDef);

	shape.SetAsBox((SIZE_BOX+SIZE) / 2.f / SCALE, SIZE_BOX / 2.f / SCALE, b2Vec2(2.f / SCALE, -37.f / SCALE), 0.f);
	fDef.shape = &shape;
	this->body->CreateFixture(&fDef);
}

void BaseSopravvivenza::draw() {
	int y = int(this->body->GetPosition().y * SCALE);
	int x = int(this->body->GetPosition().x * SCALE);
	oslSetImageTile(this->texture, 0, 82, 72, 166);
	oslDrawImageXY(this->texture, x-36,y-42);
}

BaseSopravvivenza::~BaseSopravvivenza() {
	b2World* w = this->body->GetWorld();
	w->DestroyBody(this->body);
	w = nullptr;

	this->texture = nullptr;
}