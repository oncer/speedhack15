#pragma once
#include "common.h"

class Plant
{
public:
	Plant();
	~Plant();
	void update();
	void draw();

	struct Node
	{
		enum {
			TYPE_STEM,
			TYPE_LEAF,
			TYPE_HEAD
		};
		Node();
		bool exists;
		bool drawn;
		bool flip;
		bool end;
		int type;
		int age;
		float x, y;
		float start_x, start_y;
		float target_x, target_y;
		float sine_multi;
		float sine_offset;
		int splits;
		int leaf_splits;
		float radius;
		Node *parent;
	};

	int age;

private:
	void draw_connection(float x0, float y0, float radius0,
			float x1, float y1, float radius1,
			ALLEGRO_COLOR color);

	Node *create_node(int type, float x, float y, float target_x, float target_y);
	Node *nodes;
	int nodes_count;

};

