#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#define DATA_LEN 6
#include <string.h>

// Step 2
// In cpu.c, add functions cpu_ram_read() and cpu_ram_write() that access the RAM inside the struct cpu.

// write the RAM
void writeRam(struct cpu *cpu, unsigned char value, unsigned char index)
{
  /* data */
  cpu->ram[index] = value;

};

// read the RAM

unsigned char readRam(struct cpu *cpu, unsigned char value, unsigned char index)
{
  /* data */
  // structure this as a return 
  // change void
  return cpu->ram[value] = index;
};




/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}



// Step 4
// Implement the core of cpu_run()

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    
    // unsigned char instructionRegister = cpu->PC;
    unsigned char instructionRegister = cpu_ram_read(cpu, cpu->PC);


    // 2. Figure out how many operands this next instruction requires
    // How?? 


    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned char operandA = cpu_ram_read(cpu, cpu->PC +1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->PC +2);

    // 4. switch() over it to decide on a course of action.

    switch (instructionRegister) 
    {
    case HLT:
      running = 0;
      break;
    
    default:
      break;
    }

    // 5. Do whatever the instruction should do according to the spec.

    // 6. Move the PC to the next instruction.

  }
}

// Step 3. 
/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  // set to 0
  cpu->PC = 0;
  cpu->ram = 0;
  cpu->registers = 0;

  // use memset() 
  // void *memset(void *s, int c, size_t n);

}
