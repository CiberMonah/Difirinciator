#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Difirinciator.h"
#include "Lexems/lexems.h"
#include "Dump_difirinciator.h"
#include "recursive_descent.h"

int main() {
    NODE* node;
    tree_init(&node);

    BUFFER buffer = {};
    FILE* expression = nullptr;

    if(!(expression = fopen("expression.txt", "r")))
        return -1;


    char str[MAX_LEN_OF_EXPRESSION] = {};

    fgets(str, MAX_LEN_OF_EXPRESSION, expression);

    buffer.string = str;
    buffer.ptr = 0;

    NODE** lexem_arr = nullptr;

    lexem_arr = lexem_analys(&buffer);

    //printf("%p\n", lexem_arr);

    print_lexems(lexem_arr);

    free(lexem_arr);

    free_tree(node);
}