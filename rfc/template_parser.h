#ifndef RUNTIME_FUNCTION_COMPOSER_TEMPLATE_PARSER_H
#define RUNTIME_FUNCTION_COMPOSER_TEMPLATE_PARSER_H

#include "fragment.h"
/**
 * @param template null - terminated string
 * @return
 */
rfc_wrapper_template_t* rfc_wrapper_template_new(char* template);

rfc_fragment_t* rfc_fragment_resolve(rfc_fragment_type_t);

#endif //RUNTIME_FUNCTION_COMPOSER_TEMPLATE_PARSER_H
