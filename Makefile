CC=g++
EXECUTABLE=main.exe
SRC=./src
BIN=./bin
PPD=-DGLEW_STATIC
FLAGS=-static-libgcc -static-libstdc++
LIBS=-lmingw32 -lSDL2main -lSDL2 -lopengl32
SDL_DIR=C:/SDL2-2.0.3/x86_64-w64-mingw32
SDL_PATHS=-I$(SDL_DIR)/include/ -L $(SDL_DIR)/lib/

all:
	$(CC) $(FLAGS) $(PPD) -o $(BIN)/$(EXECUTABLE) $(SRC)/main.cpp $(SRC)/glew.c $(SDL_PATHS) $(LIBS)
	
run:
	$(BIN)/$(EXECUTABLE)
	
clean:
	rm -rf $(BIN)/*
