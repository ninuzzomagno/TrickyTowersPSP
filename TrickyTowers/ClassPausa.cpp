#include"ClassPausa.h"

MenuPausa::MenuPausa() {
	this->pS = PAUSA_STATUS::RESUME;
	this->hoverIndex = 0;
}

PAUSA_STATUS MenuPausa::update(timer_TimeManager&timer) {
	if (osl_pad.pressed.start){
		if (this->pS == PAUSA_STATUS::RESUME) {
			timer.timer_startPause();
			this->pS = PAUSA_STATUS::PAUSED;
		}
		else {
			this->pS = PAUSA_STATUS::RESUME;
			timer.timer_endPause();
		}
	}

	if (this->pS==PAUSA_STATUS::PAUSED) {
		if (osl_pad.pressed.up)
			this->hoverIndex == 0 ? this->hoverIndex = 2 : this->hoverIndex--;
		else if (osl_pad.pressed.down)
			this->hoverIndex == 2 ? this->hoverIndex = 0 : this->hoverIndex++;
		else if (osl_pad.pressed.cross) {
			if (this->hoverIndex == 0) {
				timer.timer_endPause();
				this->pS = PAUSA_STATUS::RESUME;
			}
			else if (this->hoverIndex == 1)
				this->pS = PAUSA_STATUS::RESTART;
			else if (this->hoverIndex == 2)
				this->pS = PAUSA_STATUS::QUIT;
		}
	}


	return this->pS;
}

void MenuPausa::draw(Controls&ctrl) {
	if (this->pS == PAUSA_STATUS::PAUSED) {
		oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, 100));
		oslDrawFillRect(0, 15, 480, 45, RGB(255, 255, 255));
		oslDrawStringf(240, 25, "Pause");

		oslDrawFillRect(170, 90 + 36 * this->hoverIndex, 310, 120 + 36 * this->hoverIndex, RGB(255, 255, 255));

		oslDrawStringf(240, 100, "Resume");
		oslDrawStringf(240, 136, "Restart");
		oslDrawStringf(240, 172, "Quit");

		oslDrawFillRect(10,230,210,260, RGB(255, 255, 255));
		ctrl.draw(TASTI::CROSS, 30, 245, 20, 20);
		oslDrawStringf(120, 240, "Confirme");
	}
}