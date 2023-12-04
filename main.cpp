#include <stdlib.h>
#include <stdio.h>
#include "Difirinciator.h"
#include "Dump_difirinciator.h"
#include "recursive_descent.h"

int main() {
    NODE* node;
    
    tree_init(&node);

    FILE* expression = nullptr;

    if(!(expression = fopen("expression.txt", "r")))
        return -1;

    char str[MAX_LEN_OF_EXPRESSION] = {};

    fscanf(expression,"%s", str);

    node = Get_G(str);

    printf("%s = %d\n", str, Eval_tree(node));

    int counter = 0;

    make_png_dump("src_tree.dot", node, &counter);

    free_tree(node);
}