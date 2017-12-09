#include "struct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
test_func(char *f1, char *f2)
{
    FILE *f[2];
    f[0] = fopen(f1,"r");
    struct Node *L1 = read_list(f[0]);
    fclose(f[0]);
    f[1] = fopen(f2,"r");
    struct Node *L2 = read_list(f[1]);
    fclose(f[1]);
    struct Node *L3 = lists_cross(L1,L2);
    free_list(L1);
    free_list(L2);
    write_list(L3);
    free_list(L3);
}

int 
main(void) {
    test_func("./Tests/T1/1.txt","./Tests/T1/1.txt");
    test_func("./Tests/T1/1.txt","./Tests/T1/2.txt");
    test_func("./Tests/T1/2.txt","./Tests/T1/1.txt");
    test_func("./Tests/T1/3.txt","./Tests/T1/4.txt");
    test_func("./Tests/T1/3.txt","./Tests/T1/5.txt");
    return 0;
}

