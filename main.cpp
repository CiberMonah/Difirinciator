#include <stdlib.h>
#include <stdio.h>
#include "Difirinciator.h"
#include "Dump_difirinciator.h"

int main() {
    NODE* node;
    
    tree_init(&node);

    printf("Programm started\n");
    op_new(&node, OPERATION, MUL_COMAND);
    op_new(&node->left, VAR, 0);
    

    //op_new(&node->right, OPERATION, ADD_COMAND);
    op_new(&node->right, NUMBER, 5);
    //op_new(&node->right->left, VAR, 1);

    print_tree(stdout, node);

    int counter = 0;

    printf("= %d\n", Eval_tree(node));

    NODE* dif_node;
    
    tree_init(&dif_node);

    dif_node = difirinciate_expression(node);

    make_png_dump("src_tree.dot", node, &counter);

    simple_tree(&dif_node);

    make_png_dump("dif.dot", dif_node, &counter);

    printf("Eval dif = %d\n", Eval_tree(dif_node));

    free_tree(node);
}