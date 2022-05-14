#ifndef SYMBOL_TABLE_H_INCLUDED
#define SYMBOL_TABLE_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include "main.h"

typedef struct symbol_table{
    char symbol[7];
    int adresss;
}symbol_table;

void make_table();
int return_address(char*);

#endif // SYMBOL_TABLE_H_INCLUDED
