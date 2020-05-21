#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "rfc_stub.h"
#include "rfc_fibonacci.h"
#include "../rfc/fragment.h"
#include "../rfc/fsio.h"
#include "timing.h"

double fib_rfc_test_entry_1(int n);

int fibo_calls = 0;

void rfc_run_tests(int* testing_set, int testing_set_size)
{
    double run_time = 0;

    fib_test_ptr = &fib_norfc_test;

    printf("== FIBONACCI RFC ==\n");
    printf("Test,Length,Execution Time\n");
    for(int i = 0; i < testing_set_size; ++i) {
        fibo_calls = 0;
        run_time = fib_rfc_test_entry(testing_set[i]);
        printf("%d,%d,%f ms\n", i+1, testing_set[i], run_time);
    }

    printf("== FIBONACCI NoRFC ==\n");
    printf("Test,Length,Execution Time\n");
    for(int i = 0; i < testing_set_size; ++i)
    {
        fibo_calls = 0;
        run_time = fib_norfc_test_entry(testing_set[i]);
        printf("%d,%d,%f ms in %d\n", i+1, testing_set[i], run_time, fibo_calls);
    }
}

int rfc_fib_test_ramoptimized(int n)
{
    if (n <= 1) {
        return n;
    }

    void* val_list[1];

    int fib_1 = 0, fib_2 = 0;
    int n_1 = n - 1;
    int n_2 = n - 2;

    val_list[0] = &n_1;
    rfc_invoke(&rfc_fib_test_ramoptimized, val_list, 1, &fib_1);

    val_list[0] = &n_2;
    rfc_invoke(&rfc_fib_test_ramoptimized, val_list, 1, &fib_2);

    int fib = fib_1 + fib_2;

    return fib;
}

int rfc_fib_test_noramopts(int n)
{
    fibo_calls++;
    if (n <= 1) {
        return n;
    }

    void** val_list = malloc(sizeof(void*));

    int fib_1 = 0, fib_2 = 0;
    int n_1 = n - 1;
    int n_2 = n - 2;

    val_list[0] = &n_1;
    rfc_invoke(&rfc_fib_test_noramopts, val_list, 1, &fib_1);

    val_list[0] = &n_2;
    rfc_invoke(&rfc_fib_test_noramopts, val_list, 1, &fib_2);

    int fib = fib_1 + fib_2;

    free(val_list);

    return fib;
}

double fib_rfc_test_entry(int n)
{
    struct timespec time_start, time_end;

    void* val_list[1];
    int64_t result = 0;
    int64_t argval = 1;

    val_list[0] = &argval;

    clock_gettime(CLOCK_REALTIME, &time_start);

    for(int i = 1; i < n; ++i, argval = i + 1)
    {
        rfc_invoke(&rfc_fib_test_noramopts, val_list, 1, &result);
    }

    clock_gettime(CLOCK_REALTIME, &time_end);
    return get_runtime_ms(time_start, time_end);
}

double fib_norfc_test_entry(int n)
{
    struct timespec time_start, time_end;

    int result = 0;
    int argval = 1;

    clock_gettime(CLOCK_REALTIME, &time_start);

    for(int i = 1; i < n; ++i, argval = i + 1)
    {
        fib_test_ptr(argval);
    }

    clock_gettime(CLOCK_REALTIME, &time_end);
    return get_runtime_ms(time_start, time_end);
}

int fib_norfc_test(int n)
{
    fibo_calls++;

    if (n <= 1) {
        return n;
    }

    return fib_test_ptr(n-1) + fib_test_ptr(n-2);
}
