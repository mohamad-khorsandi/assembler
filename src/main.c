#include "main.h"
void read_prog_file(char*);
int count_file_lines(FILE*);
void tokenize(char*, int);
void write_output_file(char*);

char*** ass_prog;
int no_lines;
int max_line_len = 100;

long* mem;

int main(int argc, char **argv)
{
    if(argc < 3){
         printf("wrong number of inputs");
         exit(1);
    }

    read_prog_file(argv[1]);
    make_table();

    mem = malloc(no_lines * sizeof(long));
    make_instruction_list();
    fill_txt_seg();

    write_output_file(argv[2]);
    return 0;
}

void read_prog_file(char* file_name){
    FILE* prog_fp = fopen(file_name, "r");
    if (prog_fp == NULL){
        printf("%s cannot be openned\n", file_name);
        exit(1);
    }
    no_lines = count_file_lines(prog_fp);

    ass_prog = malloc(no_lines * sizeof(char**));
    for (int i = 0; i < no_lines; i++){
        ass_prog[i] = malloc(5 * sizeof(char*));
        for (int j = 0; j < 5; j++){
            ass_prog[i][j] = malloc(7 * sizeof(char));
        }
    }

    char line_buffer[max_line_len];
    for (int i = 0; i < no_lines; i++){
        fgets(line_buffer, max_line_len, prog_fp);
        if ((line_buffer[0] == 0)) continue;

        line_buffer[strcspn(line_buffer, "\n")] = 0;
        tokenize(line_buffer, i);
    }

    fclose(prog_fp);
    prog_fp = NULL;
}

int count_file_lines(FILE* fp){
    char c;
    size_t count = 0;

    while(c != EOF){
        c = fgetc(fp);
        if(c == '\n')
            count++;
    }
    rewind(fp);
    return count;
}

void tokenize(char* line, int line_count){

    char* token;

    token = strtok(line, ", \t");

    int token_counter = 0;

    if (line[0] == ' ' ||  line[0] == '\t'){
        ass_prog[line_count][0] = NULL;
        token_counter++;
    }

    while( token != NULL && token[0] != '#') {
        strcpy(ass_prog[line_count][token_counter], token);
        token = strtok(NULL, ", \t");
        token_counter++;
    }
    ass_prog[line_count][token_counter] = NULL;
}

void write_output_file(char* file_name){

    FILE* output_fp = fopen(file_name, "w+");
    if (output_fp == NULL){
        printf("%s cannot be openned\n", file_name);
        exit(1);
    }

    for(int i = 0; i < no_lines; i++){
        fprintf(output_fp, "%ld\n", mem[i]);
    }
    fclose(output_fp);
    output_fp = NULL;
}
