#ifndef RUNTIME_FUNCTION_COMPOSER_FSIO_H
#define RUNTIME_FUNCTION_COMPOSER_FSIO_H

#include "fragment.h"

rfc_fragment_t* rfc_fsread_frag(char* path);

//TODO: implement
void rfc_fswrite_wrapper(rfc_wrapper_t* wrapper);

#endif //RUNTIME_FUNCTION_COMPOSER_FSIO_H
