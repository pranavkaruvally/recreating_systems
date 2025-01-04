CC = gcc
CFLAGS = -g3 -c
CFLAGS += -Wall -Wextra -Werror -pedantic -Wunused -Wuninitialized -Wshadow \
        -Wconversion -Wformat -Wfloat-equal -Wunused-parameter -Wunused-result \
        -Wmissing-declarations -Wcast-align -Wlogical-op -Wcast-qual -Wredundant-decls \
        -Wswitch-default -Wnested-externs -Wundef
LDFLAGS = 

SRC=src
OBJECTS=objects
BUILD_DIR=build
DEBUG=$(BUILD_DIR)/debug
RELEASE=$(BUILD_DIR)/release

all: pls

$(OBJECTS)/pls.o: $(SRC)/pls.c
	mkdir -p objects
	$(CC) $(CFLAGS) -o $@ $^

$(DEBUG)/pls: $(OBJECTS)/pls.o
	mkdir -p $(DEBUG)
	$(CC) $(LDFLAGS) -g3 -o $@ $^

$(RELEASE)/pls: $(OBJECTS)/pls.o
	mkdir -p $(RELEASE)
	$(CC) $(LDFLAGS) -O3 -o $@ $^
	strip -s $(RELEASE)/pls

pls: $(DEBUG)/pls

release: $(RELEASE)/pls

clean:
	rm -rf $(OBJECTS) $(BUILD_DIR)

.PHONY: release pls clean
