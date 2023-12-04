#include "recursive_descent.h"

const char* s;
int p = 0;

NODE* Get_N() {
    int val = 0;
    NODE* new_node = 0;

    while('0' <= s[p] && s[p] <= '9') {
        val = val * 10 + s[p] - '0';
        p++;
    }

    op_new(&new_node, NUMBER, val);

    return new_node;
}

NODE* Get_G(const char* str) {
    s = str;
    p = 0;

    NODE* new_node = Get_E();

    return new_node;
}

NODE* Get_E() {
   
    
    NODE* new_node1 = Get_T();
    NODE* op_node = 0;

    char op = 0;

    while(s[p] == '+' || s[p] == '-') {
        op = s[p];
        p++;

        NODE* new_node2 = Get_T();

        switch (op)
        {
        case '+':
            op_new(&op_node, OPERATION, ADD_COMAND);
            op_node->left = new_node1;
            op_node->right = new_node2;
            new_node1 = op_node;
            break;
        case '-':
            op_new(&op_node, OPERATION, SUP_COMAND);
            op_node->left = new_node1;
            op_node->right = new_node2;
            new_node1 = op_node;
            break;
        default:
            err;
            break;
        }
    }

    return new_node1;
}


NODE* Get_T() {
    NODE* new_node1 = Get_P();
    char op = 0;

    while(s[p] == '*' || s[p] == '/') {
        op = s[p];
        p++;

        NODE* op_node = 0;

        NODE* new_node2 = Get_P();

        switch (op)
        {
        case '*':
            op_new(&op_node, OPERATION, MUL_COMAND);
            op_node->left = new_node1;
            op_node->right = new_node2;
            new_node1 =  op_node;
            break;
        case '/':
            op_new(&op_node, OPERATION, DIV_COMAND);
            op_node->left = new_node1;
            op_node->right = new_node2;
            new_node1 =  op_node;
            break;
        default:
            err;
            break;
        }
    }

    return new_node1;
}


NODE* Get_P() {
    NODE* node = 0;

    if(s[p] == '(') {
        p++;
        node = Get_E();
        p++;
        return node;
    } else if (s[p] > 'A' && s[p] < 'Z') {
        return Get_Id();
    } else {
        return Get_N();
    }
}

NODE* Get_Id() {
    NODE* node;

    if(s[p] > 'A' && s[p] < 'Z') {
        op_new(&node, VAR, 0);
        p++;
    }

    return node;
}