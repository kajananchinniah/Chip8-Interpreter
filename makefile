# set compiler here
CC := g++

# any flags 
CFLAGS := -std=c++11 `pkg-config --cflags --libs sdl2`

# headers here 
HDRS := src/Chip8.hpp src/GUI.hpp src/fonts.hpp

# source files here 
SRCS := src/main.cpp src/Chip8.cpp src/GUI.cpp 

# Exec name here 
EXEC := Chip8.sh 

# recipe for building the final executable
all: $(EXEC)

$(EXEC): makefile
	$(CC) $(SRCS) -o $@ $(CFLAGS)

# clean workspace 
clean:
	rm -f $(EXEC) 

.PHONY: all clean
