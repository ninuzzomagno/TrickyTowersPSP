#include"ClassLevel.h"

void Level::addBlock() {
	this->list_blocks.push_front(new Block(BLOCKS(this->next_block), b2Vec2(241.f, 20.f), this->world, this->texture_blocks[this->next_block]));
	this->next_block = rand() % 7;
}

Level::Level(ResourceManager&res,float yCam) {
	this->res = &res;
	this->collInfo.collision = false;
	this->collInfo.yCollision = 160.f;

	this->accumulator = 0.f;

	this->cam = new Camera(yCam);

	this->debugCam = 0.f;
	
	this->texture_blocks[0] = res.getImage("l1");
	this->texture_blocks[0]->angle = 0.f;
	oslImageRotMoveX(this->texture_blocks[0], 10);
	oslImageRotMoveY(this->texture_blocks[0], 15);
	oslSetImageRotCenter(this->texture_blocks[0]);

	this->texture_blocks[1] = res.getImage("l2");
	this->texture_blocks[1]->angle = 0.f;
	oslImageRotMoveX(this->texture_blocks[1], 10);
	oslImageRotMoveY(this->texture_blocks[1], 15);
	oslSetImageRotCenter(this->texture_blocks[1]);

	this->texture_blocks[2] = res.getImage("zd");
	this->texture_blocks[2]->angle = 0.f;
	oslImageRotMoveX(this->texture_blocks[2], 10);
	oslImageRotMoveY(this->texture_blocks[2], 15);
	oslSetImageRotCenter(this->texture_blocks[2]);

	this->texture_blocks[3] = res.getImage("q");
	this->texture_blocks[3]->angle = 0.f;
	oslImageRotMoveX(this->texture_blocks[3], 10);
	oslImageRotMoveY(this->texture_blocks[3], 10);
	oslSetImageRotCenter(this->texture_blocks[3]);

	this->texture_blocks[4] = res.getImage("p");
	this->texture_blocks[4]->angle = 0.f;
	oslImageRotMoveX(this->texture_blocks[4], 15);
	oslImageRotMoveY(this->texture_blocks[4], 10);
	oslSetImageRotCenter(this->texture_blocks[4]);

	this->texture_blocks[5] = res.getImage("r");
	this->texture_blocks[4]->angle = 0.f;
	oslImageRotMoveX(this->texture_blocks[5], 20);
	oslImageRotMoveY(this->texture_blocks[5], 5);
	oslSetImageRotCenter(this->texture_blocks[5]);

	this->texture_blocks[6] = res.getImage("zs");
	this->texture_blocks[6]->angle = 0.f;
	oslImageRotMoveX(this->texture_blocks[6], 10);
	oslImageRotMoveY(this->texture_blocks[6], 15);
	oslSetImageRotCenter(this->texture_blocks[6]);

	this->next_block = rand() % 7;

	this->world = new b2World(b2Vec2(0.f, 10.f));
	this->collisionListener=new MyContactListener(this);
	this->world->SetContactListener(this->collisionListener);

	this->timer = new Timer(this->res->getSound("counter"));

	this->addBlock();

	this->finish = false;
	this->startCount = false;
	this->block_placed = false;
	this->block_deleted = false;

	this->controls = new Controls(res);
}

Level::~Level() {
	for (int i = 0; i < 7; i++)
		this->texture_blocks[i] = nullptr;
	this->world->SetContactListener(nullptr);
	delete this->collisionListener;
	delete this->world;
	delete this->cam;
	delete this->timer;
}

void Level::updateBlocks(bool spawnBlock,float Ydead) {

	if (this->collInfo.collision == true) {
		this->cam->update(this->world, false, this->collInfo.yCollision);
		if(spawnBlock)
			this->addBlock();
		this->collInfo.collision = false;
	}
	else {
		for (std::list<Block*>::iterator it = this->list_blocks.begin(); it != this->list_blocks.end(); ++it) {
			(*it)->update();
			if ((*it)->isDead(Ydead)) {
				float y = (*it)->getCollisionY();
				it = this->list_blocks.erase(it);
				this->block_deleted = true;
				this->cam->update(this->world, true, y);
				if ((this->list_blocks.empty() || it == this->list_blocks.begin()) && spawnBlock)
					this->addBlock();
			}
		}
	}
}

void Level::drawBlock() {
	for (std::list<Block*>::iterator it = this->list_blocks.begin(); it != this->list_blocks.end(); ++it)
		(*it)->draw();
}

void Level::drawNextBlock() {
	this->texture_blocks[this->next_block]->angle = 0.f;
	oslDrawImageXY(this->texture_blocks[this->next_block], 61, 27);
}

void Level::collisionDetected(float yCollision) {
	this->collInfo.yCollision = yCollision;
	list_blocks.front()->setCollisionY(yCollision);
	this->collInfo.collision = true;
	this->list_blocks.front()->setActive(false);
	this->block_placed = true;
}

void Level::updateWorld(float dt) {
	this->accumulator += dt;
	while (this->accumulator > 0.f) {
		this->world->Step(DELTA_T, VEL_IT, POS_IT);
		this->accumulator -= dt;
	}
}

void Level::deleteBlockWithBody(b2Body* body) {
	for (std::list<Block*>::iterator it = this->list_blocks.begin(); it != this->list_blocks.end(); ++it) {
		if ((*it)->getBody() == body)
			it = this->list_blocks.erase(it);
	}
}

void Level::drawRamStatus() {
	this->ram_status = oslGetRamStatus();
	//oslDrawStringf(100, 250, "%f", this->ram_status.maxAvailable / (1024.f * 1024.f));
}