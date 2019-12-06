//Upal Patel
//CPSC 223C - Lab 4
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_SIZE 3

struct node {
    int line;
    char command[MAX_COMMAND_SIZE + 1];
    unsigned int argument;

    struct node *next;
};

struct node *create_node(int line, char *command, unsigned int argument)
{
    assert(strlen(command) <= MAX_COMMAND_SIZE);

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

    struct node *current = start;
    
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
    struct node *current = start;
	print_node(current);
}

struct node *create_list(void)
{
    struct node *head, *next;
    int line = 1;

    head = create_node(line++, "set", 0x1);
    next = append_node(head, create_node(line++, "shl", 0x1));
    next = append_node(next, create_node(line++, "shl", 0x1));
    next = append_node(next, create_node(line++, "or", 0x1));
    next = append_node(next, create_node(line++, "or", 0x2));
    next = append_node(next, create_node(line++, "shl", 0x2));
    next = append_node(next, create_node(line++, "xor", 0x10));
    next = append_node(next, create_node(line++, "xor", 0x10));
    next = append_node(next, create_node(line++, "and", 0x4));
    next = append_node(next, create_node(line++, "set", 0x1c));
    next = append_node(next, create_node(line++, "and", 0x3));
    next = append_node(next, create_node(line++, "set", 0x1c));
    next = append_node(next, create_node(line++, "shr", 0x1));

    return head;
}

void free_list(struct node *start)
{
    struct node *prev, *current;

    current = start;
    while (current != NULL) {
        prev = current;    
        current = current->next;
        free(prev);
    }
}

int main(void)
{
	char newCMD[9];
	uint8_t byteVal = 0;

    struct node *head = create_list();
	struct node *prev, *current;
	prev = current = head;
	int ln = 0;
	ln = head->line;

	while(scanf("%s", newCMD) == 1) {
		if(strcmp(newCMD, "list") == 0) {
			if(ln == 1) {
				print_list(current);
				print_list(current->next);
				ln++;
			}
			else if (ln > 1 && ln < 14) {
				current = head;
				while(current->line != ln) {
					prev = current;
					current = current->next;
				}
				if(ln == 13) {
					print_list(prev);
					print_list(current);
				}
				else {
					print_list(prev);
					print_list(current);
					print_list(current->next);
					prev = prev->next;
				}
				ln++;
			}
			else if(ln >= 14) {
				current = head;
				while(current->line != ln - 1) {
					prev = current;
					current = current->next;
				}
				print_list(prev);
				print_list(current);
			}
		}
		else if(strcmp(newCMD, "step") == 0) {
			if(strcmp(current->command, "set") == 0) {
				byteVal = current->argument;
			}
			else if(strcmp(current->command, "and") == 0) {
				byteVal =  byteVal & current->argument;
			}
			else if(strcmp(current->command, "or") == 0) {
				byteVal = byteVal | current->argument;
			}
			else if(strcmp(current->command, "xor") == 0) {
				byteVal = byteVal ^ current->argument;
			}
			else if(strcmp(current->command, "shr") == 0) {
				byteVal = byteVal >> current->argument;
			}
			else if(strcmp(current->command, "shl") == 0) {
				byteVal = byteVal << current->argument;
			}
			current = current->next;
		}
		else if(strcmp(newCMD, "continue") == 0) {
			current = head;
			while(current->line != ln) {
				current = current->next;
			}
			for (int z = ln; z < 14; z++) {
				if(strcmp(current->command, "set") == 0) {
					byteVal = current->argument;
				}
				else if(strcmp(current->command, "and") == 0) {
					byteVal =  byteVal & current->argument;
				}
				else if(strcmp(current->command, "or") == 0) {
					byteVal = byteVal | current->argument;
				}
				else if(strcmp(current->command, "xor") == 0) {
					byteVal = byteVal ^ current->argument;
				}
				else if(strcmp(current->command, "shr") == 0) {
					byteVal = byteVal >> current->argument;
				}
				else if(strcmp(current->command, "shl") == 0) {
					byteVal = byteVal << current->argument;
				}
				current = current->next;
				ln++;
			}
		}
		else if(strcmp(newCMD, "print") == 0) {
			printf("%x\n", byteVal);
		}
		else if(strcmp(newCMD, "quit") == 0) {
			break;
		}
		else {
			printf("Command not valid.\n");
		}
	}
	
	free_list(head);
    return EXIT_SUCCESS;
}
