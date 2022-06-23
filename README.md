# assembler
assembler for a simple assembly language similar to mips assembly(see test cases in io/ dir to see the syntax of this assmbly language).

this program generates machine code which can be used as input of <a href="https://github.com/mohamad-khorsandi/cpu-simulation.git">cpu simulation</a> program that executes the assembly code.

- compile:
```
gcc main.c symbol_table.c instruction.c -o assmbler
```

- run:
```
./assmbler input output
```
use test cases in io/ dir as input.
also this assmbler ditects some errors(test cases in io-err/ produce error).
