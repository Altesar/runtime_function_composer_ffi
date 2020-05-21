#ifndef RUNTIME_FUNCTION_COMPOSER_RFC_STUB_H
#define RUNTIME_FUNCTION_COMPOSER_RFC_STUB_H

typedef int(*frc_invoker_t)(void*, void**, int, void*);
frc_invoker_t rfc_invoke;

typedef int(fib_test_t)(int);
fib_test_t* fib_test_ptr;

void rfc_init();
void rfc_teardown();

#endif //RUNTIME_FUNCTION_COMPOSER_RFC_STUB_H
