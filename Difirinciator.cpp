#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
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
    if((*node)->arg_type == VAR) 
        (*node)->data = 0;
    else
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
    } else if(node->arg_type == VAR) {
        fprintf(out, "X ");
    } else {
        fprintf(out, format, node->data);
    }
    print_tree(out, node->right);
}


Elem_t Eval_tree (NODE* node) {
    if(!node)
        return 0;
    if(node->arg_type == NUMBER) {
        return node->data;
    } if(node->arg_type == VAR) {
        Elem_t var_val = 0;
        printf("\nInput X value:\n");
        scanf("%d", &var_val);
        node->data = var_val;

        return var_val;
    }

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

    return 0;
}

void difirinciate_expression (NODE* node) {

}



// Elem_t parsing_operation(char* str) {
//     if(strcmp(str, "+") == 0) {
//         return ADD_COMAND;
//     } else if (strcmp(str, "-") == 0) {
//         return SUP_COMAND;
//     } else if (strcmp(str, "*") == 0) {
//         return MUL_COMAND;
//     } else if (strcmp(str, "/") == 0) {
//         return DIV_COMAND;
//     }
// }

// static tree_err_type parse_data(FILE* fp, NODE** root) {
//     if(root == nullptr) 
//         return TREE_NO_ERR;

//     const int MAX_WORD_LEN = 50;
//     char word[MAX_WORD_LEN] = "";
//     Elem_t argumnet = ;
    
//     //fscanf(fp, format, word);
//     fscanf(fp, "%s", word);   //Reading '('

//     if(strcmp(word, "(") != 0)
//         printf("IS - ( - %s\n", word);

//     if(strcmp(word, "(") == 0) {
//         //fscanf(fp, format, word);
//         //fprintf(dump_file, "read root: %s\n", word);
//         op_new(root, comand);
//         fprintf(dump_file, "parsing left tree...%s\n", word);
//         parse_data(fp, dump_file, &((*root)->left));
//         fprintf(dump_file, "parsing right tree...%s\n", word);
//         parse_data(fp, dump_file, &((*root)->right));
//         fprintf(dump_file, "finished parsing %s\n", word);
//         fscanf(fp, "%s ", word);
//         //read_word(word, MAX_WORD_LEN, fp);
//     } else if (strcmp(word, "nil") == 0) {
//         *root = nullptr;
//         return TREE_NO_ERR;
//     } else {
//         return TREE_NO_ERR;
//     }
//     return TREE_NO_ERR;
// }

// void read_expression(const char* file_name, NODE** node) {
//     FILE* fp = nullptr;

//     if((fp = fopen(file_name, "r")) == nullptr) {
//         return;
//     }

//     parse_data(fp, node);

//     printf("Loaded succesful\n");

//     return;
// }
