#include <stdio.h>
#include "random.h"


int main () {
	Random *r = new Random(42.0);
	for (int i = 0 ; i < 1024*1000 ; i ++) {
		double rand = r->rand(256);
		fputc((char)(int)rand, stdout);
	}
}
