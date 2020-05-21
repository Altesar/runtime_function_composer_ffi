#include <stdlib.h>
#include <stdio.h>

#include "fsio.h"

int get_file_size(FILE*);

rfc_fragment_t* rfc_fsread_frag(char* path)
{
    FILE* file = fopen(path, "r");

    if(file == NULL) {
        printf("Could not open file %s", path);
        exit(EXIT_FAILURE);
    }

    rfc_fragment_t* fragment = malloc(sizeof(rfc_fragment_t));
    char* code = NULL;

    int size = get_file_size(file);
    code = malloc(size);

    fread(code, size, sizeof(char), file);

    //TODO: populate other fields
    fragment->fragment_size = size;
    fragment->fragment_code = code;

    fclose(file);

    return fragment;
}

int get_file_size(FILE* file)
{
    int size = 0;
    int offset = ftell(file);
    rewind(file);
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, offset, SEEK_SET);
    return size;
}
