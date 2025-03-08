#include <stdio.h>

#include "../src/c_random.h"

int main()
{
	printf("generateRandom(0, 100): %lld\n", generateRandom(0, 100));
	printf("generateRandom(%lld, %lld): %lld\n", INT64_MIN, INT64_MAX, generateRandom(INT64_MIN, INT64_MAX));
	return (0);
}
