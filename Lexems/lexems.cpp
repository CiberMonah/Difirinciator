#include "../Difirinciator.h"
#include "../recursive_descent.h"
#include "lexems.h"

const int MAX_NUMBER_OF_LEXEM = 255;

void print_lexems (NODE** lexem_arr) {
    for(int i = 0; i < MAX_LEXEM_LEN; i++) {
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
            default:
                break;
            }
        }
    }
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



NODE** lexem_analys(BUFFER* buffer) {
    NODE** LEXEM_ARR = (NODE**)calloc(MAX_NUMBER_OF_LEXEM, sizeof(NODE*));

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
        else {
            printf("Syntaxis error\n");
            break;
        }
    }

    return LEXEM_ARR;
}
