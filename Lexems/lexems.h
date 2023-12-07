#ifndef LEXEMS_H_INCLUDE
#define LEXEMS_H_INCLUDE
#include "../Difirinciator.h"
#include "../recursive_descent.h"

const int MAX_LEXEM_LEN = 255;

struct BUFFER {
    const char* string;
    int ptr = 0;
};

void print_lexems (NODE** lexem_arr);
NODE** lexem_analys(BUFFER* buffer);

#endif