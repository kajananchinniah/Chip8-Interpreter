#include "Chip8.hpp"

Chip8::Chip8()
{
    this->pc = START_ADDRESS; // Should start at 0x200

    // Load fonts into beginning memory addresses
    for (int i = 0; i < FONT_SIZE; i++)
    {
        memory[i + FONT_START_ADDRESS] = fonts[i]; 
    }
}

void Chip8::load()
{
    //TODO
}

void Chip8::cycle()
{
    // Get opcode; retrieve the instruction to execute from memory
    this->opcode = this->memory[this->pc] << 8 | this->memory[this->pc + 1];

    // Decode opcode
    
    // Execute opcode
    
    // Update timer


}

//TODO: implement opcodes

