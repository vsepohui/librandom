#include <stdio.h>
#include "random.h"


int main () {
	Random *r = new Random(42.0);
	while (1) {
		fputc((char)(int)r->rand(256), stdout);
	}
}
