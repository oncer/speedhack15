#include "common.h"

class Plant
{
public:
	Plant();
	~Plant();
	void update();
	void draw();

	struct Leaf
	{
		Leaf():exists(false){}
		bool exists;
		int age;
		int health;
		bool mirror;
	};

	int age;

private:
	ALLEGRO_BITMAP *im_leaf;
	Leaf *leaves;
	int leaves_count;

};

