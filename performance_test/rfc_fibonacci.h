#ifndef RUNTIME_FUNCTION_COMPOSER_RFC_FIBONACCI_H
#define RUNTIME_FUNCTION_COMPOSER_RFC_FIBONACCI_H

int rfc_fib_test_ramoptimized(int n);
int rfc_fib_test_noramopts(int n);

void rfc_run_tests(int* testing_set, int testing_set_size);
double fib_rfc_test_entry(int n);
double fib_norfc_test_entry(int n);
int fib_norfc_test(int n);

#endif //RUNTIME_FUNCTION_COMPOSER_RFC_FIBONACCI_H
