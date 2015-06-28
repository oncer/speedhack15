#include "char.h"

Char::Char()
{
	img[0] = al_load_bitmap("assets/char00.png");
	img[1] = al_load_bitmap("assets/char01.png");
	t = 0;
}

void Char::update()
{
	t += 0.016;
}

void Char::draw()
{
	int idx = (int)(t) % 2;
	al_draw_bitmap(img[idx], 82, 287, 0);
}

