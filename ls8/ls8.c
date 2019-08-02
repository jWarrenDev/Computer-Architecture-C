#include <stdio.h>
#include "cpu.h"

/**
 * Main
 */
int main(int argc, char *argv[])
{
  struct cpu cpu;
  char *loadFile = argv[1];

  if (argc != 2){
    return 1;
  }

  cpu_init(&cpu);
  cpu_load(&cpu, loadFile);
  cpu_run(&cpu);

  return 0;
}