FILENAME = main

#OBJS specifies which files to compile as part of the project
OBJS = src\main.cpp src\Tile.cpp src\Block.cpp src\Text.cpp src\util.cpp

PIECE_FILE_LIST = src\Piece.cpp src\S_Piece.cpp src\T_Piece.cpp src/Z_Piece.cpp
#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\MinGW\include\SDL2 -I.
#INCLUDE_PATHS = -I include -IC:\MinGW\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\MinGW\lib
#LIBRARY_PATHS = -L lib -LC:\MinGW\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
# ONLY DO THIS WHEN YOU DON'T WANT ERRORS IN CONSOLE.
#COMPILER_FLAGS = -w -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = exe\tetris.exe

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(PIECE_FILE_LIST) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
