#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/mman.h>

#include <stdio.h>

#include "./fragment.h"

//rfc_entry_arg_list_t* rfc_entry_arg_list_new(int arg_count, ...)
//{
//    rfc_entry_arg_list_t* arg_list = malloc(sizeof(rfc_entry_arg_list_t));
//
//    arg_list->entry_arg_count = arg_count;
//    arg_list->entry_arg_list = malloc(arg_count * sizeof(void*));
//
//    va_list arg_ptr;
//    va_start(arg_ptr, arg_count);
//
//    for(int i = 0; i < arg_count; ++i)
//        arg_list->entry_arg_list[i] = va_arg(arg_ptr, void*);
//
//    va_end(arg_ptr);
//
//    return arg_list;
//}
//
//void rfc_entry_arg_list_delete(rfc_entry_arg_list_t* entry_arg_list)
//{
//    free(entry_arg_list->entry_arg_list);
//    free(entry_arg_list);
//}

//--------
//   ...
//--------

rfc_wrapper_t* rfc_wrapper_new(rfc_wrapper_template_t* template)
{
    //TODO: input sanitation
    rfc_wrapper_t* wrapper = malloc(sizeof(rfc_wrapper_t));

    int size = 0;
    rfc_wrapper_entry_t* entry = NULL;

    //TODO: error checking
    rfc_composer_amd64(template, &entry, &size);

    wrapper->wrapper_size = size;
    wrapper->wrapper_entry = entry;


    return wrapper;
}

//TODO: full-fledged executable composition pipeline
void rfc_composer_amd64(rfc_wrapper_template_t* template, void **entry, int* size)
{
    int size_temp = 0;
    void* entry_temp = NULL;

    for(int i = 0; i < template->wrapper_frag_count; size_temp += template->wrapper_fragments[i]->fragment_size, ++i);

    *size = size_temp;

    entry_temp = mmap(0, size_temp, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    if(entry_temp == NULL)
    {
        printf("[rfc_composer_amd64] could not map memory");
        exit(EXIT_FAILURE);
    }

    int offset = 0;
    rfc_fragment_t* fragment;
    for(int i = 0; i < template->wrapper_frag_count; ++i)
    {
        printf("fragment size %d\n", template->wrapper_fragments[i]->fragment_size);
        fragment = template->wrapper_fragments[i];
        memcpy((char*)entry_temp + offset, (char*)fragment->fragment_code, fragment->fragment_size);
        offset += fragment->fragment_size;
    }

    *entry = entry_temp;
}