//Upal Patel - lab7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "faculty.h"

int cmp_for_main(const void *X, const void *Y)
{
	return strcmp(((const struct command*)X)->name, ((const struct command*)Y)->name);
}

int main(int argc, char *argv[])
{
	if(argc == 3) {
		struct command *find_professor;
		find_professor = bsearch(argv[1], commands, NUM_COMMANDS, sizeof(struct command), cmp_for_main);
		if(find_professor != NULL) {
			int point = find_professor->function(argv[2]);
			if(point == -1) {
				printf("No Match.\n");
				return EXIT_FAILURE;
			}
			else {
				printf("%s\n", faculty[point].name);
				printf("%s\n", faculty[point].office);
				printf("%s\n", faculty[point].phone);
				printf("%s\n", faculty[point].email);
				return EXIT_SUCCESS;
			}
		}
		else {
			printf("No Match.\n");
			return EXIT_FAILURE;
		}
	}
	else {
		printf("Usage: phonebook <command> <string>\n");
		return EXIT_FAILURE;
	}
}

