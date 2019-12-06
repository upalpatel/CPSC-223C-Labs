
CC=gcc
CFLAGS = -g -std=c11 -Wall -Wextra -Wpedantic -Werror \
	-Wfloat-equal -Wlogical-op -Wshadow -Wswitch-default \
	-Wbad-function-cast -Wcast-qual -Waggregate-return \
	-fno-diagnostics-show-option -D_POSIX_C_SOURCE=200801L

PROG = calculator
SRCS = lab8.c

OBJS = $(SRCS:.c=.o)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(PROG)

lab8.o: lab8.c

clean:
	rm -f core $(PROG) $(OBJS)
