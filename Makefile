CFLAGS := -Wall -Wextra -pedantic -std=c11 -g -ggdb

PROG := main
OBJS := $(PROG).o list.o

all: main

main: $(OBJS)

clean:
	rm -f $(OBJS) $(PROG)
