#include"ClassCamera.h"

Camera::Camera(float y) {
	this->cameraY = y;
}

float Camera::update(b2World*world,bool deletedBlock,float Y) {
	if (Y < this->cameraY && Y>40.f) {
		float val = (this->cameraY - Y) / SCALE;
		if (deletedBlock)
			val = -val;
		for (b2Body* body = world->GetBodyList(); body; body = body->GetNext()) {
			b2BodyType t = body->GetType();
			body->SetType(b2_kinematicBody);
			body->SetTransform(b2Vec2(0.f, val) + body->GetPosition(), body->GetAngle());
			body->SetType(t);
		}
	}
	return (Y);
}