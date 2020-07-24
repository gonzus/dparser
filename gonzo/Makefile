first: all

# List of programs we know about.
PROGS = \
	4calc \
	json \
	expr \

# Configuration to compile C sources into objects.
CC = cc -c
CFLAGS += -I..
CFLAGS += -Wall -Wextra -Wshadow
CFLAGS += -g
# CFLAGS += -O

# Configuration to link objects into executables.
LD = cc
LDFLAGS +=
LDLIBS += -L.. -ldparse

# Configuration to generate parsers from DParser grammars.
DPARSER = ../make_dparser
# DParser suffix
DPS = d_parser

# This macro will generate all the targets required to build one program.
# It also appends dependencies / rules for targets 'all' and 'clean'
define make-prog-target
  $1/$1.g.$(DPS).c: $1/$1.g
	$(DPARSER) $1/$1.g

  $1/$1: $1/$1.g.$(DPS).o $1/$1.o
	$(LD) $(LDFLAGS) -o $1/$1 $1/$1.g.$(DPS).o $1/$1.o $(LDLIBS)

  all:: $1/$1

  clean::
	rm -f $1/$1.g.$(DPS).c $1/$1.g.$(DPS).o $1/$1.o $1/$1
endef

# We can now generate the rules for all listed programs.
$(foreach prog,$(PROGS),$(eval $(call make-prog-target,$(prog))))
# $(info the progs are $(PROGS))

# Pattern rule to compile a .c source into its .o object.
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

# Rule to update .gitignore -- cheap enough so that we can afford to run it
# every time we run the 'all' target, and let git find out if anything changed.
gitignore:
	@rm -f .gitignore; for p in $(PROGS); do echo $$p/$$p >> .gitignore; done
all:: gitignore

# These rules don't actually generate their named target, so they are phony.
.PHONY: all clean gitignore
