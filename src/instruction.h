#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "symbol_table.h"

typedef enum inst_types{
    R = 1, I = 2, J = 3
}inst_types;
typedef struct instructoin{
    inst_types type;
    char* name;
    int opcode;
    int rs;
    int rt;
    int rd;
    int imm;
    int line_number;
}instructoin;

void make_instruction_list();
void fill_txt_seg();

#endif // INSTRUCTION_H_INCLUDED
