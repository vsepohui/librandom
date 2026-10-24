librandom++ - C++ Library for Strong Random!

# API

```
class Random {
	public:
		Random(double seed);
		Random();
		double rand(unsigned num);
		double get_seed();
};
```

# Example

Black-Noise Generator like best /dev/random:

## demo.cpp

```
#include <stdio.h>
#include "random.h"

int main () {
	Random *r = new Random;
	while (1) {
		fputc((char)(int)r->rand(256), stdout);
	}
}

```

## Compile

```
g++ -o demo demo.cpp random++.cpp
```


# Credits

librandom++ developed by Ivan Trunaev, Russia, Uray.
