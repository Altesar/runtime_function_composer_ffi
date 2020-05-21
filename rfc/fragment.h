#ifndef RUNTIME_FUNCTION_COMPOSER_FRAGMENT_H
#define RUNTIME_FUNCTION_COMPOSER_FRAGMENT_H

#ifndef RFC_ARG_MEDIUM_ENUM
    #define RFC_ARG_MEDIUM_ENUM rfc_argument_medium_x86_t
#endif // RFC_ARG_MEDIUM_ENUM

/*
 * Defines fragment type, used by composer function
 */
typedef enum rfc_fragment_type {
    RFC_FRAG_PROLOGUE,
    RFC_FRAG_ARG_RESOLVER,
    RFC_FRAG_INVOKER,
    RFC_FRAG_RETVAL_RESOLVER,
    RFC_FRAG_EPILOGUE
} rfc_fragment_type_t;

typedef enum rfc_resolver_target_amd64_arg {
    RFC_ARG_AMD64_0,
    RFC_ARG_AMD64_1,
    RFC_ARG_AMD64_2,
    RFC_ARG_AMD64_3,
    RFC_ARG_AMD64_4,
    RFC_ARG_AMD64_5,
    RFC_ARG_AMD64_6 //TODO: more arguments
} rfc_resolver_target_amd64_arg;

typedef enum rfc_resolver_target_amd64_medium {
    RFC_ARG_AMD64_REG,
    RFC_ARG_AMD64_MMC,
    RFC_ARG_AMD64_STACK //just in case
} rfc_resolver_target_amd64_medium_t;

#ifndef RFC_ARG_TARGET_ENUM_T
    #define RFC_ARG_TARGET_ENUM_T rfc_resolver_target_amd64_arg
#endif

#ifndef RFC_ARG_MEDIUM_ENUM_T
    #define RFC_ARG_MEDIUM_ENUM_T rfc_resolver_target_amd64_medium_t
#endif

typedef struct rfc_arg_resolver_data {
    RFC_ARG_MEDIUM_ENUM_T resolver_arg_medium;   // Defines how argument should be passed to target function
    RFC_ARG_TARGET_ENUM_T resolver_arg_target;  // Defines argument target (corresponding register in case if AMD64)
} rfc_arg_resolver_data_t;

typedef struct rfc_retval_resolver_data {
    RFC_ARG_MEDIUM_ENUM_T resolver_arg_medium;
} rfc_retval_resolver_data_t;

typedef union rfc_fragment_metadata {
    rfc_arg_resolver_data_t* arg_resolver_data;
    rfc_retval_resolver_data_t* retval_resolver_data;
} rfc_fragment_metadata_t;

// TODO: generate fragments and corresponding descriptors based on template
typedef struct rfc_fragment {
    char* fragment_label; // Exported asm label name, matching /^RFCFRAG__[a-zA-Z0-9]$/ pattern [subjected to change]
    void* fragment_code;
    int fragment_size;
    rfc_fragment_type_t fragment_type;
    int fragment_arg_count;

    rfc_fragment_metadata_t fragment_metadata;

    //TODO: fragment_args_resolver
    //TODO: fragment_factory
} rfc_fragment_t;

typedef struct rfc_wrapper_template {
    int wrapper_arg_count;
    int wrapper_frag_count;
    char* template_target_id;
    void* template_target_ptr;
    rfc_fragment_t** wrapper_fragments; // Array of fragments in order of appearance
    // TODO: wrapper_compose_exception_callback
} rfc_wrapper_template_t;

// Wrapper function pointer type
typedef void (rfc_wrapper_entry_t)(int arg_list_size, void** arg_list, void* ret_val);

//TODO: Template-specific composer
typedef void (rfc_function_composer)(rfc_wrapper_template_t* wrapper_template, rfc_wrapper_entry_t* entry, int* size);

typedef struct rfc_wrapper {
    int wrapper_size;
    rfc_wrapper_entry_t* wrapper_entry;
    //TODO: exception severity evaluation
    //TODO: Panic and recovery methods
} rfc_wrapper_t;

rfc_wrapper_t* rfc_wrapper_new(rfc_wrapper_template_t* wrapper_template);

void rfc_composer_amd64(rfc_wrapper_template_t* wrapper_template, void **entry, int* size);

#endif //RUNTIME_FUNCTION_COMPOSER_FRAGMENT_H
