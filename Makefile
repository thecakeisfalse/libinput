# Makefile

AR = ar
CC = gcc
MKDIR = mkdir
MSG = echo
REMOVE = rm

INCLUDE = include
SOURCE = src
BUILD = build

CFLAGS = -std=c89 -Wall -Wextra -pedantic-errors -Werror -I $(INCLUDE) -g

SOURCES := $(wildcard $(SOURCE)/*.c)
OBJECTS := $(patsubst $(SOURCE)/%.c, $(BUILD)/%.o, $(SOURCES))
LIBRARY = libinput.a

Q = @

.PHONY: all build clean

all: help

setup:
	$(Q) $(MKDIR) -p $(BUILD)

build: setup $(LIBRARY)

clean:
	$(Q) $(MSG) [Cleaning]
	$(Q) $(REMOVE) -rf $(OBJECTS) $(BUILD) $(LIBRARY)
	$(Q) $(MSG) done

test:
	$(Q) $(MSG) [Compiling] examples/main.c
	$(Q) $(CC) examples/main.c -o main -I$(INCLUDE) -L. -linput
	$(Q) $(MSG) done
	$(Q) $(MSG) Run './main'

help:
	$(Q) $(MSG) "Targets:"
	$(Q) $(MSG) "build - compile and build library"
	$(Q) $(MSG) "clean - cleanup old .o files"

$(LIBRARY): $(OBJECTS)
	$(Q) $(MSG) [Linking] $@
	$(Q) $(AR) rcs $@ $(OBJECTS)
	$(Q) $(MSG) done

$(BUILD)/%.o: $(SOURCE)/%.c
	$(Q) $(MSG) [Compiling] $<
	$(Q) $(CC) $(CFLAGS) -c $< -o $@
