first: all

CFLAGS += -I../..
CFLAGS += -Wall -Wextra -Wshadow
CFLAGS += -g

LDFLAGS += -L../.. -ldparse

D_GRAMMAR = json.g
C_GRAMMAR = $(D_GRAMMAR).d_parser.c
C_DRIVER = $(D_GRAMMAR:.g=.c)
C_EXE = $(C_DRIVER:.c=)

C_SRCS = \
		 $(C_DRIVER) \
		 $(C_GRAMMAR) \

C_OBJS = $(C_SRCS:.c=.o)

%.o: %.c
	cc $(CFLAGS) -c -o $@ $^

$(C_GRAMMAR): $(D_GRAMMAR)
	../../make_dparser $^

$(C_EXE): $(C_OBJS)
	cc -o $@ $^ $(LDFLAGS)

all: $(C_EXE)

clean:
	rm -f $(C_GRAMMAR)
	rm -f *.o
	rm -f $(C_EXE)
