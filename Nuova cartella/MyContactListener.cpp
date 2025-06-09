#include"MyContactListener.h"

MyContactListener::MyContactListener(Level*lv) {
	this->lv = lv;
}

MyContactListener::~MyContactListener() {
	this->lv = nullptr;
}

void MyContactListener::BeginContact(b2Contact* contact) {
	
	Block* activeBlock = this->lv->getCurrentActiveBlock();
	b2Body* active = activeBlock->getBody();

	if (activeBlock->isActive() && (active == contact->GetFixtureB()->GetBody() || active==contact->GetFixtureA()->GetBody())) {
		oslPlaySound(this->lv->getResMan()->getSound("collision"), 2);

		b2Body* bA = contact->GetFixtureA()->GetBody();
		b2Body* bB = contact->GetFixtureB()->GetBody();

		bA->SetLinearVelocity(b2Vec2(0.f, 0.f));
		bA->SetGravityScale(1.f);
		bB->SetLinearVelocity(b2Vec2(0.f, 0.f));
		bB->SetGravityScale(1.f);

		float yCollisionA = bA->GetPosition().y;
		float yCollisionB = bB->GetPosition().y;

		this->lv->collisionDetected((yCollisionA <= yCollisionB ? yCollisionA : yCollisionB) * SCALE);
	}
}