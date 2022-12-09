#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM_STRINGS 180

struct node {
    char *value[NUM_STRINGS];
    int num;            
    struct node *p_left;
    struct node *p_right;
    int len;
};