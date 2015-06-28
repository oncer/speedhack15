#pragma once

#include "common.h"

class Char
{
public:
	Char();
	void update();
	void draw();
private:
	float t;
	ALLEGRO_BITMAP *img[2];
};
