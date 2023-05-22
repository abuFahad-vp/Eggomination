CC = clang++
LINKERS = -lglfw -lGL -lGLEW -ldl
FLAGS = -Wall

UTL = src/utils/stb_image.cpp src/utils/Error.cpp
SRC = src/main.cpp 

main: $(UTL) $(SRC)
	$(CC) $(FLAGS) $(SRC) $(UTL) -o build/main $(LINKERS)

run:
	build/main

clean:
	rm main
