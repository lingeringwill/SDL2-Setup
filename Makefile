all:
	gcc -Isrc/Include -Lsrc/lib -o main main.c -g -lmingw32 -lSDL2main -lSDL2