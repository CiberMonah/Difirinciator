#ifndef RECURSIVE_DESCENT_H_INCLUDED
#define RECURSIVE_DESCENT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "Difirinciator.h"

#define err {                               \
    printf("Syn error %d\n", __LINE__);     \
}

NODE* Get_G(const char* str);
NODE* Get_N();
NODE* Get_E();
NODE* Get_T();
NODE* Get_P();

#endif