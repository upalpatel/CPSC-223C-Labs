//Upal Patel
//CPSC223C - Lab 5
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
	struct stack_element *top;
	int element_count;
};

struct stack_element {
	unsigned char c;
	struct stack_element *next;
};

struct stack *stack_create(void)
{
	struct stack *s = malloc(sizeof(struct stack));
	if (s == NULL) {
		fprintf(stderr, "%s:%d: malloc() returned NULL\n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	s->top = NULL;
	s->element_count = 0;
	return s;
}

void stack_destroy(struct stack *s)
{
	assert(s != NULL);

	struct stack *prev, *current;
	current = s;
	while(current->top != NULL) {
		s->element_count--;
		prev = current;
		current->top = current->top->next;
		free(prev);
	}
	free(s);
}

void stack_push(struct stack *s, unsigned char c)
{
	assert(s != NULL);

	if(s->top == NULL) {
		s->element_count++;
		struct stack_element *temp = malloc(sizeof(struct stack_element));
		temp->c = c;
		temp->next = NULL;
		s->top = temp;

	}
	else {
		s->element_count++;
		struct stack_element *temp = malloc(sizeof(struct stack_element));
		temp->c = c;
		temp->next = s->top;
		s->top = temp;
	}
}

int stack_pop(struct stack *s)
{
	assert(s != NULL);

	unsigned char c;
	struct stack_element *temp = NULL;
	if(s->top != NULL) {
		c = s->top->c;
		temp = s->top;
		s->top = s->top->next;
		free(temp);
		--(s->element_count);
		return c;
	}
	return EOF;
}

int main(int argc, char *argv[])
{
	struct stack *s = stack_create();
	for (int i = argc - 1; i > 0; i--) {
		char *arg = argv[i];
		for (size_t j = 0; j < strlen(arg); j++) {
			stack_push(s, arg[j]);
		}

		char c;
		while ((c = stack_pop(s)) != EOF) {
			printf("%c", c);
		}

		printf(" ");
	}
	printf("\n");

	stack_destroy(s);

	return EXIT_SUCCESS;
}

