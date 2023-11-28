#include <stdlib.h>
#include <stdio.h>
#include "Difirinciator.h"


int main() {
    NODE* node;
    
    tree_init(&node);

    printf("Programm started\n");
    op_new(&node, OPERATION, ADD_COMAND);
    printf("pointer - %p value - %d\n", &node, node->data);
    op_new(&node->left, NUMBER, 2);

    op_new(&node->right, NUMBER, 3);

    print_tree(stdout, node);

    free_tree(node);
}