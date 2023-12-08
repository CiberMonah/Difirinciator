#include "../Difirinciator.h"
#include "lexems.h"

const int MAX_LEXEM_NUMBER = 255;

void print_lexems (NODE** lexem_arr, int counter) {
    op_new(&lexem_arr[counter + 1], OPERATION, END_COMAND);
    
    for(int i = 0; i < counter + 1; i++) {
        //printf("\ndata - %d\n", lexem_arr[i]->data);
        
        if((lexem_arr[i])->arg_type == NUMBER) {
            printf("%d", lexem_arr[i]->data);
        } else if((lexem_arr[i])->arg_type == OPERATION) {
            switch (lexem_arr[i]->data)
            {
            case ADD_COMAND:
                printf(" + ");
                break;
            case SUP_COMAND:
                printf(" - ");
                break;
            case DIV_COMAND:
                printf(" / ");
                break;
            case MUL_COMAND:
                printf(" * ");
                break;
            case OBR_COMAND:
                printf(" ( ");
                break;
            case CBR_COMAND:
                printf(" ) ");
                break;
            case END_COMAND:
                printf("END - \\0");
                return;
                break;
            default:
                printf("Syntax error - %d\n", lexem_arr[i]->data);
                break;
            }
        } else if((lexem_arr[i])->arg_type == VAR) {
            printf(" X ");
        }
    }
    printf("\n");
}

static void skip_spaces(BUFFER* buffer) {
    while(buffer->string[buffer->ptr] == ' ') {
        buffer->ptr++;
    }
}

static NODE* get_number(BUFFER* buffer) {
    int old_ptr = buffer->ptr;
    Elem_t number = 0;
    NODE* ret_node = nullptr;

    while(buffer->string[buffer->ptr] >= '0' && buffer->string[buffer->ptr] <= '9') {
        number = number * 10 + (buffer->string[buffer->ptr] - '0');
        buffer->ptr++;
    }

    if(old_ptr == buffer->ptr) {
        return nullptr;
    } else {
        op_new(&ret_node, NUMBER, number);
        return ret_node;
    }
}

static NODE* get_op(BUFFER* buffer) {
    NODE* ret_node = nullptr;

    switch(buffer->string[buffer->ptr]) {
        case '+':
            op_new(&ret_node, OPERATION, ADD_COMAND);
            buffer->ptr++;
            break;
        case '-':
            op_new(&ret_node, OPERATION, SUP_COMAND);
            buffer->ptr++;
            break;
        case '*':
            op_new(&ret_node, OPERATION, MUL_COMAND);
            buffer->ptr++;
            break;
        case '/':
            op_new(&ret_node, OPERATION, DIV_COMAND);
            buffer->ptr++;
            break;
        case '(':
            op_new(&ret_node, OPERATION, OBR_COMAND);
            buffer->ptr++;
            break;
        case ')':
            op_new(&ret_node, OPERATION, CBR_COMAND);
            buffer->ptr++;
            break;
        default:
            return nullptr;
    }

    return ret_node;
}

static NODE* get_var(BUFFER* buffer) {
    NODE* ret_node = nullptr;

    if(buffer->string[buffer->ptr] >= 'A' && buffer->string[buffer->ptr] <= 'Z') {
        op_new(&ret_node, VAR, 1);
        buffer->ptr++;
    }

    return ret_node;
}

static NODE* get_end(BUFFER* buffer) {
    NODE* ret_node = nullptr;

    if(buffer->string[buffer->ptr] == '\0') {
        op_new(&ret_node, OPERATION, END_COMAND);
        buffer->ptr++;
    }

    return ret_node;
}



NODE** lexem_analys(BUFFER* buffer, int* counter) {
    NODE** LEXEM_ARR = (NODE**)calloc(MAX_LEXEM_NUMBER, sizeof(NODE*));

    if(!buffer->string) {
        printf("Nullptr string passed\n");
        return nullptr;
    }

    int i = 0;

    while(buffer->string[buffer->ptr] != '\0') {
        skip_spaces(buffer);

        if((LEXEM_ARR[i] = get_number(buffer)) != nullptr)
            i++;
        else if((LEXEM_ARR[i] = get_op(buffer)) != nullptr)
            i++;
        else if((LEXEM_ARR[i] = get_var(buffer)) != nullptr)
            i++;
        else if((LEXEM_ARR[i] = get_end(buffer)) != nullptr)
            i++;
        else {
            printf("Syntaxis error\n");
            break;
        }
    }

    NODE* end_node = nullptr;
    op_new(&end_node, OPERATION, END_COMAND);

    LEXEM_ARR[i] = end_node;

    *counter = i;

    return LEXEM_ARR;
}


