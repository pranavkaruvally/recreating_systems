CC = gcc
CFLAGS = -g3 -c
CFLAGS += -Wall -Wextra -Werror -pedantic -Wunused -Wuninitialized -Wshadow \
        -Wconversion -Wformat -Wfloat-equal -Wunused-parameter -Wunused-result \
        -Wmissing-declarations -Wcast-align -Wlogical-op -Wcast-qual -Wredundant-decls \
        -Wswitch-default -Wnested-externs -Wundef
LDFLAGS = -g3

SRC=src
OBJECTS=objects
BUILD_DIR=build
DEBUG=$(BUILD_DIR)/debug

all: pls

$(OBJECTS)/pls.o: $(SRC)/pls.c
	mkdir -p objects
	$(CC) $(CFLAGS) -o $@ $^

$(DEBUG)/pls: $(OBJECTS)/pls.o
	mkdir -p $(DEBUG)
	$(CC) $(LDFLAGS) -o $@ $^

pls: $(DEBUG)/pls

clean:
	rm -rf $(OBJECTS) $(BUILD_DIR)

.PHONY: pls clean
