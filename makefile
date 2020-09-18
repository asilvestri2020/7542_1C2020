#OBJS specifies which files to compile as part of the project
OBJS = src/Main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -ljsoncpp -lX11 -lXrandr -lXi -lXxf86vm -lGL

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME =src/main

#This is the target that compiles our executable

SRC_DIR := src
OBJ_DIR := src

all :
	$(CC) $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
