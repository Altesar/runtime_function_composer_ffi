#ifndef RUNTIME_FUNCTION_COMPOSER_RFC_H
#define RUNTIME_FUNCTION_COMPOSER_RFC_H

#include "fragment.h"

// To make sure all arguments will be passed in registers (on amd64 and arm linux)
typedef void(*rfc_invoker_t)(rfc_wrapper_t* wrapper, int arg_list_size, void** arg_list, void* ret_val);

typedef struct rfc_registry
{
    int wrapper_list_size;
    rfc_wrapper_t* wrapper_list;
    rfc_invoker_t  invoker;
} rfc_registry_t;

#endif //RUNTIME_FUNCTION_COMPOSER_RFC_H
