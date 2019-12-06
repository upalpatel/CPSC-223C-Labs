#include "commands.h"
#include "faculty.h"
#include <string.h>
#include <stdlib.h>

struct command commands[NUM_COMMANDS] = {
	{ "email",  find_by_email},
	{ "name",   find_by_name },
	{ "office", find_by_office },
	{ "phone",  find_by_phone },
};

int cmp_by_name(const void *X, const void *Y)
{
	return strcmp(((const struct professor*)X)->name, ((const struct professor*)Y)->name);
}
int find_by_name(char *name)
{
	qsort(faculty, NUM_FACULTY, sizeof(struct professor), cmp_by_name);
	struct professor find, *ptr_name;
	strcpy(find.name, name);
	ptr_name = bsearch(&find, faculty, NUM_FACULTY, sizeof(struct professor), cmp_by_name);
	if(ptr_name == NULL) {
		return -1;
	}
	else {
		return ptr_name - faculty;
	}
}

int cmp_by_office(const void *X, const void *Y)
{
	return strcmp(((const struct professor*)X)->office, ((const struct professor*)Y)->office);
}
int find_by_office(char *office)
{
	qsort(faculty, NUM_FACULTY, sizeof(struct professor), cmp_by_office);
	struct professor find, *ptr_office;
	strcpy(find.office, office);
	ptr_office = bsearch(&find, faculty, NUM_FACULTY, sizeof(struct professor), cmp_by_office);
	if(ptr_office == NULL) {
		return -1;
	}
	else {
		return ptr_office - faculty;
	}
}

int cmp_by_phone(const void *X, const void *Y)
{
	return strcmp(((const struct professor*)X)->phone, ((const struct professor*)Y)->phone);
}
int find_by_phone(char *phone)
{
	qsort(faculty, NUM_FACULTY, sizeof(struct professor), cmp_by_phone);
	struct professor find, *ptr_phone;
	strcpy(find.phone, phone);
	ptr_phone = bsearch(&find, faculty, NUM_FACULTY, sizeof(struct professor), cmp_by_phone);
	if(ptr_phone == NULL) {
		return -1;
	}
	else {
		return ptr_phone - faculty;
	}
}

int cmp_by_email(const void *X, const void *Y)
{
	return strcmp(((const struct professor*)X)->email, ((const struct professor*)Y)->email);
}
int find_by_email(char *email)
{
	qsort(faculty, NUM_FACULTY, sizeof(struct professor), cmp_by_email);
	struct professor find, *ptr_email;
	strcpy(find.email, email);
	ptr_email = bsearch(&find, faculty, NUM_FACULTY, sizeof(struct professor), cmp_by_email);
	if(ptr_email == NULL) {
		return -1;
	}
	else {
		return ptr_email - faculty;
	}
}


