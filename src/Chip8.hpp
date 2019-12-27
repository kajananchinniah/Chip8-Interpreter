// Sources:
// https://en.wikipedia.org/wiki/CHIP-8
// https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Technical-Reference
// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
// http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/

#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <fstream> // for reading files
#include <string>

//Include the fonts array and fonts size
#include "fonts.hpp"

// Constants related to variables
const unsigned int STACK_LEVEL = 16;
const unsigned int MEMORY_SIZE = 4096;
const unsigned int NUM_REGS = 16;
const unsigned int DISP_LENGTH = 64;
const unsigned int DISP_WIDTH = 32;
const unsigned int NUM_KEYPADS = 16;

//Constants used in .cpp file
const unsigned int START_ADDRESS = 0x200;
const unsigned int FONT_START_ADDRESS = 0x0;

class Chip8
{

    //TODO: decide which members should be public and private
    //temporarily, to simplify, everyone will be public 

    public:
        Chip8();
        void load();
        void cycle();
        void selectOpcode();
        int rand_num;


        // 4kb of 8 bit memory
        // Starting address at 0x200. ROM can use 0x200 - 0xFFF basically
        // 0x000 - 0x200 (non-inclusive) should be left alone
        // Somewhere between 0x000 - 0x200 will be used for memory
        // 0x00 - 0x50 will be used for fonts (0 to F) 
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
        bool keypad[NUM_KEYPADS];

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
        
        /* Functions for the instruction set / opcode codes for the Chip8
         * will be implemented below.
         * Wikipedia contains a list of all the opcodes and what they do
         * https://en.wikipedia.org/wiki/CHIP-8
         * NOTE: I'm not implementing 0NNN
         * 
         * This resource contains a more detailed description of what each
         * opcode does, which made it easier to implement certain opcodes
         * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
         */

        void OP_00E0();
        void OP_00EE();
        void OP_1NNN();
        void OP_2NNN();
        void OP_3XNN();
        void OP_4XNN();
        void OP_5XY0();
        void OP_6XNN();
        void OP_7XNN();
        void OP_8XY0();
        void OP_8XY1();
        void OP_8XY2();
        void OP_8XY3();
        void OP_8XY4();
        void OP_8XY5();
        void OP_8XY6();
        void OP_8XY7();
        void OP_8XYE();
        void OP_9XY0();
        void OP_ANNN();
        void OP_BNNN();
        void OP_CXNN();
        void OP_DXYN();
        void OP_EX9E();
        void OP_EXA1();
        void OP_FX07();
        void OP_FX0A();
        void OP_FX15();
        void OP_FX18();
        void OP_FX1E();
        void OP_FX29();
        void OP_FX33();
        void OP_FX55();
        void OP_FX65();
};




