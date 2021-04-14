# Makefile

AR = ar
CC = gcc
MKDIR = mkdir
MSG = echo
REMOVE = rm

INCLUDE_DIRECTORY = include
SOURCE_DIRECTORY = src
BUILD_DIRECTORY = build

CFLAGS = -std=c89 -Wall -Wextra -pedantic-errors -Werror -I $(INCLUDE_DIRECTORY) -g

SOURCES := $(wildcard $(SOURCE_DIRECTORY)/*.c)
OBJECTS := $(patsubst $(SOURCE_DIRECTORY)/%.c, $(BUILD_DIRECTORY)/%.o, $(SOURCES))
LIBRARY = libinput.a

Q = @

.PHONY: all build clean

all: help

setup:
	$(Q) $(MKDIR) -p $(BUILD_DIRECTORY)

build: setup $(LIBRARY)

clean:
	$(Q) $(MSG) [Cleaning]
	$(Q) $(REMOVE) -rf $(OBJECTS) $(BUILD_DIRECTORY)
	$(Q) $(MSG) done

test:
	$(Q) $(MSG) [Compiling] examples/main.c
	$(Q) $(CC) examples/main.c -o main -I$(INCLUDE_DIRECTORY) -L. -linput
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

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c
	$(Q) $(MSG) [Compiling] $<
	$(Q) $(CC) $(CFLAGS) -c $< -o $@
