# Chip8-Interpreter

A Chip8 interpreter written in C++. Currently there is no sound and the interpreter seems reasonably laggy. Nonetheless from my tests, it's in a usable state. 

I've only tested the emulator on Pong and Tetris. Necessary ROMs to use the interpreter can be found online.

So far, I've only compiled on Ubuntu. Not sure if this will work on other platforms.

Chip8 keypad -> keyboard mapping:

1 -> 1

2 -> 2

3 -> 3

C -> 4

4 -> Q

5 -> W

6 -> E

D -> R

7 -> A

8 -> S

9 -> D

E -> F

A -> Z

0 -> X

B -> C

F -> V 

Future plans:
- Add sound
- Possibly aim for computation speedup 
- Code cleanup

In the src file, compile with:
g++ *.cpp -std=c++11 $(pkg-config --cflags --libs sdl2)

Usage after compilation:
./output_file path_to_ROM

Resources consulted:
- https://en.wikipedia.org/wiki/CHIP-8
- https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Technical-Reference
- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
- http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
- https://github.com/tlively/sdl_seminar
- https://wiki.libsdl.org/SDL_Scancode

