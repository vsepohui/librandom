#include "random.h"

double csrand() {
	Random *r = new Random;
	return r->get_seed();
}

double crand(double seed, unsigned num) {
	Random *r = new Random(seed);
	return r->rand(num);
}

