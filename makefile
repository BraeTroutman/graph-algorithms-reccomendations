targets=bin/main

.phony: all debug benchmarks
all: $(targets)

debug: bin/debug

benchmarks: bin/strassens_benchmark

bin/strassens_benchmark: build/strassens_benchmark.o build/matmul.o
	cc -o $@ $^

bin/main: build/graph.o build/main.o
	cc -o $@ $^

bin/debug: build/graph.debug.o build/main.debug.o
	cc -o $@ -g $^

build/%.debug.o: src/%.c
	cc -I include -o $@ -g -c $^

build/%.o: src/%.c
	cc -I include -o $@ -c $^

