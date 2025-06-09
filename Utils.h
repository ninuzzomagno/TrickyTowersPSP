#pragma once

const float SIZE = 10.f;
const float SIZE_BOX = 9.7f;
const float SCALE = 10.f;

const int POS_IT = 3;
const float DELTA_T = 1.f / 60.f;
const int VEL_IT = 8;

enum class BLOCKS { LD, LS, ZD, Q, P, R, ZS };
enum class DIFFICULTY { EASY, NORMAL, HARD, RANDOM };

char* itoa(int num, char* buffer, int base); 

