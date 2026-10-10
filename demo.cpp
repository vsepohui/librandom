#include <stdio.h>
#include <stdlib.h>
#include "random.h"


int main () {
	Random *r = new Random(121305500.9112345678);
	while (1) {
		double rand = r->rand(256);
		//printf("%d\n", (int) rand);
		fputc((char)(int)rand, stdout);
	}
}
