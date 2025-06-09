#pragma once
#include<box2d/box2d.h>

class MyQueryCallback : public b2QueryCallback {
public:

	bool found = false;

	bool ReportFixture(b2Fixture* fixture)override {
		if (fixture->GetBody()->GetGravityScale() != 0.f) {
			this->found = true;
		}
		return false;
	};
};