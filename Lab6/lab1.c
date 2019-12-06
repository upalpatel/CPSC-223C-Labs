//Upal Patel
//CPSC 223C - Lab1
#include <stdio.h>
#include "bstrlib.h"

void bump1(int *i, int amount)
{
	*i += amount;
}

int main()
{
	int i = 1;

	printf("%d\n", i);
	bump1(&i, 1);
	printf("%d\n", i);
	bump1(&i, 2);
	printf("%d\n", i);

	bstring s = bfromcstr ("foo");
	printf("%s\n", s->data);
	bconchar(s, 'o');
	printf("%s\n", s->data);
	bconchar(s, 'x');
	printf("%s\n", s->data);

	bdestroy(s);
	return 0;
}
