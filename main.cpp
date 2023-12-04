#include <stdlib.h>
#include <stdio.h>
#include "Difirinciator.h"
#include "Dump_difirinciator.h"
#include "recursive_descent.h"

int main() {
    NODE* node;
    
    tree_init(&node);

    node = Get_G("2+3");

    int counter = 0;

    make_png_dump("src_tree.dot", node, &counter);

    free_tree(node);
}