#pragma once

#include<oslib/oslib.h>
#include<fstream>
#include"Utils.h"

struct rect {
	int x, y, w, h;
};

struct position {
	float x;
	float y;
};

struct my_particle {
	rect frame;
	position pos;
	float angle, delta;
};

class Cloud {
public:
	Cloud(int,OSL_IMAGE*);
	~Cloud();
	virtual void update(float);
	virtual void draw();
protected:
	int nClouds;
	rect* p_sky_frames;
	OSL_IMAGE*texture;
	my_particle*p_sky_particle;
};

class GaraCloud : public Cloud {
public:
	GaraCloud(int,OSL_IMAGE*);
};

class RompicapoMeteor : public Cloud {
public:
	RompicapoMeteor(int n, OSL_IMAGE* texture);

	void update(float)override;
	void draw()override;
};

class SopravvivenzaCloud :public Cloud {
public:
	SopravvivenzaCloud(int, OSL_IMAGE*);

	void update(float)override;
};