NODE* Get_N(LEXEM_ARR* arr) {
    if(arr->lexem_arr[arr->ptr]->arg_type == NUMBER) {
        printf("Number - %d\n", arr->lexem_arr[arr->ptr]->data);
        arr->ptr++;
        return arr->lexem_arr[arr->ptr - 1];
    } else 
        return nullptr;
    
}

NODE* Get_E(LEXEM_ARR* arr) {
    NODE* node1 = Get_T(arr);
    printf("NODE1 data - %d\n", node1->data);

    while(arr->lexem_arr[arr->ptr]->arg_type == OPERATION && (arr->lexem_arr[arr->ptr]->data == ADD_COMAND || arr->lexem_arr[arr->ptr]->data == SUP_COMAND)) {
        arr->ptr++;

        printf("%d\n", arr->lexem_arr[arr->ptr - 1]->data);

        NODE* node2 = Get_T(arr);

        printf("NODE2 data - %d\n", node2->data);

        switch (arr->lexem_arr[arr->ptr - 2]->data)
        {
        case ADD_COMAND:
            printf("+\n");
            arr->lexem_arr[arr->ptr - 2]->left = node1;
            arr->lexem_arr[arr->ptr - 2]->right = node2;
            node1 = arr->lexem_arr[arr->ptr - 2];
            break;
        case SUP_COMAND:
            printf("-\n");
            arr->lexem_arr[arr->ptr - 2]->left = node1;
            arr->lexem_arr[arr->ptr - 2]->right = node2;
            node1 = arr->lexem_arr[arr->ptr - 2];
            break;
        default:
            break;
        }
    }
    return node1;
}

NODE* Get_Id(LEXEM_ARR* arr) {
    NODE* node = nullptr;

    if(arr->lexem_arr[arr->ptr]->arg_type == VAR) {
        node = arr->lexem_arr[arr->ptr];
        arr->ptr++;
    }

    return node;
}

NODE* Get_P(LEXEM_ARR* arr) {
    NODE* node = 0;

    if(arr->lexem_arr[arr->ptr]->arg_type == OPERATION && arr->lexem_arr[arr->ptr]->data == OBR_COMAND) {
        arr->ptr++;
        node = Get_E(arr);
        arr->ptr++;
        return node;
    } else if (arr->lexem_arr[arr->ptr]->arg_type == VAR) {
        return Get_Id(arr);
    } else {
        return Get_N(arr);
    }
}


NODE* Get_T(LEXEM_ARR* arr) {
    NODE* node1 = Get_P(arr);

    while(arr->lexem_arr[arr->ptr]->arg_type == OPERATION && (arr->lexem_arr[arr->ptr]->data == MUL_COMAND || arr->lexem_arr[arr->ptr]->data == DIV_COMAND)) {
        arr->ptr++;

        NODE* node2 = Get_P(arr);

        switch (arr->lexem_arr[arr->ptr - 2]->data)
        {
        case ADD_COMAND:
            arr->lexem_arr[arr->ptr - 2]->left = node1;
            arr->lexem_arr[arr->ptr - 2]->right = node2;
            node1 = arr->lexem_arr[arr->ptr - 2];
            break;
        case SUP_COMAND:
            arr->lexem_arr[arr->ptr - 2]->left = node1;
            arr->lexem_arr[arr->ptr - 2]->right = node2;
            node1 = arr->lexem_arr[arr->ptr - 2];
            break;
        default:
            printf("Syntax err - %d\n", arr->lexem_arr[arr->ptr]->data);
            break;
        }
    }
    return node1;
}

NODE* Get_G(LEXEM_ARR* arr) {
    return Get_E(arr);
}


