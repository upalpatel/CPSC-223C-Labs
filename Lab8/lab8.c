//Upal Patel - CS223C - Lab8
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_BYTE_COMMAND_SIZE 3
#define MAX_DEBUG_COMMAND_SIZE 8
#define PROGRAM_SIZE 13

struct node {
	int line;
	char command[MAX_BYTE_COMMAND_SIZE + 1];
	unsigned int argument;

	struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

uint8_t byte = 0;

struct node *create_node(int line, char *command, unsigned int argument)
{
	assert(strlen(command) <= MAX_BYTE_COMMAND_SIZE);
	struct node *new = malloc(sizeof(struct node));
	if (new == NULL) {
		fprintf(stderr, "%s:%d: malloc() returned NULL\n", __FILE__, __LINE__); 
		exit(EXIT_FAILURE);
	}
	new->line = line;
	strcpy(new->command, command);
	new->argument = argument;
	new->next = NULL;

    return new;
}

struct node *append_node(struct node *start, struct node *new)
{
	assert(start != NULL);
	current = start;
	while (current->next != NULL) {
		current = current->next;
    }
	current->next = new;

	return new;
}

void print_node(struct node *n)
{
	printf("%2d %s %x\n", n->line, n->command, n->argument);
}

void print_list(struct node *start)
{
	current = start;
	while (current != NULL) {
		print_node(current);
		current = current->next;
	}
}

void free_list(struct node *start)
{
	struct node *prev;
	current = start;
	while (current != NULL) {
		prev = current;    
		current = current->next;
		free(prev);
	}
}

void do_step()
{
	if (current == NULL) {
		return;
	}
	if (strcmp(current->command, "set") == 0) {
		byte = current->argument;
	} else if (strcmp(current->command, "and") == 0) {
		byte &= current->argument;
	} else if (strcmp(current->command, "or") == 0) {
		byte |= current->argument;
	} else if (strcmp(current->command, "xor") == 0) {
		byte ^= current->argument;
	} else if (strcmp(current->command, "shr") == 0) {
		byte >>= current->argument;
	} else if (strcmp(current->command, "shl") == 0) {
		byte <<= current->argument;
	}
	current = current->next;
}

void do_continue()
{
	while (current != NULL) {
		do_step();
	}
}

void do_vContinue()
{
	while (current != NULL) {
		printf("%s %x => %x\n", current->command, current->argument, byte);
		do_step();
	}
}

void do_print()
{
	printf("%x\n", byte);
}

struct node *find_prev(struct node *start)
{
	struct node *prev = head;
	while (prev->next != start) {
		prev = prev->next;
	}
	return prev;
}

void do_list(struct node *head_2)
{
	if (current == head_2) {
		print_node(current);
		print_node(current->next);
	} else if (current == NULL) {
		struct node *prev = find_prev(current);
		struct node *prevprev = find_prev(prev);

		print_node(prevprev);
		print_node(prev);
	} else {
		struct node *prev = find_prev(current);

		print_node(prev);
		print_node(current);
		print_node(current->next);
	}
}

int main(int argc, char * argv[])
{
	FILE *fp;
	int ver = 0;
	int deb = 0;
	int c = 0;
	char bCMD [MAX_BYTE_COMMAND_SIZE + 1];
	char dCMD [MAX_DEBUG_COMMAND_SIZE + 1];
	unsigned int arg_hex = 0;
	int line = 1;
	
	struct node  *next;
	
	while((c = getopt(argc,argv,"dv"))!= -1) 
	{
		switch(c) {
		case 'd':
			deb = 1;
		break;
		case 'v':
			ver = 1;
		break;
		default:
			abort();
		break;
		}
	
	}

	for(; optind < argc; optind++)
	{
		fp = fopen(argv[optind], "r");
		while(fscanf(fp,"%s %x", bCMD, &arg_hex) != EOF)
		{
			if(line == 1) {
				head = create_node(line++, bCMD, arg_hex);
			} else if(line == 2) {
				next = append_node(head, create_node(line++, bCMD, arg_hex));
			} else {
				next = append_node(next, create_node(line++, bCMD, arg_hex));
			}
		}
		fclose(fp);
	}
	current = head;
	
	if(deb == 1)
	{
		while(scanf("%s", dCMD) != EOF)
		{	
			if(strcmp(dCMD, "step") == 0) {
				do_step();
			} else if(strcmp(dCMD, "continue") == 0) {
				do_continue();
			} else if(strcmp(dCMD, "print") == 0) {
				do_print();
			} else if(strcmp(dCMD, "list") == 0) {
				do_list(head);
			} else if(strcmp(dCMD, "quit") == 0) {
				abort();
			} else {
				printf("invalid");
			}
		}
	}
	if(ver == 1) {
		do_vContinue();
	}
	
	if(ver == 0 && deb == 0) {
		do_continue();
		do_print();
	}
	
	if(deb == 1 && ver == 1) {
		while(scanf("%s", dCMD) != EOF)
		{	
			if(strcmp(dCMD, "step") == 0) {
				do_step();
			} else if(strcmp(dCMD, "continue") == 0) {
				do_continue();
			} else if(strcmp(dCMD, "print") == 0) {
				do_print();
			} else if(strcmp(dCMD, "list") == 0) {
				do_list(head);
			} else if(strcmp(dCMD, "quit") == 0) {
				abort();
			} else {
				printf("invalid");
			}
			do_vContinue();
		}
	}
	
	free_list(head);
	free_list(current);
	
}
