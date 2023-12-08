#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Lexems/lexems.h"
#include "Difirinciator.h"
#include "Dump_difirinciator.h"

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

    int number = 0;

    lexem_arr = lexem_analys(&buffer, &number);

    //printf("%p\n", lexem_arr);

    print_lexems(lexem_arr, number);

    LEXEM_ARR arr = {};
    arr.lexem_arr = lexem_arr;
    arr.ptr = 0;

    node = Get_G(&arr);

    printf("%p\n", node);

    int counter = 0;

    make_png_dump("src_tree.dot", node, &counter);

    free(lexem_arr);

    free_tree(node);
}