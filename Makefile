CC = clang
TARGET = ./bin/dbView
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default 
	./$(TARGET)

default: $(TARGET)

$(TARGET): $(OBJ) | bin
	$(CC) -o $@ $?

obj/%.o: src/%.c | obj
	$(CC) -c $< -o $@ -Iinclude


obj:
	mkdir -p obj

bin:
	mkdir -p bin

clean:
	rm -f obj/*.o
	rm -f bin/*
	rm -f *.db