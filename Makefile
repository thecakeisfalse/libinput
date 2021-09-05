CC      = gcc
AR      = ar
MKDIR   = mkdir
DELETE  = rm

INCLUDE = include
SOURCE  = src
BUILD   = build

CFLAGS  = -std=c89 -I$(INCLUDE) -Wall -Wextra -Werror -pedantic-errors -g

OBJECTS = $(patsubst $(SOURCE)/%.c, $(BUILD)/%.o, $(wildcard $(SOURCE)/*.c))
TARGET  = libinput.a

.PHONY: all build clean

all: help

setup:
	@ $(MKDIR) -p $(BUILD)

build: setup $(TARGET)

clean:
	@ echo [Cleaning]
	@ $(DELETE) -rf $(OBJECTS) $(BUILD) $(LIBRARY)
	@ echo done

test:
	@ echo [Compiling] examples/main.c
	@ $(CC) examples/main.c -o main -I$(INCLUDE) -L. -linput -g
	@ echo done
	@ echo Run './main'

help:
	@ echo "Targets:"
	@ echo "build - compile and build library"
	@ echo "clean - cleanup old .o files"

$(TARGET): $(OBJECTS)
	@ echo [Linking] $@
	@ $(AR) rcs $@ $(OBJECTS)
	@ echo done

$(BUILD)/%.o: $(SOURCE)/%.c
	@ echo [Compiling] $<
	 $(CC) $(CFLAGS) -c $< -o $@
