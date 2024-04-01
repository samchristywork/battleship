CC=gcc
CFLAGS=-Isrc/

all: build/battleship

.PHONY: objects
objects: $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

build/%.o: src/%.c
	mkdir -p build
	$(CC) -c $(CFLAGS) $< -o $@

build/battleship: objects
	${CC} build/*.o ${LIBS} -o $@

.PHONY: run
run: build/battleship
	./build/battleship

.PHONY: clean
clean:
	rm -rf build
