#include <stdlib.h>

#include "rfc_stub.h"
#include "../rfc/fragment.h"
#include "../rfc/fsio.h"

void rfc_init()
{
    rfc_fragment_t* prologue = rfc_fsread_frag("../fragments/prologue.frag");
    rfc_fragment_t* arg_resolver = rfc_fsread_frag("../fragments/fib_arg_resolver.frag");
    rfc_fragment_t* epilogue = rfc_fsread_frag("../fragments/epilogue.frag");

    rfc_wrapper_template_t* test_template = malloc(sizeof(rfc_wrapper_template_t));
    test_template->wrapper_fragments = malloc(3 * sizeof(rfc_fragment_t));
    test_template->wrapper_fragments[0] = prologue;
    test_template->wrapper_fragments[1] = arg_resolver;
    test_template->wrapper_fragments[2] = epilogue;
    test_template->wrapper_frag_count = 3;
    test_template->wrapper_arg_count = 2;

    void *wrapper_entry = NULL;
    int wrapper_size = 0;
    rfc_composer_amd64(test_template, &wrapper_entry, &wrapper_size);

    rfc_invoke = wrapper_entry;

    free(prologue);
    free(arg_resolver);
    free(epilogue);
}

void rfc_teardown()
{
    free(rfc_invoke);
}