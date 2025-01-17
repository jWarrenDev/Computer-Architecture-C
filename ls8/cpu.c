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

unsigned char readRam(struct cpu *cpu, unsigned char value)
{
  /* data */
  // structure this as a return 
  // change void
  return cpu->ram[value];
};

void cpupush(struct cpu *cpu, unsigned char value)
{
  /* data */
  cpu->registers[7]--; // decrement
  writeRam(cpu, cpu->registers[7], value);
};

unsigned char cpupop(struct cpu *cpu) {
  unsigned char value = readRam(cpu, cpu->registers[7]);
  cpu->registers[7]++;
  return value;
}


/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *loadFile)
{
  
  // TODO: Replace this with something less hard-coded

    FILE *fp = fopen(loadFile, "r");
    char line[1024];
    int address = 0;

 
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char *END;
        unsigned char value = strtoul(line, &END, 2);
        if (END == line)
        {
            continue;
        }
        //writeRam(cpu, address++, value);
        cpu->ram[address++] = value; // ATEHWLEWKKSLKTW~~~~!!!!!!
    }
    
    fclose(fp);

}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{

  unsigned int x = cpu->registers[regA];
  unsigned int y = cpu->registers[regB];

  switch (op) {
    case ALU_MUL:
      cpu->registers[x] *= cpu->registers[y];
      break;

    // TODO: implement more ALU ops
    case ALU_ADD:
      cpu->registers[x] += cpu->registers[y];
      break;

    case ALU_CMP:
        if (cpu->registers[x] == cpu->registers[y]) {
            cpu->flag = 1;
        }
        else {
            cpu->flag = 0;
        }
        cpu->PC = cpu->PC + op + 1;
        break;
       
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
    unsigned char instructionRegister = readRam(cpu, cpu->PC);


    // 2. Figure out how many operands this next instruction requires
    unsigned int numberOperands = instructionRegister >> 6;


    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned char operandA = readRam(cpu, cpu->PC + 1);
    unsigned char operandB = readRam(cpu, cpu->PC + 2);


    // 4. switch() over it to decide on a course of action.

      switch (instructionRegister) {
        case LDI:
          cpu->registers[operandA] = operandB;
          cpu->PC = cpu->PC + numberOperands + 1;
          break;

        case PRN:
         printf("This is the number %d\n", cpu->registers[operandA]);
          cpu->PC = cpu->PC + numberOperands + 1;
          break;

        case MUL: // Multiply the values in two registers together and store the result in registerA.
          cpu->registers[operandA] *= cpu->registers[operandB];
          cpu->PC = cpu->PC + numberOperands + 1;
          break;

        case ADD: //  Bitwise-AND the values in registerA and registerB, then store the result in registerA.
          cpu->registers[operandA] += cpu->registers[operandB];
          cpu->PC = cpu->PC + numberOperands + 1;
          break;

        case PUSH:
          cpupush(cpu, cpu->registers[operandA]);
          cpu->PC = cpu->PC + numberOperands + 1;
          break;

        case POP:
          cpu->registers[operandA] = cpupop(cpu);
          cpu->PC = cpu->PC + numberOperands + 1;
          break;

        case CMP:
           if (cpu->registers[operandA] == cpu->registers[operandB]) {
              cpu->flag = 1;
              } else {
              cpu->flag = 0;
              }
              cpu->PC = cpu->PC + numberOperands + 1;
              break;

        case CALL:
          cpupush(cpu, cpu->PC + 2);
          cpu->PC = cpu->PC + numberOperands + 1;
          break;

        case RET:
          cpu->PC = cpupop(cpu);
          break;
        
        case JMP:
          cpu->PC = cpu->registers[operandA];
          break;

        case JEQ:
          if (cpu->flag == 1) {
           cpu->PC = cpu->registers[operandA];
          } else {
           cpu->PC = cpu->PC + numberOperands + 1;
          }
          break;

        case JNE:
          if (cpu->flag != 1) {
            cpu->PC = cpu->registers[operandA];
            } else {
              cpu->PC = cpu->PC + numberOperands + 1;
            }
            break;

        

        case HLT:
          running = 0;
          break;
        
        default:
        printf("Unexpected instruction 0x%02X at 0%02X\n", instructionRegister, cpu->PC);
           exit(1);
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
   cpu->flag = 0;
  // cpu->ram = 0;
  // cpu->registers = 0;
   cpu->registers[7] = 0xF4;

  // use memset() 
  // void *memset(void *s, int c, size_t n);

  memset(cpu->ram, 0, sizeof(cpu->ram));
  memset(cpu->registers, 0, 8);

}
