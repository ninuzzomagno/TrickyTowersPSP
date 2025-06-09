#pragma once

#include<box2d/box2d.h>
#include"Utils.h"
#include<string>
#include<oslib/oslib.h>

class Camera {
public:
	Camera(float);
	float update(b2World*, bool, float);
private:
	float cameraY;
};