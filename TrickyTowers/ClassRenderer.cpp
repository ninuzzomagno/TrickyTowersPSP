#include"ClassRenderer.h"

Renderer::Renderer() {
	this->lastFrame = this->currentFrame = 0;
}

void Renderer::start(const OSL_COLOR&c) {
	this->lastFrame = this->currentFrame;
	oslStartDrawing();
	oslClearScreen(c);
	oslReadKeys();
}

float Renderer::end(timer_TimeManager&timer) {
	oslEndDrawing();
	oslEndFrame();
	oslWaitVSync();
	oslSwapBuffers();
	this->currentFrame = timer.timer_getTimeMilliSec();
	return float(this->currentFrame - this->lastFrame)/1000.f;
}