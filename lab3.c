//Upal Patel
//CPSC 223C
//Lab 3
#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct byte{
	int line;
	char cmd[5];
	int arg;
};

int main()
{
	int i = 0, j = 0;
	char newCMD[10];
	uint8_t val = 0;
	
	struct byte input[13] = 
	{
		{1, "set", 1},
		{2, "shl", 1},
		{3, "shl", 1},
		{4, "or", 1},
		{5, "or", 2},
		{6, "shl", 2},
		{7, "xor", 10},
		{8, "xor", 10},
		{9, "and", 4},
		{10, "set", 0x1c},
		{11, "and", 3},
		{12, "set", 0x1c},
		{13, "shr", 1}
	};

	while(scanf("%s", newCMD) == 1)
	{
		if(strcmp(newCMD, "list") == 0)
		{
			if(i == 0)
			{
				printf(" %d %s %x\n", input[i].line, input[i].cmd, input[i].arg);
				printf(" %d %s %x\n", input[i+1].line, input[i+1].cmd, input[i+1].arg);
				j = i;
				i++;
				continue;
			}
			else if (i > 0 && i < 12)
			{
				printf(" %d %s %x\n", input[i-1].line, input[i-1].cmd, input[i-1].arg);
				printf(" %d %s %x\n", input[i].line, input[i].cmd, input[i].arg);
				printf(" %d %s %x\n", input[i+1].line, input[i+1].cmd, input[i+1].arg);
				j = i;
				i++;
				continue;
			}
			else if(i >= 12)
			{
				printf(" %d %s %x\n", input[i-3].line, input[i-3].cmd, input[i-3].arg);
				printf(" %d %s %x\n", input[i-2].line, input[i-2].cmd, input[i-2].arg);
				continue;
			}
		}
		else if(strcmp(newCMD, "step") == 0)
		{
			if(strcmp(input[j].cmd, "set") == 0)
			{
				val = input[j].arg;
			}
			else if(strcmp(input[j].cmd, "and") == 0)
			{
				val =  val & input[j].arg;
			}
			else if(strcmp(input[j].cmd, "or") == 0)
			{
				val = val | input[j].arg;
			}
			else if(strcmp(input[j].cmd, "xor") == 0)
			{
				val = val ^ input[j].arg;
			}
			else if(strcmp(input[j].cmd, "shr") == 0)
			{
				val = val >> input[j].arg;
			}
			else if(strcmp(input[j].cmd, "shl") == 0)
			{
				val = val << input[j].arg;
			}
		}
		else if(strcmp(newCMD, "continue") == 0)
		{
			for (int z = j; z < 13; z++)
			{
				if(strcmp(input[z].cmd, "set") == 0)
				{
					val = input[z].arg;
					i++;
				}
				else if(strcmp(input[z].cmd, "and") == 0)
				{
					val = val & input[z].arg;
					i++;
				}
				else if(strcmp(input[z].cmd, "or") == 0)
				{
					val = val | input[z].arg;
					i++;
				}
				else if(strcmp(input[z].cmd, "xor") == 0)
				{
					val = val ^ input[z].arg;
					i++;
				}
				else if(strcmp(input[z].cmd, "shr") == 0)
				{
					val = val >> input[z].arg;
					i++;
				}
				else if(strcmp(input[z].cmd, "shl") == 0)
				{
					val = val << input[z].arg;
					i++;
				}
			}
		}
		else if(strcmp(newCMD, "print") == 0)
		{
			printf("%x\n", val);
		}
		else if(strcmp(newCMD, "quit") == 0)
		{
			break;
		}
		else
		{
			printf("Command not valid.\n");
		}
	}
	return 0;
}
