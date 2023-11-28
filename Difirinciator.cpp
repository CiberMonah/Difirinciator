#include <stdlib.h>
#include <stdio.h>
#include "Difirinciator.h"

void free_tree(NODE* node) {
    if(!node) {
        return;
    }

    free_tree(node->left);
    free_tree(node->right);
    free(node);

    return;
}

static tree_err_type node_ctor(NODE** node) {

    *node = (NODE*)calloc(1, sizeof(NODE));

    if(!(*node))
        return TREE_MEM_ALLOC_ERR;
    return TREE_NO_ERR;
}

tree_err_type op_new(NODE** node, Arg_t arg_t, Elem_t value) {

    if(node_ctor(node) == TREE_MEM_ALLOC_ERR) {
        return TREE_MEM_ALLOC_ERR;
    }

    printf("in func - %p\n", node);
    
    (*node)->arg_type = arg_t;
    (*node)->data = value;
    (*node)->left = nullptr;
    (*node)->right = nullptr;

    //printf("node->data = %d\n", node->data);
    
    return TREE_NO_ERR;
}

void tree_init(NODE** node) {
    op_new(node, NUMBER, 0);
}


//In this program we only need print "in order"
void print_tree (FILE* out, NODE* node) {
     if(!node) {
        fprintf(out, "nil ");
        return;
    }
    fprintf(out, "( ");
    print_tree(out, node->left);
    fprintf(out, format, node->data);
    print_tree(out, node->right);
    fprintf(out, ") ");
}