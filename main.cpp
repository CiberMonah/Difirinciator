#include <stdlib.h>
#include <stdio.h>
#include "Difirinciator.h"
#include "Dump_difirinciator.h"


int main() {
    NODE* node;
    
    tree_init(&node);

    printf("Programm started\n");
    op_new(&node, OPERATION, DIV_COMAND);
    //printf("pointer - %p value - %d\n", &node, node->data);
    op_new(&node->left, NUMBER, 1);

    op_new(&node->right, VAR, 2);

    print_tree(stdout, node);

    int counter = 0;

    printf("= %d\n", Eval_tree(node));

    NODE* dif_node;
    
    tree_init(&dif_node);

    dif_node = difirinciate_expression(node);

    make_png_dump("src_tree.dot", node, &counter);

    make_png_dump("dif.dot", dif_node, &counter);

    free_tree(node);
}