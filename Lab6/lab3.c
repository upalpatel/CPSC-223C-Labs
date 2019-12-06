//Upal Patel
//CPSC 223C - Lab 3
#include <stdio.h>
#include <stdint.h>
#include "bstrlib.h"

struct byte{
	int line;
	bstring cmd;
	int arg;
};

int main()
{
	int i = 0, j = 0;
	bstring newCMD;
	uint8_t val = 0;
	
	bstring set = bfromcstr("set");
	bstring set2 = bfromcstr("set");
	bstring set3 = bfromcstr("set");
	bstring shl = bfromcstr("shl");
	bstring shl2 = bfromcstr("shl");
	bstring shl3 = bfromcstr("shl");
	bstring or = bfromcstr("or");
	bstring or2 = bfromcstr("or");
	bstring xor = bfromcstr("xor");
	bstring xor2 = bfromcstr("xor");
	bstring and = bfromcstr("and");
	bstring and2 = bfromcstr("and");
	bstring shr = bfromcstr("shr");
	
	struct byte input[13] = 
	{
		{1, set, 1},
		{2, shl, 1},
		{3, shl2, 1},
		{4, or, 1},
		{5, or2, 2},
		{6, shl3, 2},
		{7, xor, 10},
		{8, xor2, 10},
		{9, and, 4},
		{10, set2, 0x1c},
		{11, and2, 3},
		{12, set3, 0x1c},
		{13, shr, 1}
	};
	
	while((newCMD = bgets((bNgetc) fgetc, stdin, '\n')) != NULL)
	{
		if(biseqcstr(newCMD, "list\n") == 1)
		{
			if(i == 0)
			{
				printf(" %d %s %x\n", input[i].line, input[i].cmd->data, input[i].arg);
				printf(" %d %s %x\n", input[i+1].line, input[i+1].cmd->data, input[i+1].arg);
				j = i;
				i++;
				bdestroy(newCMD);
				continue;
			}
			else if (i > 0 && i < 12)
			{
				printf(" %d %s %x\n", input[i-1].line, input[i-1].cmd->data, input[i-1].arg);
				printf(" %d %s %x\n", input[i].line, input[i].cmd->data, input[i].arg);
				printf(" %d %s %x\n", input[i+1].line, input[i+1].cmd->data, input[i+1].arg);
				j = i;
				i++;
				bdestroy(newCMD);
				continue;
			}
			else if(i >= 12)
			{
				printf(" %d %s %x\n", input[i-3].line, input[i-3].cmd->data, input[i-3].arg);
				printf(" %d %s %x\n", input[i-2].line, input[i-2].cmd->data, input[i-2].arg);
				bdestroy(newCMD);
				continue;
			}
		}
		else if(biseqcstr(newCMD, "step\n") == 1)
		{
			if(biseqcstr(input[j].cmd, "set") == 1)
			{
				val = input[j].arg;
			}
			else if(biseqcstr(input[j].cmd, "and") == 1)
			{
				val =  val & input[j].arg;
			}
			else if(biseqcstr(input[j].cmd, "or") == 1)
			{
				val = val | input[j].arg;
			}
			else if(biseqcstr(input[j].cmd, "xor") == 1)
			{
				val = val ^ input[j].arg;
			}
			else if(biseqcstr(input[j].cmd, "shr") == 1)
			{
				val = val >> input[j].arg;
			}
			else if(biseqcstr(input[j].cmd, "shl") == 1)
			{
				val = val << input[j].arg;
			}
		}
		else if(biseqcstr(newCMD, "continue\n") == 1)
		{
			for (int z = j; z < 13; z++)
			{
				if(biseqcstr(input[z].cmd, "set") == 1)
				{
					val = input[z].arg;
					i++;
				}
				else if(biseqcstr(input[z].cmd, "and") == 1)
				{
					val = val & input[z].arg;
					i++;
				}
				else if(biseqcstr(input[z].cmd, "or") == 1)
				{
					val = val | input[z].arg;
					i++;
				}
				else if(biseqcstr(input[z].cmd, "xor") == 1)
				{
					val = val ^ input[z].arg;
					i++;
				}
				else if(biseqcstr(input[z].cmd, "shr") == 1)
				{
					val = val >> input[z].arg;
					i++;
				}
				else if(biseqcstr(input[z].cmd, "shl") == 1)
				{
					val = val << input[z].arg;
					i++;
				}
			}
		}
		else if(biseqcstr(newCMD, "print\n") == 1)
		{
			printf("%x\n", val);
		}
		else if(biseqcstr(newCMD, "quit\n") == 1)
		{
		//	bdestroy(newCMD);
			break;
		}
		else
		{
			printf("Command not valid.\n");
		}
		bdestroy(newCMD);
	}
	
	bdestroy(newCMD);
	bdestroy(set);
	bdestroy(set2);
	bdestroy(set3);
	bdestroy(or);
	bdestroy(or2);
	bdestroy(shl);
	bdestroy(shl2);
	bdestroy(shl3);
	bdestroy(shr);
	bdestroy(xor);
	bdestroy(xor2);
	bdestroy(and);
	bdestroy(and2);
	return 0;
}
