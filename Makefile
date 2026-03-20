TARGET = pet

$(TARGET):
	gcc -fsanitize=address -g -Wall -Wextra *.c -o pet -lSDL2 -lSDL2_ttf

