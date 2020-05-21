#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "performance_test/rfc_stub.h"
#include "performance_test/rfc_fibonacci.h"
#include "performance_test/rfc_mujs_fibonacci.h"

#define C_TESTING_SET { 5, 10, 15, 20, 25, 30, 35, 40 }
#define MUJS_TESTING_SET { 5, 10, 15, 20, 25, 30, 35 }

typedef int(fib_test_t)(int);
fib_test_t* fib_test_ptr;

int main(int argc, char *argv[])
{
    int c_testing_set[] = C_TESTING_SET;
    int c_testing_set_size = sizeof(c_testing_set) / sizeof(int);

    int mujs_testing_set[] = MUJS_TESTING_SET;
    int mujs_testing_set_size = sizeof(mujs_testing_set_size / sizeof(int));

    rfc_init();

    rfc_run_tests(c_testing_set, c_testing_set_size);
    rfc_mujs_run_tests(mujs_testing_set, mujs_testing_set_size);

    rfc_teardown();

    return 0;
}
