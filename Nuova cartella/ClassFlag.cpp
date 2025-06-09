#include"OggettiPartita.h"

char* itoa(int num, char* buffer, int base) {
	int curr = 0;

	if (num == 0) {
		// Base case
		buffer[curr++] = '0';
		buffer[curr] = '\0';
		return buffer;
	}

	int num_digits = 0;

	if (num < 0) {
		if (base == 10) {
			num_digits++;
			buffer[curr] = '-';
			curr++;
			// Make it positive and finally add the minus sign
			num *= -1;
		}
		else
			// Unsupported base. Return NULL
			return NULL;
	}

	num_digits += (int)floor(log(num) / log(base)) + 1;

	// Go through the digits one by one
	// from left to right
	while (curr < num_digits) {
		// Get the base value. For example, 10^2 = 1000, for the third digit
		int base_val = (int)pow(base, num_digits - 1 - curr);

		// Get the numerical value
		int num_val = num / base_val;

		char value = num_val + '0';
		buffer[curr] = value;

		curr++;
		num -= base_val * num_val;
	}
	buffer[curr] = '\0';
	return buffer;
}

Flag::Flag(b2World&world,DIFFICULTY diff) {

	switch (diff) {
	case DIFFICULTY::EASY:
		this->flag_diff_h = 20.f;
		break;
	case DIFFICULTY::NORMAL:
		this->flag_diff_h = -100.f;
		break;
	case DIFFICULTY::HARD:
		this->flag_diff_h = -200.f;
		break;
	}

	this->world = &world;

	char num[2];
	std::string file = "";

	for (int i = 0; i < 33; i++) {
		file = "resource/mode/gara/bandiera/bandiera";
		file = file + itoa(i + 1, num, 10);
		file = file + ".png";
		this->bandiera[i] = oslLoadImageFilePNG(const_cast<char*>(file.c_str()), OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	}

	this->frame = 0;
	this->frame_time = 0.05f;
	this->flag_h = this->flag_diff_h;

	this->aabb.lowerBound.Set(220.f / SCALE, this->flag_h / SCALE);
	this->aabb.upperBound.Set(280.f / SCALE, (this->flag_h + 10) / SCALE);

}

Flag::~Flag() {
	this->world = nullptr;
	for (int i = 0; i < 33; ++i) {
		if (bandiera[i] != nullptr) {
			oslDeleteImage(bandiera[i]);
			bandiera[i] = nullptr;
		}
	}
}

bool Flag::update(int yBase,float dt) {
	this->flag_h = this->flag_diff_h + (yBase - 192);
	this->aabb.lowerBound.Set(220.f / SCALE, this->flag_h / SCALE);
	this->aabb.upperBound.Set(280.f / SCALE, (this->flag_h + 10) / SCALE);
	this->frame_time -= dt;
	if (this->frame_time < 0) {
		this->frame_time = 0.05f;
		this->frame == 32 ? this->frame = 0 : this->frame++;
	}
	this->world->QueryAABB(&this->queryCB, this->aabb);
	if(this->queryCB.found==false)
		return false;
	else {
		this->queryCB.found = false;
		return true;
	}
}

void Flag::draw() {
	oslDrawImageXY(this->bandiera[this->frame], 0, this->flag_h);
}