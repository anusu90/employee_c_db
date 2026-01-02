CC = clang
TARGET = ./bin/dbView
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default 
	./$(TARGET)

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $?

obj/%.o: src/%.c
	$(CC) -c $< -o $@ -Iinclude

clean:
	rm -f obj/*.o
	rm -f bin/*
	rm -f *.d