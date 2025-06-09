#pragma once

#include<oslib/oslib.h>
#include<box2d/box2d.h>
#include"ClassResourceManager.h"
#include"ClassDraw.h"
#include"Utils.h"

struct BlockUserData {
	float w, h;
};

class Block {
public:
	~Block();
	Block(BLOCKS, b2Vec2, b2World*, OSL_IMAGE*);

	void createShape(const BLOCKS,const b2Vec2&, b2World*, bool doubled = false);
	void update();
	void draw();

	inline void setCollisionY(float y) { this->collision_y = y; };
	inline float getCollisionY() { return this->collision_y; };
	inline void setActive(bool val) { this->active = val; };
	inline bool isActive() { return this->active; };
	inline void Dead(bool v) { this->DEAD = v; };
	
	bool isDead(int);
	inline b2Body* getBody() { return this->body; };
private:
	bool DEAD, active;

	float collision_y;

	OSL_IMAGE* texture;

	b2Body* body;
	b2Vec2 pos_g, def_vel;
	b2Vec2 POS;
};
