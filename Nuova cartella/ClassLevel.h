#pragma once

#include<list>
#include"ClassBlock.h"
#include<oslib/oslib.h>
#include<box2d/box2d.h>
#include"ClassResourceManager.h"
#include"OggettiPartita.h"
#include"Backgrounds.h"
#include"ClassRenderer.h"
#include"timeManager.h"
#include"ClassCamera.h"
#include"MyContactListener.h"
#include"Utils.h"
#include"ClassPausa.h"


enum class PARTITA { SOPRAVVIVENZA, ROMPICAPO, GARA, RANDOM };

class MyContactListener;

struct collisionInfo {
	float yCollision;
	bool collision;
};

class Level {
public:
	Level(ResourceManager&, float);
	~Level();

	void collisionDetected(float);
	inline Block* getCurrentActiveBlock() { return this->list_blocks.front(); };
	inline bool collision() { return this->collInfo.collision; };
	inline b2World* getWorld() { return this->world; };

	inline ResourceManager* getResMan() { return this->res; };
	void deleteBlockWithBody(b2Body*);

protected:
	b2World* world;

	void updateWorld(float);
	void updateBlocks(bool,float);
	void addBlock();
	void drawBlock();
	void drawNextBlock();
	Renderer renderer;
	collisionInfo collInfo;
	Camera* cam;

	Timer* timer;

	float debugCam;
	bool block_deleted;
	bool block_placed;
	ResourceManager* res;

	bool finish;

	bool startCount;

	void drawRamStatus();

	MenuPausa menuPausa;

	Controls*controls;
private:
	std::list<Block*>list_blocks;
	MyContactListener* collisionListener;
	OSL_IMAGE* texture_blocks[7];

	int next_block;
	float accumulator;

	OSL_MEMSTATUS ram_status;
};

class Gara : public Level {
public:
	Gara(ResourceManager&,DIFFICULTY);
	~Gara();
	PAUSA_STATUS run();
private:

	void update(float);
	void draw();

	BgGara*background;
	BaseGara*base;
	Flag*flag;
};

class Rompicapo : public Level {
public:
	Rompicapo(ResourceManager&, DIFFICULTY);
	~Rompicapo();
	PAUSA_STATUS run();
private:

	void update(float);
	void draw();
	
	BgRompicapo* background;
	BaseRompicapo* base;
	Laser* laser;

	bool laserCollision;
};

class Sopravvivenza : public Level {
public:
	Sopravvivenza(ResourceManager&, DIFFICULTY);
	~Sopravvivenza();

	PAUSA_STATUS run();
private:

	void update(float);
	void draw();

	BaseSopravvivenza* base;

	BgSopravvivenza* background;

	Hearts*hearts;

	int num_block;
};

