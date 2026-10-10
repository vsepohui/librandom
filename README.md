librandom++ - C++ Library for Strong Random!

# API

```
class Random {
	public: 
		Random(double seed);
		double rand(unsigned num);
};
```

# Example

Black-Noise Generator like best /dev/random:

## demo.ccp

```
#include <stdio.h>
#include "random.h"

int main () {
	Random *r = new Random(42.0);
	for (int i = 0 ; i < 1024*1000 ; i ++) {
		double rand = r->rand(256);
		fputc((char)(int)rand, stdout);
	}
}

```

## Compile

```
g++ -o demo demo.cpp random.cpp
```


# Credits

librandom++ developed by Ivan Trunaev, Russia, Uray.
