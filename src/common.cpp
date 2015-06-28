#include "common.h"
#include <time.h>

static uint32_t _xorshift_register;

static void _rng_next()
{
	_xorshift_register ^= _xorshift_register >> 12;
	_xorshift_register ^= _xorshift_register << 25;
	_xorshift_register ^= _xorshift_register >> 27;
}

void rng_init()
{
	_xorshift_register = time(0);
}

float rng_random()
{
	_rng_next();
	return _xorshift_register / ((float)0xffffffff);
}

int rng_random(int max)
{
	_rng_next();
	return _xorshift_register % max;
}

int rng_random(int min, int max)
{
	return min + rng_random(max - min + 1);
}

