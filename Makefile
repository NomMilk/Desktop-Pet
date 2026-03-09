SRC = $(wildcard *.c)

TARGET = game

$(TARGET): $(SRC)
	g++ $(SRC) -o $(TARGET) -lSDL2
