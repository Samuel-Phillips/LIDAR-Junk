# vim: ft=make
CC := gcc
CFLAGS := -Werror -Wall -Wextra -std=c99 -Wfatal-errors -Wno-overflow \
	-Wno-pointer-sign -Wno-format
SRC := las.c
OBJ := $(SRC:.c=.o)

.PHONY: all

all: las

las: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

-include .depends

.depends: $(SRC)
	-rm $@
	@for src in $^; do \
		echo "Making rule for $$src"; \
		cpp -MM -MG $$src >> $@; \
		echo '	$$(CC) $$(CFLAGS) -c -o $$@ $$^' >> $@;\
	done
