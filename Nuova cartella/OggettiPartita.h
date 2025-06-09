#pragma once

#include<oslib/oslib.h>
#include<box2d/box2d.h>
#include<string>
#include"ClassDraw.h"
#include"Utils.h"
#include"ClassResourceManager.h"
#include"MyQueryCallback.h"
#include"ClassAnimatedSprite.h"

class Flag {
public:

	Flag(b2World&, DIFFICULTY);
	~Flag();
	inline void setH(float h) { this->flag_h = h; };
	bool update(int,float);
	void draw();
private:
	OSL_IMAGE* bandiera[33];
	int flag_diff_h, flag_h;
	int frame;
	float frame_time;

	b2AABB aabb;

	MyQueryCallback queryCB;
	b2World* world;
};

class BaseGara {
public:
	BaseGara(b2World&,ResourceManager&,DIFFICULTY);
	~BaseGara();
	inline float getY() { return this->body->GetPosition().y * SCALE; };
	void draw();
private:
	OSL_IMAGE* texture;
	int base_mod_n;
	int* base_mod_x;
	b2Body* body;
};

class BaseSopravvivenza {
public:
	BaseSopravvivenza(b2World&, ResourceManager&);
	~BaseSopravvivenza();
	inline float getY() { return this->body->GetPosition().y * SCALE; };
	void draw();
private:
	OSL_IMAGE* texture;
	b2Body* body;
};

class BaseRompicapo {
public:
	BaseRompicapo(b2World&, ResourceManager&, DIFFICULTY);
	~BaseRompicapo();
	void draw();
private:
	int base_mod_n;
	int* base_mod_h;
	int base_rock_n[2];
	int* base_rock_h;
	OSL_IMAGE* texture;
	b2Body* body;
};

class Timer {
public:
	Timer(OSL_SOUND*);
	~Timer();
	bool update(float);
	void reset();
	void draw();
private:
	int counter;
	float wait;
	OSL_SOUND* sound;
};

class Laser : public AnimatedSprite {
public:
	Laser(b2World&);
	~Laser();
	bool update(bool&,float dt);
	void draw();
private:
	int yLaser;

	b2AABB aabb;

	MyQueryCallback queryCB;
	b2World* world;

};

class Hearts {
public:
	Hearts(ResourceManager&);
	~Hearts();
	bool update(float,bool&);
	void draw();
private:
	OSL_IMAGE* texture;
	int current;
	int max;
	float eff;
};