#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

    //printf("in func - %p\n", node);
    
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
        return;
    }
    print_tree(out, node->left);
    if(node->arg_type == OPERATION) {
        switch(node->data) {
            case ADD_COMAND:
                fprintf(out, "+ ");
                break;
            case SUP_COMAND:
                fprintf(out, "- ");
                break;
            case MUL_COMAND:
                fprintf(out, "* ");
                break;
            case DIV_COMAND:
                fprintf(out, "/ ");
                break;
            default:
                break;
        }
    } else {
        fprintf(out, format, node->data);
    }
    print_tree(out, node->right);
}


Elem_t Eval_tree (NODE* node) {
    if(!node)
        return 0;
    if(node->arg_type == NUMBER) 
        return node->data;
    Elem_t left = Eval_tree(node->left);
    Elem_t right = Eval_tree(node->right);
    switch (node->data)
    {
    case ADD_COMAND:
        return left + right;
        break;
    case SUP_COMAND:
        return left - right;
        break;
    case MUL_COMAND:
        return left * right;
        break;
    case DIV_COMAND:
        if(right == 0)
            return 0;
        return left / right;
    default:
        break;
    }

    return 123123;
}
