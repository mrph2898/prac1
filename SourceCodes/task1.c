#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node *
lists_cross(const struct Node *L1, const struct Node *L2)
{
    struct Node *L3 = malloc(sizeof(*L3));
    //LCOV_EXCL_START
    if (!L3) {
        puts("There is no memory for List3\n");
        free_list((struct Node *)L1);
        free_list((struct Node *)L2);
        exit(EXIT_FAILURE);
    }
    //LCOV_EXCL_STOP
    struct Node *p3 = L3;    //it's runer point of list
    int flag_first_pointer = 0;
    char *cur_str;
    if ((!L1) || (!L2)) {
        free(L3);
        return NULL;
    } else {
        const struct Node *p1 = L1;
        const struct Node *p2 = L2;
        while (p1) {
            p2 = L2;
            while (p2) {
                if (!strcmp(p1->str, p2->str)) {
                    cur_str = malloc((strlen(p1->str) +1) * sizeof(*cur_str));
                    //LCOV_EXCL_START
                    if (!cur_str) {
                        puts("There is no memory for List3\n");
                        free_list((struct Node *)L1);
                        free_list((struct Node *)L2);
                        exit(EXIT_FAILURE);
                    }
                    //LCOV_EXCL_STOP
                    memcpy(cur_str, p1->str, ((strlen(p1->str) + 1) * sizeof(*cur_str)));
                    if (add_node(&L3, &p3, cur_str, &flag_first_pointer)) { 
                        //LCOV_EXCL_START
                        puts("There is no memory for List3\n");
                        free_list((struct Node *)L1);
                        free_list((struct Node *)L2);
                        if (flag_first_pointer) {
                            free_list(L3);
                        }
                        exit(EXIT_FAILURE);
                        //LCOV_EXCL_STOP
                    }
                }
                p2 = p2->next;
            }
            p1 = p1->next;
        }
        p3->next = NULL;
    }
    if (!flag_first_pointer) {
        free(L3);
        return NULL;
    } else {		
        return L3;		
    }	    
}
