#include "symbol_table.h"
symbol_table* table = NULL;
int no_symbols;

int count_symbols(){
    int counter =0;
    for(int i = 0; i < no_lines; i++)
        if (ass_prog[i][0] != NULL)
            counter++;

    return counter;
}
void check_duplicate_symbol(){
    for(int i = 0; i < no_symbols; i++){
        char* s1 = table[i].symbol;

        for(int j = i + 1; j < no_symbols; j++){
            char* s2 = table[j].symbol;

            if (strcmp(s1, s2) == 0){
                printf("error: multiple declaration of '%s' lable in lines %d and %d\n", s1, table[i].adresss + 1, table[j].adresss + 1);
                exit(1);
            }
        }
    }
}
void make_table(){
    no_symbols = count_symbols();
    table = malloc(no_symbols * sizeof(symbol_table));

    int symbol_count = 0;
    for(int i = 0; i < no_lines; i++){
        if (ass_prog[i][0] != NULL){

            strcpy(table[symbol_count].symbol, ass_prog[i][0]);
            table[symbol_count].adresss = i;
            symbol_count++;
        }
    }
    check_duplicate_symbol();
}

int return_address(char* symbol){
    for(int i = 0; i < no_symbols; i++){
        if (strcmp(table[i].symbol, symbol) == 0){
            return table[i].adresss;
        }
    }
    printf("error: '%s' symbol is not defined", symbol);
    exit(1);
}


