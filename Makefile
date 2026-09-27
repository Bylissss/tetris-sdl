all:
	gcc -o tetris tetris.c -lSDL3

clean:
	rm -rf bin

.PHONY: clean all
