#include "Chip8.hpp"

Chip8::Chip()
{
    this->pc = START_ADDRESS; // Should start at 0x200

    // Load fonts into beginning memory addresses
    for (int i = 0; i < FONT_SIZE; i++)
    {
        memory[i + FONT_START_ADDRESS] = fonts[i]; 
    }
}

//TODO: implement opcodes
