#include "instruction.h"
int is_firstC_alphbet(char*);
void fill_data_seg();
inst_types return_type(int);
void print_inst(instructoin*);
int return_opcode(char*);
void set_fields(int);
void constructor(char*, char*, char*, char*, int);

instructoin* inst_list;
int no_inst;

char inst_name_list[15][5]={"add", "sub", "slt", "or", "nand", "addi", "slti", "ori", "lui", "lw", "sw", "beq", "jlar", "j", "halt"};

void make_instruction_list(){
    fill_data_seg();
    inst_list = malloc(no_inst * sizeof(instructoin));

    for(int i = 0; i < no_lines; i++){
        char* name = ass_prog[i][1];
        if (name[0] == '.') continue;

        inst_list[i].name = name;
        inst_list[i].opcode = return_opcode(name);
        inst_list[i].type = return_type(inst_list[i].opcode);
        inst_list[i].line_number = i;

        set_fields(i);
    }

//    for (int i = 0; i < no_inst; i++){
//        print_inst(&(inst_list[i]));
//    }
}

void fill_data_seg(){
    int no_fill = 0;
    for(int i = 0; i < no_lines; i++){
        if (ass_prog[i][1][0] == '.'){
            no_fill++;
            char* val = ass_prog[i][2];

            if (is_firstC_alphbet(val))
                mem[i] = return_address(val);
            else
                mem[i] = atoi(val);
        }
    }
    no_inst = no_lines - no_fill;
}

int is_firstC_alphbet(char* str){
    if (('A' <= str[0] && str[0] <= 'Z') || ('a' <= str[0] && str[0] <= 'z'))
        return 1;
    else
        return 0;
}

inst_types return_type(int opcode){
    if (opcode <= 4) return R;

    if(opcode <= 12) return I;

    if(opcode <= 14) return J;

    printf("an invalid opcode detected: %d", opcode);
    exit(1);
}

int return_opcode(char* inst_name){
    int list_size = sizeof(inst_name_list) / 5;
    for(int i = 0; i < list_size; i++){
        if (strcmp(inst_name_list[i], inst_name) == 0)
            return i;
    }
    printf("error: instruction '%s' is unkown", inst_name);
    exit(1);
}

void set_fields(int i){
    char** cur_line = ass_prog[i];

    switch(inst_list[i].type){
        case R:
            constructor(cur_line[2], cur_line[3], cur_line[4], NULL, i);
        break;

        case I:
            if (strcmp(cur_line[1], "lui") == 0)
                constructor(NULL, "0", cur_line[2], cur_line[3], i);
            else if (strcmp(cur_line[1], "jlar") == 0)
                constructor(NULL, cur_line[3], cur_line[2], "0", i);
            else if (strcmp(cur_line[1], "beq") == 0)
                constructor(NULL, cur_line[2], cur_line[3], cur_line[4], i);
            else
                constructor(NULL, cur_line[3], cur_line[2], cur_line[4], i);
        break;

        case J:
            if (strcmp(cur_line[1], "j") == 0)
                constructor(NULL, NULL, NULL, cur_line[2], i);
            else if (strcmp(cur_line[1], "halt") == 0)
                constructor(NULL, NULL, NULL, "0", i);
        break;
    }
}

void constructor(char* rd, char* rs, char* rt, char* imm, int i){
    instructoin* cur_inst = inst_list + i;

    cur_inst->rd = (rd != NULL)? atoi(rd) : -1;

    cur_inst->rs = (rs != NULL)? atoi(rs) : -1;

    cur_inst->rt = (rt != NULL)? atoi(rt) : -1;

    if (imm != NULL){
        if (is_firstC_alphbet(imm)){
            cur_inst->imm = return_address(imm);
        } else{
            cur_inst->imm = atoi(imm);
        }
    } else{
        cur_inst->imm = 0;
    }

    if (strcmp(cur_inst->name, "beq") == 0)
        cur_inst->imm = cur_inst->imm - cur_inst->line_number - 1;

    if (cur_inst->imm < -32768 || cur_inst->imm > 32767){
        printf("error: immediate value '%d' is not in range", cur_inst->imm);
        exit(1);
    }
}

void print_inst(instructoin* inst){
    if (inst->type == R)
    printf("%d    %d  %d,%d,%d   (R)\n", inst->line_number, inst->opcode, inst->rd, inst->rs, inst->rt);

    else if (inst->type == I)
    printf("%d    %d  %d,%d,%d    (I)\n", inst->line_number, inst->opcode, inst->rt, inst->rs, inst->imm);

    else if (inst->type == J)
    printf("%d    %d  %d         (J)\n", inst->line_number, inst->opcode, inst->imm);
}

void fill_txt_seg(){
    for(int j = 0;  j < no_inst; j++){
        instructoin* inst = inst_list + j;
        long dec_inst;
        switch(inst->type){
            case R:
                dec_inst = inst->rd*pow(2,12) + inst->rt*pow(2,16)
                         + inst->rs*pow(2,20) + inst->opcode*pow(2,28);
            break;

            case I:
                dec_inst = inst->imm + inst->rt*pow(2,16)
                         + inst->rs*pow(2,20) + inst->opcode*pow(2,24);
            break;

            case J:
                dec_inst = inst->imm + inst->opcode*pow(2,24);
            break;
        }
        mem[inst->line_number] = dec_inst;
    }
}




