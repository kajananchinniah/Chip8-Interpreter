// Sources:
// https://en.wikipedia.org/wiki/CHIP-8
// https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Technical-Reference

#include <cstdint>
#include <stdio.h>
#include <stdlib.h>

// Constants
const int STACK_LEVEL = 16;
const int MEMORY_SIZE = 4096;
const int NUM_REGS = 16;
const int DISP_LENGTH = 64;
const int DISP_WIDTH = 32;
const int NUM_KEYPADS = 16;

class Chip8
{

    //TODO: decide which members should be public and private
    //temporarily, to simplify, everyone will be public 

    public:
        // 4kb of 8 bit memory
        // Starting address at 0x200. ROM can use 0x200 - 0xFFF basically
        // 0x000 - 0x200 (non-inclusive) should be left alone
        // Somewhere between 0x000 - 0x200 will be used for memory
        // TODO: decide where (I'm thinking first 80 addresses for now)
        // For fonts (0 to F) 
        uint8_t memory[MEMORY_SIZE];


        // 16 8-bit data registers; V0 - VF
        // Avoid using VF (see wikipedia for why; sometimes used as a flag)
        uint8_t registers[NUM_REGS];

        // 16 bit wise address register
        // used for instructions related to memory 
        uint16_t I;

        // timer will count down at 60 Hz until 0
        // NOTE: the 7th and 8th bit are unused 
        // delay timer used for timing events; can be set and read
        uint8_t delay_timer;
        uint8_t sound_timer;

        // hex keyboard that has 16 keys (0 to F)
        uint8_t keypad[NUM_KEYPADS];

        // Graphics display (display is 64x32)
        uint8_t display[DISP_LENGTH][DISP_WIDTH];
        
        // Instructions on chip-8 are 2 bytes long 
        uint16_t opcode;

        //the stack; has 16 levels 
        uint16_t stack[STACK_LEVEL];

        //stack pointer 
        uint16_t sp;

        //program counter
        uint16_t pc;
};




