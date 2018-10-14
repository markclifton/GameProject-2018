SHELL:=/bin/bash

PROG = $(shell basename $(dir $(abspath $$PWD)))
BUILD = build/
BIN = bin/
RESOURCES = resources/

CC = g++
CPPFLAGS = -g -Wall -std=c++17
LDFLAGS = -lglfw3 -lGLU -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
INCLUDES = -Iengine/

all: pre-build build post-build

pre-build:
	@if ! [ -d "$(BIN)" ]; then mkdir $(BIN); fi
	@if ! [ -d "$(BUILD)" ]; then mkdir $(BUILD); fi
	@./buildStructure $(BUILD)

SOURCE_FILES = $(shell find ./engine -type f -name '*.cpp') main.cpp
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)
%.o : %.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $^ -o $(BUILD)$@

COMPILED_FILES = $(shell find ./$(BUILD) -type f -name '*.o')

build : $(OBJECT_FILES)
	$(CC) $(CPPFLAGS) $(COMPILED_FILES) $(LDFLAGS) $(LIBS) -o $(BIN)$(PROG)

post-build:
	cp -r $(RESOURCES) $(BIN) 

clean:
	@if [ -d "$(BIN)" ]; then rm -r $(BIN); fi
	@if [ -d "$(BUILD)" ]; then rm -r $(BUILD); fi

