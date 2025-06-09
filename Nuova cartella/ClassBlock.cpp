#include"ClassBlock.h"

Block::Block(BLOCKS s, b2Vec2 pos, b2World* world, OSL_IMAGE* texture) {

	this->body = nullptr;

	this->active = true;
	this->DEAD = false;

	this->collision_y = 0;

	this->texture = texture;

	this->createShape(s,pos, world, false);
}

void Block::createShape(const BLOCKS type_block,const b2Vec2& pos, b2World* world, bool doubled) {

	if (this->body != nullptr)
		world->DestroyBody(this->body);

	this->texture->stretchX = this->texture->sizeX * (1 + 1 * doubled);
	this->texture->stretchY = this->texture->sizeY * (1 + 1 * doubled);

	b2PolygonShape shape;
	b2BodyDef bBDEF;
	b2FixtureDef bFDEF;

	bBDEF.type = b2_dynamicBody;
	bBDEF.position.Set(pos.x / SCALE, pos.y / SCALE);
	bBDEF.allowSleep = true;
	bFDEF.density = 0.5f;
	bFDEF.restitution = 0.f;
	bFDEF.friction = 1.f;
	bFDEF.shape = &shape;

	this->body = world->CreateBody(&bBDEF);
	this->body->SetGravityScale(0.f);

	switch (type_block) {
	case BLOCKS::LD:

		shape.SetAsBox((SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE * 2 + SIZE_BOX) * (1 + 1 * doubled) / 2.f / SCALE, b2Vec2((SIZE * (1 + 1 * doubled)) / 2.f / SCALE, 0), 0);
		this->body->CreateFixture(&bFDEF);
		
		shape.SetAsBox((SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, b2Vec2((-SIZE * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE * (1 + 1 * doubled)) / SCALE), 0);
		this->body->CreateFixture(&bFDEF);

		break;
	case BLOCKS::LS:

		shape.SetAsBox((SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE * 2 + SIZE_BOX) * (1 + 1 * doubled) / 2.f / SCALE, b2Vec2((-SIZE * (1 + 1 * doubled)) / 2.f / SCALE, 0), 0);
		this->body->CreateFixture(&bFDEF);

		shape.SetAsBox((SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, b2Vec2((SIZE * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE * (1 + 1 * doubled)) / SCALE), 0);
		this->body->CreateFixture(&bFDEF);

		break;
	case BLOCKS::P:

		shape.SetAsBox((SIZE * 2 + SIZE_BOX) * (1 + 1 * doubled) / 2.f / SCALE, (SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, b2Vec2(0.f, (SIZE * (1 + 1 * doubled)) / 2.f / SCALE), 0);
		this->body->CreateFixture(&bFDEF);

		shape.SetAsBox((SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, b2Vec2(0.f, (-SIZE * (1 + 1 * doubled)) / 2.f / SCALE), 0);
		this->body->CreateFixture(&bFDEF);

		break;
	case BLOCKS::Q:

		shape.SetAsBox(((SIZE + SIZE_BOX) * (1 + 1 * doubled)) / 2.f / SCALE, ((SIZE + SIZE_BOX) * (1 + 1 * doubled)) / 2.f / SCALE);
		this->body->CreateFixture(&bFDEF);

		break;

	case BLOCKS::ZS:

		shape.SetAsBox((SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE + SIZE_BOX) * (1 + 1 * doubled) / 2.f / SCALE, b2Vec2(-5.f / SCALE, -5.f / SCALE),0.f);
		this->body->CreateFixture(&bFDEF);

		shape.SetAsBox((SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE + SIZE_BOX) * (1 + 1 * doubled) / 2.f / SCALE, b2Vec2(5.f / SCALE, 5.f / SCALE), 0.f);
		this->body->CreateFixture(&bFDEF);

		break;

	case BLOCKS::ZD:

		shape.SetAsBox((SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE + SIZE_BOX) * (1 + 1 * doubled) / 2.f / SCALE, b2Vec2(-5.f / SCALE, 5.f / SCALE), 0.f);
		this->body->CreateFixture(&bFDEF);

		shape.SetAsBox((SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE, (SIZE + SIZE_BOX) * (1 + 1 * doubled) / 2.f / SCALE, b2Vec2(5.f / SCALE, -5.f / SCALE), 0.f);
		this->body->CreateFixture(&bFDEF);

		break;

	case BLOCKS::R:

		shape.SetAsBox((SIZE * 3 + SIZE_BOX) * (1 + 1 * doubled) / 2.f / SCALE, (SIZE_BOX * (1 + 1 * doubled)) / 2.f / SCALE);
		this->body->CreateFixture(&bFDEF);

		break;
	}
}

void Block::update() {

	this->POS = this->body->GetPosition();

	if (this->active) {
		if (osl_pad.pressed.up)
			this->body->SetTransform(this->POS, this->body->GetAngle() + b2_pi / 2.f);
		else if (osl_pad.pressed.right)
			this->body->SetTransform(this->POS + b2Vec2(5.f / SCALE, 0.f), this->body->GetAngle());
		else if (osl_pad.pressed.left)
			this->body->SetTransform(this->POS - b2Vec2(5.f / SCALE, 0.f), this->body->GetAngle());
		else if (osl_pad.pressed.R)
			this->body->SetTransform(this->POS + b2Vec2(10.f / SCALE, 0.f), this->body->GetAngle());
		else if (osl_pad.pressed.L)
			this->body->SetTransform(this->POS - b2Vec2(10.f / SCALE, 0.f), this->body->GetAngle());
		else if (osl_pad.held.down)
			this->body->SetLinearVelocity(b2Vec2(0.f, 0.5f * SCALE));
		else
			this->body->SetLinearVelocity(b2Vec2(0.f, 0.05f * SCALE));
	}
}

void Block::draw() {

	if (this->POS.y * SCALE < 320.f) {
		float angle = 180.f * this->body->GetAngle() / b2_pi;
		this->texture->angle = angle;
		if (this->active) {
			int SIZE = this->texture->stretchX * oslCos(angle, 1.f) + this->texture->stretchY * oslSin(angle, 1.f);
			Draw::fillRect(this->POS.x * SCALE - SIZE / 2, 0, SIZE, 272, RGBA(255, 255, 255, 100));
		}
		oslDrawImageXY(this->texture, int(this->POS.x * SCALE), int(SCALE * (this->POS.y)));
	}

}

Block::~Block() {
	this->texture = nullptr;
	b2World* w = this->body->GetWorld();
	w->DestroyBody(this->body);
	this->body = nullptr;
	w = nullptr;
}

bool Block::isDead(int y) {
	if (this->DEAD || this->body->GetPosition().y * SCALE > y)
		return true;
	return false;
}