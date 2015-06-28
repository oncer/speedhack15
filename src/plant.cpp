#include "plant.h"
#include <algorithm>
#include <cmath>

static const int MAX_LEAVES = 32;

Plant::Plant()
{
	im_leaf = al_load_bitmap("assets/leaf.png");
	leaves = new Leaf[MAX_LEAVES];
	leaves_count = 0;
	age = 0;
}

Plant::~Plant()
{
	delete[] leaves;
}

void Plant::update()
{
	age++;
	for (int i = 0; i < leaves_count; i++) {
		leaves[i].age++;
	}

	if (leaves_count < age * 0.05) {
		Leaf& leaf = leaves[leaves_count];
		leaf.age = 0;
		leaf.health = 100;
		leaves_count++;
	}
}

void Plant::draw()
{
	const int cx = 100;
	const int cy = 50;
	const int dx = 256;
	const int dy = 256;
	for (int i = 0; i < leaves_count; i++) {
		const Leaf& leaf = leaves[i];
		float angle = std::max(50.0f - leaf.age * 0.2f, 0.0f);
		float scale = std::min(leaf.age * 0.01f, 2.0f);
		al_draw_scaled_rotated_bitmap(im_leaf, cx, cy, dx, dy, scale, scale, angle, 0);
	}
}

