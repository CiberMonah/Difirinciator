#include <stdlib.h>
#include <stdio.h>
#include "Difirinciator.h"
#include "Dump_difirinciator.h"


int main() {
    NODE* node;
    
    tree_init(&node);

    printf("Programm started\n");
    op_new(&node, OPERATION, ADD_COMAND);
    //printf("pointer - %p value - %d\n", &node, node->data);
    op_new(&node->left, NUMBER, 2);

    op_new(&node->right, NUMBER, 3);

    print_tree(stdout, node);

    int counter = 0;

    make_png_dump("dif.dot", node, &counter);

    printf("= %d\n", Eval_tree(node));

    free_tree(node);
}