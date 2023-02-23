targets=bin/demo16

.phony: all debug clean tests
all: $(targets)

debug: bin/debug
tests: test/bin/strassens

test/bin/strassens: build/matrix.o test/build/strassens.o
	cc -o $@ $^

bin/demo16: build/graph.o build/demo16.o build/matrix.o
	cc -o $@ $^

bin/debug: build/graph.debug.o build/main.debug.o build/matrix.debug.o
	cc -o $@ -g $^

build/%.debug.o: src/%.c
	cc -I include -o $@ -g -c $^

build/%.o: src/%.c
	cc -I include -o $@ -c $^

test/build/%.o: test/%.c
	cc -I include -o $@ -c $^

clean: 
	-rm build/* bin/*

