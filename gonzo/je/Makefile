first: all

# Known grammars
GRAMMARS = \
	json \
	expr \

# Configuration to compile C sources into objects.
CC = cc -c
CFLAGS += -I../..
CFLAGS += -Wall -Wextra -Wshadow
CFLAGS += -g
# CFLAGS += -O

# Configuration to link objects into executables.
LD = cc
LDFLAGS +=
LDLIBS += -L../.. -ldparse

# Configuration to generate parsers from DParser grammars.
DP = ../../make_dparser
DPFLAGS +=

# This macro will generate all the targets required to build one grammar.
# It also appends dependencies / rules for targets 'all' and 'clean'
define make-grammar-target
  $1_parser.c: $1_parser.g
	$(DP) $(DPFLAGS) -i $1 -o $1_parser.c $1_parser.g

  $1_parser.o: $1_parser.c $1_parser.h
	$(CC) $(CFLAGS) -o $1_parser.o $1_parser.c

  $1_api.o: $1_api.c $1_api.h
	$(CC) $(CFLAGS) -o $1_api.o $1_api.c

  clean::
	rm -f $1_parser.c $1_parser.o $1_api.o
endef

# We can now generate the rules for all listed grammars.
$(foreach grammar,$(GRAMMARS),$(eval $(call make-grammar-target,$(grammar))))
# $(info the grammars are $(GRAMMARS))

# Pattern rule to compile a .c source into its .o object.
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

je: json_parser.o json_api.o expr_parser.o expr_api.o je.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

all:: je

clean::
	rm -f je.o je

# These rules don't actually generate their named target, so they are phony.
.PHONY: all clean
