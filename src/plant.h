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
		int type;
		int age;
		int health;
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
	Node *create_node(int type, int x, int y, int target_x, int target_y);
	Node *nodes;
	int nodes_count;

};

