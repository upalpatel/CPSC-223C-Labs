//Upal Patel
//CPSC 223C
//Lab 2
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main()
{
	uint8_t val = 0;
	unsigned int arg = 0;
	char str[3];
	
	while(scanf("%s %x", str, &arg) != EOF)
	{
		if(strcmp(str, "set") == 0)
		{
			val = arg;
			printf("set %x => %x\n", arg, val);
		}
		else if(strcmp(str, "and") == 0)
		{
			val &= arg;
			printf("and %x => %x\n", arg, val);
		}
		else if(strcmp(str, "or") == 0)
		{
			val |= arg;
			printf("or %x => %x\n", arg, val);
		}
		else if(strcmp(str, "xor") == 0)
		{
			val ^= arg;
			printf("xor %x => %x\n", arg, val);
		}
		else if(strcmp(str, "shr") == 0)
		{
			val = val >> arg;
			printf("shr %x => %x\n", arg, val);
		}
		else if(strcmp(str, "shl") == 0)
		{
			val = val << arg;
			printf("shl %x => %x\n", arg, val);
		}
		else
		{
			printf("Please enter the right command.");
		}
	}
	return 0;
}
