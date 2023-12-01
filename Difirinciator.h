#ifndef DIFIRINCIATOR_H_INCLUDED
#define DIFIRINCIATOR_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

typedef int Elem_t;
#define format "%d"

enum Arg_t {
    NUMBER      = 1 << 1,
    OPERATION   = 1 << 2,
    VAR         = 1 << 3,
};

struct NODE {
    Arg_t arg_type;
    Elem_t data;
    NODE* left;
    NODE* right;
};

//This about values if it is OPERATION value

const Elem_t ADD_COMAND = 1 << 1;
const Elem_t SUP_COMAND = 1 << 2;
const Elem_t MUL_COMAND = 1 << 3;
const Elem_t DIV_COMAND = 1 << 4;
const Elem_t LOG_COMAND = 1 << 5;

enum tree_err_type {
    TREE_NO_ERR           = 0,

    TREE_MEM_ALLOC_ERR   = 1 << 0,
    TREE_FILE_OPEN_ERR   = 1 << 1,
    WRONG_ARGS_ERROR     = 1 << 2,
};

void tree_init(NODE** node);
void free_tree(NODE* node);
tree_err_type op_new(NODE** node, Arg_t arg_t, Elem_t value);
void print_tree (FILE* out, NODE* node);
Elem_t Eval_tree (NODE* node);

NODE* difirinciate_expression(NODE* node);
void simple_tree(NODE* node);

#endif