#include "struct.h"
#include <string.h>

void 
free_list(struct Node *L)
{
    if (L) {
        struct Node *p = L;
        while (p) {
            free(p->str);
            L = L->next;
            free(p);
            p = L;
        }
    }
}

char *
read_line (FILE * f)
{
    unsigned int str_size =  BUF_SIZE, move = 0;
    int flag = 1, more_then_once = 0;
    char *global_line, *tmp;
    if (!(tmp = calloc (str_size + 1, sizeof(*tmp)))) {
        //LCOV_EXCL_START
        return NULL;
        //LCOV_EXCL_STOP
    }
    global_line = tmp;  
    flag = 1;
    while (flag && fgets(global_line + move, str_size + 1, f)) {
        for(unsigned int i = move; flag && i < (str_size + move); i++) {
            if (global_line[i] == '\n' ) {
                global_line[i + 1] = '\0';
                flag = 0;
            }
        }   
        if (flag) {
            if (more_then_once) {
                str_size = str_size * 2;
            }
            move = str_size; 
            if (!(tmp = realloc (global_line, (2 * str_size + 1) * (sizeof(*global_line))))) {
                //LCOV_EXCL_START
                free(global_line);   
                return NULL;
                //LCOV_EXCL_STOP
            }   
            global_line = tmp;
        }
        more_then_once = 1;
    }
    if (!more_then_once) {
        free(tmp);
        return NULL;
    }
    if ((tmp = realloc(global_line, (strlen(global_line) + 1) * sizeof(*global_line)))) {
        global_line = tmp;
    }
    return global_line;
}
        
int
add_node(struct Node **L, struct Node **run_p, char *in_str, int *flag)
{
    struct Node *new_elem;
    if (!*flag) {
        (*L)->str = in_str;
        *run_p = *L;
        (*run_p)->next = NULL;
        *flag = 1;
    } else {
        if (!(new_elem = malloc(sizeof(*new_elem)))) {
            //LCOV_EXCL_START
            return -1;
            //LCOV_EXCL_STOP
        }
        new_elem->str = in_str;
        new_elem->next = NULL;
        (*run_p)->next = new_elem;
        *run_p = (*run_p)->next;
    }
    return 0;
}    

#define ASSERT(cond) do { if (!(cond)) goto FAIL; } while(0)

struct Node *
read_list(FILE *f) 
{
    struct Node *L = malloc(sizeof(*L));
    //LCOV_EXCL_START
    ASSERT(L);
    //LCOV_EXCL_STOP
    struct Node *p = L;    
    char *cur_str;
    int flag_first_pointer = 0;
    printf("All is ready for reading elements of list\n");
    printf("Elements parts with ENTER\n");
    while ((cur_str = read_line(f))) {
        ASSERT(add_node(&L, &p, cur_str, &flag_first_pointer) == 0);
    }	
    if (!flag_first_pointer) {
        free(L);
        return NULL;
    } else {
        return L;    
    }
//LCOV_EXCL_START
FAIL:
    perror(0);
    free_list(L);
    exit(EXIT_FAILURE);
//LCOV_EXCL_STOP
}

void 
write_list(struct Node *L)
{
    struct Node *p = L;
    if (!p) { 
        puts("Number of the same elements = 0");
    } else {
        puts("Same elements are:");
        while (p) {
            printf("%s\n",p->str);
            putchar('\n');
            p = p->next;
        }
    }
}
