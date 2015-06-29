#include "plant.h"
#include <algorithm>
#include <cmath>

static const int MAX_NODES = 64;

Plant::Plant()
{
	nodes = new Node[MAX_NODES];
	nodes_count = 0;
	Node *n = create_node(Node::TYPE_STEM, 400, 400, 400, 400);
	Node *n1 = create_node(Node::TYPE_STEM, 400, 400, 400, 350);
	n1->parent = n;
	n1->splits = 5;
	n1->leaf_splits = 2;
	age = 0;
}

Plant::~Plant()
{
	delete[] nodes;
}

void Plant::update()
{
	age++;
	for (int i = 0; i < nodes_count; i++) {
		Node& n = nodes[i];
		n.age++;
		float dx = n.target_x - n.x;
		float dy = n.target_y - n.y;
		float sine_x = std::cos(n.age * 0.01f + n.sine_offset) * n.sine_multi;
		float sine_y = std::sin(n.age * 0.01f + n.sine_offset) * n.sine_multi * 0.5f;

		const float growth = 0.01;
		n.x += (dx + sine_x) * growth;
		n.y += (dy + sine_y) * growth;
		if (n.sine_multi > std::max(5.0f, growth)) n.sine_multi -= growth;
		if (n.radius > 0 && n.splits <= 0) {
			if (n.type == Node::TYPE_STEM) {
				n.radius += growth * (1.0 - n.radius / 10);
			} else if (n.type == Node::TYPE_HEAD) {
				n.radius += growth * (1.0 - n.radius / 30);
			} else if (n.type == Node::TYPE_LEAF && !n.end) {
				n.radius += growth * (1.0 - n.radius / 20);
			}
		}

		const float limit = n.sine_multi * n.sine_multi + 16;
		if (dx*dx < limit && dy*dy < limit) {
			switch (n.type) {
				case Node::TYPE_STEM:
					if (n.splits > 0) {
						int type = n.type;
						if (n.splits == 1) {
							type = Node::TYPE_HEAD;
						}
						Node *n1 = create_node(type, n.x, n.y, 
								n.target_x + rng_random(-5, 5), n.target_y - 35 - rng_random() * 15);
						n1->splits = n.splits - 1;
						n1->parent = &n;
						n.splits = 0;

						if (n1->splits > 0 && rng_random() < 0.6f) {
							n1->leaf_splits = 2;
						}
					}

					if (n.leaf_splits > 0 && rng_random(100) == 0) {
						int offset_x = 50 + rng_random() * 20;
						int offset_y = -30 - rng_random() * 10;
						if (n.flip) offset_x = -offset_x;
						n.flip = !n.flip;
						n.leaf_splits--;
						n.age = 0;
						Node *n1 = create_node(Node::TYPE_LEAF, n.x, n.y,
								n.x + offset_x, n.y + offset_y);
						n1->parent = &n;
						n1->splits = 1;
					}
					break;
				case Node::TYPE_LEAF:
					if (n.splits > 0) {
						Node *n1 = create_node(n.type, n.x, n.y,
								n.target_x + (n.target_x - n.start_x), n.target_y + 30 + rng_random() * 20);
						n1->parent = &n;
						n1->splits = n.splits - 1;
						n1->end = n1->splits <= 0;
						n.splits = 0;
					}
					break;
			}
		}
	}
}

void Plant::draw()
{
	for (int i = 0; i < nodes_count; i++) {
		nodes[i].drawn = false;
	}
	for (int i = nodes_count; i >= 0; i--) {
		Node* n0 = &nodes[i];
		Node* n1 = n0->parent;
		float n0_radius = n0->radius;
		if (n1 && !n0->drawn) {
			n0->drawn = true;
			ALLEGRO_COLOR color;
			switch (n0->type) {
				case Node::TYPE_HEAD:
				case Node::TYPE_STEM:
					color = al_map_rgb(0, 255, 0); break;
				case Node::TYPE_LEAF:
					color = al_map_rgb(100, 255, 100); break;
			}
			ALLEGRO_COLOR node_color;
			switch (n0->type) {
				case Node::TYPE_HEAD:
					node_color = al_map_rgb(255 - rng_random(20), 255 - rng_random(20), 0); break;
					n0_radius = n1->radius;
					break;
				case Node::TYPE_STEM:
					node_color = al_map_rgb(0, 255, 0); break;
				case Node::TYPE_LEAF:
					node_color = al_map_rgb(100, 255, 100); break;
			}
			draw_connection(n0->x, n0->y, n0_radius + 1,
					n1->x, n1->y, n1->radius + 1, color);
			al_draw_filled_circle(n0->x, n0->y, n0->radius, node_color);
			al_draw_filled_circle(n1->x, n1->y, n1->radius, color);
		}
	}
}

void Plant::draw_connection(float x0, float y0, float radius0,
		float x1, float y1, float radius1,
		ALLEGRO_COLOR color)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	float len = std::sqrt(dx*dx + dy*dy);
	float dxn = 0, dyn = 0;
	if (len > 0) {
		dxn = dx / len;
		dyn = dy / len;
	}
	float norm0_x = -dyn;
	float norm0_y = dxn;
	float norm1_x = dyn;
	float norm1_y = -dxn;

	float p0_x = x0 + norm0_x * radius0;
	float p0_y = y0 + norm0_y * radius0;
	float p1_x = x1 + norm0_x * radius1;
	float p1_y = y1 + norm0_y * radius1;
	float p2_x = x1 + norm1_x * radius1;
	float p2_y = y1 + norm1_y * radius1;
	float p3_x = x0 + norm1_x * radius0;
	float p3_y = y0 + norm1_y * radius0;
	al_draw_filled_triangle(p0_x, p0_y, p1_x, p1_y, p2_x, p2_y, color);
	al_draw_filled_triangle(p0_x, p0_y, p2_x, p2_y, p3_x, p3_y, color);
}

Plant::Node *Plant::create_node(int type, float x, float y, float target_x, float target_y)
{
	if (nodes_count + 1 < MAX_NODES) {
		Node* n = &nodes[nodes_count++];
		n->type = type;
		n->x = n->start_x = x;
		n->y = n->start_y = y;
		n->target_x = target_x;
		n->target_y = target_y;
		float dx = n->target_x - n->x;
		float dy = n->target_y - n->y;
		float d = std::sqrt(dx*dx + dy*dy);
		n->sine_multi = rng_random() * d * 0.5f;
		n->sine_offset = rng_random() * 2 * M_PI;
		n->radius = 0.01;
		return n;
	}

	return NULL;
}

Plant::Node::Node():
	exists(false), drawn(false),
	flip(false),
	end(false),
	type(Node::TYPE_STEM),
	age(0),
	x(0), y(0),
	target_x(0), target_y(0),
	sine_multi(0), sine_offset(0),
	splits(0), leaf_splits(0),
	radius(0), parent(NULL)
{
}


