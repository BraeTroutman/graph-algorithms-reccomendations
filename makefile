targets=bin/main

.phony: all debug
all: $(targets)

debug: bin/debug

bin/main: build/graph.o build/main.o
	cc -o $@ $^

bin/debug: build/graph.debug.o build/main.debug.o
	cc -o $@ -g $^

build/%.debug.o: src/%.c
	cc -I include -o $@ -g -c $^

build/%.o: src/%.c
	cc -I include -o $@ -c $^

