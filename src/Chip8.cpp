#include "Chip8.hpp"

Chip8::Chip8()
{
    this->pc = START_ADDRESS; // Should start at 0x200
    this->sp = -1; // Starts at -1 because of the way it's implemented

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
    //TODO 
    // Get opcode; retrieve the instruction to execute from memory
    // Each instruction is 2 bytes, which is why it's extracted this way
    this->opcode = this->memory[this->pc] << 8 | this->memory[this->pc + 1];

    // Decode opcode
    
    // Execute opcode
    
    // Update timer


}

//TODO: implement opcodes
// Below are all the opcodes that are implemented
// See the links mentioned in the Chip8.hpp for more details 

void Chip8::OP_00E0()
{
    // clear display 
    memset(this->display, 0, DISP_LENGTH * DISP_WIDTH);
}

void Chip8::OP_00EE()
{
    // Set pc to address at top of stack and then subtract 1 from sp 
    this->pc = this->stack[this->sp];
    this->sp--;
}

void Chip8::OP_1NNN()
{
    // Extract the address from the opcode; address is the first 3 nibbles
    uint16_t address = this->opcode & 0xFFF; 

    //Set pc as that address
    this->pc = address; 
}

void Chip8::OP_2NNN()
{
    //Place program counter into the stack
    this->sp++;
    this->stack[this->sp] = this->pc;

    // Extract the address and then set the pc to it
    uint16_t address = this->opcode & 0xFFF;
    this->pc = address;
}

void Chip8::OP_3XNN()
{
    // Extract the register in question
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Extract the value to compare to
    uint8_t value = this->opcode & 0x00FF;

    if (this->registers[reg_idx] == value)
    {
        this->pc += 2; // Skip next instruction
    }
}

void Chip8::OP_4XNN()
{
    // Extract the register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Extract the value to compare to
    uint8_t value = this->opcode & 0x00FF;

    if (this->registers[reg_idx] != value)
    {
        this->pc += 2; // Skip next instruction 
    }
}

void Chip8::OP_5XY0()
{
    // Extract the registers 
    uint8_t reg_idx1 = (this->opcode & 0x0F00) >> 8;
    uint8_t reg_idx2 = (this->opcode & 0x00F0) >> 4;

    // If both registers have same value, increment pc by 2
    if (this->registers[reg_idx1] == this->registers[reg_idx2])
    {
        this->pc += 2;
    }
}

void Chip8::OP_6XNN()
{
    // Extract the register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Extract the value to put into said register
    uint8_t value = this->opcode & 0x00FF;

    //Set the register to have the value 
    this->registers[reg_idx] = value;
}

void Chip8::OP_7XNN()
{
    // Extract the register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Extract the value to be added
    uint8_t value = this->opcode & 0x00FF;

    // Add the extracted value to the current register
    this->registers[reg_idx] += value;
}

void Chip8::OP_8XY0()
{
    // Extract the two registers 
    uint8_t reg_idx1 = (this->opcode & 0x0F00) >> 8;
    uint8_t reg_idx2 = (this->opcode & 0x00F0) >> 4;

    // Overwrite one of the registers with the other one
    this->registers[reg_idx1] = this->registers[reg_idx2];
}

void Chip8::OP_8XY1()
{
    // Extract the two registers
    uint8_t reg_idx1 = (this->opcode & 0x0F00) >> 8;
    uint8_t reg_idx2 = (this->opcode & 0x00F0) >> 4;

    // Overwrite one of the registers with the bitwise OR of both
    this->registers[reg_idx1] = this->registers[reg_idx1] | this->registers[reg_idx2];
}

void Chip8::OP_8XY2()
{
    // Extract the two registers
    uint8_t reg_idx1 = (this->opcode & 0x0F00) >> 8;
    uint8_t reg_idx2 = (this->opcode & 0x00F0) >> 4;

    // Overwrite one of the registers with the bitwise AND of both
    this->registers[reg_idx1] = this->registers[reg_idx1] & this->registers[reg_idx2];
}

void Chip8::OP_8XY3()
{
    // Extract the two registers
    uint8_t reg_idx1 = (this->opcode & 0x0F00) >> 8;
    uint8_t reg_idx2 = (this->opcode & 0x00F0) >> 4;

    // Overwrite one of the registers with the bitwise XOR of both
    this->registers[reg_idx1] = this->registers[reg_idx1] ^ this->registers[reg_idx2];
}

void Chip8::OP_8XY4()
{
    // Extract the two registers
    uint8_t reg_idx1 = (this->opcode & 0x0F00) >> 8;
    uint8_t reg_idx2 = (this->opcode & 0x00F0) >> 4;

    //Add both together and overwrite one of the registers. If result > 255, VF = 1 otherwise 0
    //Only keep the lowest 8 bits 

    uint16_t sum = this->registers[reg_idx1] + this->registers[reg_idx2];
    if (sum > 255)
    {
        this->registers[15] = 1; // VF = 1
    }

    else
    {
        this->registers[15] = 0; // VF = 0
    }

    this->registers[reg_idx1] = sum & 0xFF; // keep only the lowest 8 bits
}

void Chip8::OP_8XY5()
{
   // Extract the two registers
   uint8_t reg_idx1 = (this->opcode & 0x0F00) >> 8;
   uint8_t reg_idx2 = (this->opcode & 0x00F0) >> 4;

   // If reg_idx1 > reg_idx2, the set VF to 1; 0 otherwise
   if (this->registers[reg_idx1] > this->registers[reg_idx2])
   {
       this->registers[15] = 1; // VF = 1
   }

   else
   {
       this->registers[15] = 0; // VF = 0
   }

   // Subtract reg_idx2 from reg_idx1 and str the result in reg_idx1
   this->registers[reg_idx1] = this->registers[reg_idx1] - this->registers[reg_idx2];
}

