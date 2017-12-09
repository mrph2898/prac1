#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int 
is_it_num_in_str(FILE *f, int *is_first_char) 
{
    int c;
    int ans = 0, flag_first_char = 0;
    *is_first_char = 0;
    while ((c = getc(f)) != '\n') { //Не учитываю, когда EOF вместо \n
        if (c == EOF) { return -1; }
        if ((c <= '9') && (c >= '0')) {
            ans = 1;
            flag_first_char = 2;
            continue;
            
        }
        if (!(flag_first_char)) {
            *is_first_char = 1;  
            flag_first_char = 1;
        } 
    }
    return ans;
}

int 
main (int argc, char *argv[])
{   
    if (argc == 1) {
        puts("There is no arguments in one call");
        exit(EXIT_FAILURE);
    } else {
        puts("Program is running..");
    }
    FILE *file;
    long pos1, pos2, print_pos;
    int c, var, first_char_in_str = 0;
    if (!(file = fopen(argv[argc - 1],"r+"))) {
        perror("AccessErr");
        puts("Program can't open file");
        exit(EXIT_FAILURE);
    }
    print_pos = ftell(file);
    while (1) {
        pos1 = ftell(file);
        var = is_it_num_in_str(file, &first_char_in_str); 
        if (var == 1) {
            pos2 = ftell(file);
            fseek(file, pos1, SEEK_SET);
            int sum = 0;
            while ((ftell(file) + 1) < pos2) {
                int num = 0;
                if (first_char_in_str) {            
                    fscanf(file, "%*[^1-9-\n]%d", &num);
                } else {
                    fscanf(file, "%d", &num);
                    first_char_in_str = 1;
                }
                sum += num;
            }
            fseek(file, print_pos, SEEK_SET);
            fprintf(file, "%d\n", sum); 
            print_pos = ftell(file);
            fseek(file, pos2, SEEK_SET);
        } else if (var == 0) {
            pos2 = ftell(file);
            while (pos1 != pos2) {
                fseek(file, pos1, SEEK_SET);
                c = fgetc(file);
                pos1 = ftell(file);
                fseek(file, print_pos, SEEK_SET);
                fputc(c, file);
                print_pos = ftell(file);
            }
            fseek(file, pos2, SEEK_SET);//maybe + 1
        } else { break; }
    }
    fflush(file);
    fclose(file);
    #if (defined(unix) || defined(_unix) || defined(_unix_))
        truncate(argv[argc - 1], print_pos);
    #elif (defined(_WIN32) || defined(_WIN64))
        _ftruncate(argv[argc - 1], print_pos);
    #endif
    puts("End of program");
    return 0;
}
