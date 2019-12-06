//Upal Patel
//CPSC 223C
//Lab1
#include <stdio.h>
#include <string.h>

void bump1(int *i, int amount)
{
    *i += amount;
}

void add(char s[], char c)
{
	int length = strlen(s);
	s[length] = c;
	s[length + 1] = '\0';
}
void bump2(char s[], char c)
{
	add(s, c);
}

int main()
{
    int i = 1;

    printf("%d\n", i);
    bump1(&i, 1);
    printf("%d\n", i);
    bump1(&i, 2);
    printf("%d\n", i);

    char s[5] = "foo";
	
    printf("%s\n", s);
    bump2(s, 'o');
   	printf("%s\n", s);
    bump2(s, 'x');
    printf("%s\n", s);

    return 0;
}

/*
Terminal Commands to run the files:
To run the file:
>cc lab4.c -g -Wall -Wextra -Wpedantic
>./a.out

or
>cc -o lab4run lab4.c -g -Wall -Wextra -Wpedantic
>./lab4run

Debugger:
> gcc -o lab4test lab4.c -ggdb
> gdb lab4test
(gdb) run

Valgrind:
> valgrind --leak-check=full ./a.out
*/
