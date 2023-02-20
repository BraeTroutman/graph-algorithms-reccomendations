targets=bin/main

.phony: all
all: $(targets)

bin/main: build/graph.o build/main.o
	cc -o $@ $^

build/%.o: src/%.c
	cc -I include -o $@ -c $^

