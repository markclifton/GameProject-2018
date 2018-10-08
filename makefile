SHELL:=/bin/bash

PROG = GameProject
BUILD = build/
BIN = bin/

CC = g++
CPPFLAGS = -g -Wall -std=c++14
LDFLAGS = -lglfw3 -lGLU -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl

all: pre-build build post-build

pre-build:
	@if ! [ -d "$(BIN)" ]; then mkdir $(BIN); fi
	@if ! [ -d "$(BUILD)" ]; then mkdir $(BUILD); fi
	@./buildStructure $(BUILD)

SOURCE_FILES = $(shell find ./ -type f -name '*.cpp')
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)
%.o : %.cpp
	$(CC) -c $^ -o $(BUILD)$@

COMPILED_FILES = $(shell find ./$(BUILD) -type f -name '*.o')

build : $(OBJECT_FILES)
	$(CC) $(COMPILED_FILES) $(LDFLAGS) $(LIBS) -o $(BIN)$(PROG)

post-build: 

clean:
	@if [ -d "$(BUILD)" ]; then rm -r $(BUILD); fi