void Chip8::OP_8XY6()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Write least significant bit into VF
    this->registers[15] = registers[reg_idx] & 0x1;

    // Divide the extracted register by 2
    registers[reg_idx] = registers[reg_idx] >> 1;
}

void Chip8::OP_8XY7()
{
    // Extract the two registers
    uint8_t reg_idx1 = (this->opcode & 0x0F00) >> 8;
    uint8_t reg_idx2 = (this->opcode & 0x00F0) >> 4;

    // If register reg_idx2 > register reg_idx1, then VF = 1. 0 Otherwise
    if(this->registers[reg_idx2] > this->registers[reg_idx1])
    {
        this->registers[15] = 1; // VF = 1
    }

    else
    {
        this->registers[15] = 0; // VF = 0
    }

    // Subtract register reg_idx1 = register reg_idx2 - register reg_idx1
    this->registers[reg_idx1] = this->registers[reg_idx2] - this->registers[reg_idx1];
}

void Chip8::OP_8XYE()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Write most significant bit into VF
    this->registers[15] = (this->registers[reg_idx] & 0x80) >> 7;

    // Multiply register reg_idx by 2 
    this->registers[reg_idx] = this->registers[reg_idx] << 1;
}

void Chip8::OP_9XY0()
{
    // Extract the two registers
    uint8_t reg_idx1 = (this->opcode & 0x0F00) >> 8;
    uint8_t reg_idx2 = (this->opcode & 0x00F0) >> 4;

    // If not equal, increment pc by 2 
    if (this->registers[reg_idx1] != this->registers[reg_idx2])
    {
        this->pc += 2;
    }
}

void Chip8::OP_ANNN()
{
    // Extract the value
    uint16_t value = this->opcode & 0x0FFF; 

    //Write it to the I register
    this->I = value;
}

void Chip8::OP_BNNN()
{
    // Extract memory location
    uint16_t address = this->opcode & 0x0FFF;

    // Set pc to address + value of register 0
    this->pc = address + this->registers[0];
}

void Chip8::OP_CXNN()
{
    //TODO: should look into a better method of random number generation
    this->rand_num = rand() % 256; // random number from 0-255

    // Extract the value and register 
    uint8_t value = this->opcode & 0x00FF; 
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;
    this->registers[reg_idx] = rand_num & value; // bitwise AND the value and random number into the register
}

void Chip8::OP_DXYN()
{
    //TODO: I have no idea how to do this one for now
}

void Chip8::OP_EX9E()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;
    uint8_t key = this->registers[reg_idx]; // value located in register

    if (keypad[key] == true) // was keypad located at register hit? 
    {
        this->pc += 2; // increment pc by 2 if yes
    }
}

void Chip8::OP_EXA1()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;
    uint8_t key = this->registers[reg_idx]; // key located in the register

    if (keypad[key] == false) // if value located in the register wasn't hit, increment pc by 2 
    {
        this->pc += 2;
    }
}

void Chip8::OP_FX07()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Set value of register equal to delay timer
    this->registers[reg_idx] = this->delay_timer;
}

void Chip8::OP_FX0A()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;
    for (int i = 0; i < 16; i++) // only 15 possible keys
    {
        // Valid key pad was hit, write that into reg, then exit
        if (keypad[i] == true)
        {
            this->registers[reg_idx] = i;
            return;
        }
    }

    // Redo the previous instruction
    this->pc = this->pc - 2;
}

void Chip8::OP_FX15()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Set the value of delay timer equal to value of register
    this->delay_timer = this->registers[reg_idx];
}

void Chip8::OP_FX18()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Set the value of the sound timer equal to value of register
    this->sound_timer = this->registers[reg_idx];
}

void Chip8::OP_FX1E()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Set I equal to extracter register + I
    this->I += this->registers[reg_idx];
}

void Chip8::OP_FX29()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;

    // Set I equal to the location of the hexadecimal sprite corrosponding to the value of the extracted register
    this->I = FONT_START_ADDRESS + this->registers[reg_idx];

}

void Chip8::OP_FX33()
{
    // Extract register
    uint8_t reg_idx = (this->opcode & 0x0F00) >> 8;
    uint8_t value = this->registers[reg_idx];

    // Place hundreds digit in memory location starting at I, tens in I+1 and ones in I+2 

    for (int i = 2; i >= 0; i--)
    {
        this->memory[this->I + i] = value % 10;
        value = value / 10;
    }
}

void Chip8::OP_FX55()
{
    // Extract stopping register
    uint8_t reg_stop_idx = (this->opcode & 0x0F00) >> 8;

    // Write into memory starting at address I the values from registers R0 to R_reg_stop_idx
    for (int i = 0; i <= reg_stop_idx; i++)
    {
        this->memory[this->I + i] = this->registers[i];
    }
}

void Chip8::OP_FX65()
{
    // Extract stopping register
    uint8_t reg_stop_idx = (this->opcode & 0x0F00) >> 8;

    // Write into the registers the values in memory starting at address I
    for (int i = 0; i <= reg_stop_idx; i++)
    {
        this->registers[i] = this->memory[this->I + i];
    }
}
