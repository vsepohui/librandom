#include <stdio.h>
#include <stdlib.h>
#include "random.h"


int main () {
	Random *r = new Random(42.0);
	for (int i = 0 ; i < 16 ; i ++) {
		double rand = r->rand(256);
		printf("%d\n", (int) rand);
		//fputc((char)(int)rand, stdout);
	}
}
