CC=g++
EXECUTABLE=main.exe
SRC=./src
BIN=./bin
PPD=-DGLEW_STATIC -DGLM_FORCE_RADIANS
FLAGS=-static-libgcc -static-libstdc++ -std=c++11
LIBS=-lmingw32 -lSDL2main -lSDL2 -lopengl32
SDL_DIR=C:/SDL2-2.0.3/x86_64-w64-mingw32
GLM_DIR=C:/glm
INC_PATHS=-I$(SDL_DIR)/include/ -I$(GLM_DIR)/
LIB_PATHS=-L$(SDL_DIR)/lib/

all:
	$(CC) $(FLAGS) $(PPD) -o $(BIN)/$(EXECUTABLE) $(SRC)/*.cpp $(SRC)/glew.c $(INC_PATHS) $(LIB_PATHS) $(LIBS)
	
run:
	$(BIN)/$(EXECUTABLE)
	
clean:
	rm -rf $(BIN)/*
