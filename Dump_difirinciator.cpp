#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Difirinciator.h"
#include "Dump_difirinciator.h"

static char* str_insert(char* dst, const char* src, size_t dstSize, size_t pos) {
    char* tmp;
	tmp = (char*)calloc(dstSize, sizeof(char));

    size_t i, j, dstLen, srcLen;
 
    for ( dstLen = 0; dst[dstLen]; ++dstLen )
        ;
    for ( srcLen = 0; src[srcLen]; ++srcLen )
        ;
    
    if ( pos > dstLen )
        pos = dstLen;
    
	//Check if we are in range
    for ( i = 0; i < pos && i < dstSize - 1; ++i )
        tmp[i] = dst[i];
    for ( j = 0; src[j] && i < dstSize - 1; ++j, ++i )
        tmp[i] = src[j];
    for ( j = pos; dst[j] && i < dstSize - 1; ++j, ++i )
        tmp[i] = dst[j];
    tmp[i] = '\0';
 
    //copy temp str to dst
    for ( i = 0; ( dst[i] = tmp[i] ) != '\0'; ++i );

    free(tmp);
    return dst;
}


static void dot_dump(FILE* file, NODE* node, int* counter) {
	setvbuf(file, NULL, _IONBF, 0);

	int counter_now = *counter;

	if (node != 0) {
		if(node->arg_type == OPERATION) {
			switch(node->data) {
				case ADD_COMAND:
					fprintf(file, "\tNode_%d [label = \"+\", shape = \"ellipse\", style = \"filled\", fillcolor = \"#1f77b4\"]\n", (*counter));
					break;
				case SUP_COMAND:
					fprintf(file, "\tNode_%d [label = \"-\", shape = \"ellipse\", style = \"filled\", fillcolor = \"#1f77b4\"]\n", (*counter));
					break;
				case MUL_COMAND:
					fprintf(file, "\tNode_%d [label = \"*\", shape = \"ellipse\", style = \"filled\", fillcolor = \"#1f77b4\"]\n", (*counter));
					break;
				case DIV_COMAND:
					fprintf(file, "\tNode_%d [label = \"/\", shape = \"ellipse\", style = \"filled\", fillcolor = \"#1f77b4\"]\n", (*counter));
					break;
				default:
					break;
			}
		} else if (node->arg_type == VAR) {
			fprintf(file, "\tNode_%d [label = \"X\", shape = \"ellipse\", style = \"filled\", fillcolor = \"#1f77b4\"]\n", (*counter));
		} else { 
			fprintf(file, "\tNode_%d [label = \"%d\", shape = \"ellipse\", style = \"filled\", fillcolor = \"#1f77b4\"]\n", (*counter), node->data);
		}

		if (node->left != 0) {
			fprintf(file, "\tNode_%d -> Node_%d\n", counter_now, (*counter) + 1);
			(*counter)++;
			dot_dump(file, node->left, counter);
		}
		if (node->right != 0) {
			fprintf(file, "\tNode_%d -> Node_%d\n", counter_now, (*counter) + 1);
			(*counter)++;
			dot_dump(file, node->right, counter);
		}
	}
}

char NUMBER_OF_DUMP_PNG = 'A';

void make_png_dump(const char* file_name , NODE* node, int* counter) {
	FILE* dot_file = nullptr;
	const int MAX_FILE_NAME = 255;

	if(!(dot_file = fopen(file_name, "w")))
		return;

    fprintf(dot_file, "digraph G{\n");

    dot_dump(dot_file, node, counter);

    fprintf(dot_file, "}");

	fclose(dot_file);

	char comand[MAX_FILE_NAME] = "dot  -T png -o  .png";

	str_insert(comand, file_name, MAX_FILE_NAME, 4);			//4 is position to insert file_name in comand
	int i = 0;

	while(comand[i] != '\0')i++;

	comand[i-5] = NUMBER_OF_DUMP_PNG;
	NUMBER_OF_DUMP_PNG++;

	printf("%s\n", comand);

	system(comand);
}