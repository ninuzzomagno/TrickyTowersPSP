#pragma once

#include<box2d/box2d.h>
#include"Utils.h"
#include"ClassLevel.h"

class Level;

class MyContactListener : public b2ContactListener {
public:
	MyContactListener(Level*);
	~MyContactListener();
	void BeginContact(b2Contact*) override;
private:
	Level* lv;
};