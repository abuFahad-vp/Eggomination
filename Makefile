CC = clang++
LINKERS = -lglfw -lGL -lGLEW -ldl
FLAGS = -Wall

UTL = src/utils/stb_image.cpp
SRC = src/main.cpp
OBJ = src/obj/glad.o

main: $(UTL) $(SRC)
	$(CC) $(FLAGS) $(SRC) $(OBJ) $(UTL) -o build/main $(LINKERS)

run:
	build/main

clean:
	rm main
