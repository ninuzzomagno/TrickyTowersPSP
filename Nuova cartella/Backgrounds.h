#pragma once

#include<oslib/oslib.h>
#include<box2d/box2d.h>
#include"ClassCloud.h"
#include"ClassAnimatedSprite.h"

#include"ClassResourceManager.h"

class Background {
public:
	Background(ResourceManager&);
	virtual void update(int,float)=0;
	virtual void drawBack()=0;
	virtual void drawFront() = 0;
	~Background();
protected:
	OSL_IMAGE* next_block_icon, ** back;
};

class BgGara : public Background {
public:
	BgGara(ResourceManager&);
	~BgGara();
	void update(int,float)override;
	void drawBack()override;
	void drawFront()override;
private:
	GaraCloud* cloud;
	OSL_IMAGE* wave;
	float pos_wave[2];
};

class BgRompicapo : public Background {
public:
	BgRompicapo(ResourceManager&);
	~BgRompicapo();
	void update(int,float)override;
	void drawBack()override;
	void drawFront()override;
private:
	RompicapoMeteor* meteor;
	float pos_wave[2];
};

class BgSopravvivenza :public Background {
public:
	BgSopravvivenza(ResourceManager&);
	~BgSopravvivenza();
	void update(int, float)override;
	void drawBack()override;
	void drawFront()override;
private:
	SopravvivenzaCloud* cloud;
};