#ifndef LEXEMS_H_INCLUDE
#define LEXEMS_H_INCLUDE
#include "../Difirinciator.h"

const int MAX_LEXEM_LEN = 255;
const int MAX_LEN_OF_EXPRESSION = 255;

struct BUFFER {
    const char* string;
    int ptr = 0;
};


struct LEXEM_ARR {
    NODE** lexem_arr;
    int ptr = 0;
};

void print_lexems (NODE** lexem_arr, int counter);
NODE** lexem_analys(BUFFER* buffer, int* counter);
NODE* Get_G(LEXEM_ARR* arr);
NODE* Get_E(LEXEM_ARR* arr);
NODE* Get_T(LEXEM_ARR* arr);
NODE* Get_P(LEXEM_ARR* arr);
NODE* Get_N(LEXEM_ARR* arr);
NODE* Get_Id(LEXEM_ARR* arr);

#endif