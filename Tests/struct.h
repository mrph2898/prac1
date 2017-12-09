#ifndef _STRUCT_H_
#define _STRUCT_H_ 
    #include <stdio.h>
    #include <stdlib.h>   
    enum {BUF_SIZE = 8};
    struct Node 
    {
    	struct Node *next;
    	char *str;
    };
    struct Node *lists_cross(const struct Node *, const struct Node *);
    void free_list(struct Node *);    
    int add_node(struct Node **, struct Node **, char *, int *);
    void write_list(struct Node *);    
    struct Node *read_list(FILE *);
#endif
