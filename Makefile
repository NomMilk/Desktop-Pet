SRC = $(wildcard *.c)

TARGET = pet

$(TARGET): $(SRC)
	g++ $(SRC) -o $(TARGET) -lSDL2 -lSDL2_ttf
