#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

extern ALLEGRO_DISPLAY *g_display;

void rng_init();
float rng_random();
int rng_random(int max);
int rng_random(int min, int max);

