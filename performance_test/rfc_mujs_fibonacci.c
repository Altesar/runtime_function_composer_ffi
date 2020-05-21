#include <stdlib.h>
#include <stdio.h>
#include <mujs.h>
#include <time.h>

#include "rfc_mujs_fibonacci.h"
#include "rfc_stub.h"
#include "timing.h"

js_State* mujs_state;

void rfc_mujs_invoker(js_State* state);
int rfc_mujs_fib_test(int n);
void js_print_str(js_State* state);

void js_print_str(js_State* state)
{
    const char* str = js_tostring(state, 1);
    printf("%s", str);
    js_pushundefined(mujs_state);
}

void mujs_init()
{
    mujs_state = js_newstate(NULL, NULL, JS_STRICT);
    js_newcfunction(mujs_state, rfc_mujs_invoker, "rfc_invoke", 1);
    js_setglobal(mujs_state, "rfc_invoke");

    js_newcfunction(mujs_state, js_print_str, "print_str", 1);
    js_setglobal(mujs_state, "print_str");
}

void mujs_teardown()
{
    js_freestate(mujs_state);
}

int rfc_mujs_fib_test(int n)
{
    js_getglobal(mujs_state, "fibonacci_rfc");
    js_pushnull(mujs_state);
    js_pushnumber(mujs_state, n);

    js_pcall(mujs_state, 1);

    int result = js_tointeger(mujs_state, -1);

    js_pop(mujs_state, 1);

    return result;
}

int rfc_mujs_fib_norfc_test(int n)
{
    js_getglobal(mujs_state, "fibonacci_norfc");
    js_pushnull(mujs_state);
    js_pushnumber(mujs_state, n);

    js_pcall(mujs_state, 1);

    int result = js_tointeger(mujs_state, -1);

    js_pop(mujs_state, 1);

    return result;
}

void rfc_mujs_invoker(js_State* state)
{
    int result = 0;
    int argval = js_tointeger(state, 1);

    void** val_list = malloc(sizeof(void*));
    val_list[0] = &argval;

    rfc_invoke(&rfc_mujs_fib_test, val_list, 1, &result);

    js_pushnumber(mujs_state, result);
}

double fib_mujs_rfc_entry(int n)
{
    struct timespec time_start, time_end;

    int result = 0;
    int argval = 1;

    clock_gettime(CLOCK_REALTIME, &time_start);

    for(int i = 1; i < n; ++i, argval = i + 1)
    {
        rfc_mujs_fib_test(argval);
    }

    clock_gettime(CLOCK_REALTIME, &time_end);
    return get_runtime_ms(time_start, time_end);
}

double fib_mujs_norfc_entry(int n)
{
    struct timespec time_start, time_end;

    int result = 0;
    int argval = 1;

    clock_gettime(CLOCK_REALTIME, &time_start);

    for(int i = 1; i < n; ++i, argval = i + 1)
    {
        rfc_mujs_fib_norfc_test(argval);
    }

    clock_gettime(CLOCK_REALTIME, &time_end);
    return get_runtime_ms(time_start, time_end);
}

void rfc_mujs_run_tests(int* testing_set, int testing_set_size)
{
    mujs_init();

    js_dofile(mujs_state, "../performance_test/js_src/fibonacci.js");

    double run_time;

    printf("== MuJs FIBONACCI RFC ==\n");
    printf("Test,Length,Execution Time\n");
    for(int i = 0; i < testing_set_size; ++i)
    {
        run_time = fib_mujs_rfc_entry(testing_set[i]);
        printf("%d,%d,%f\n", i+1, testing_set[i], run_time);
    }

    printf("== MuJs FIBONACCI NoRFC ==\n");
    printf("Test,Length,Execution Time\n");
    for(int i = 0; i < testing_set_size; ++i)
    {
        run_time = fib_mujs_norfc_entry(testing_set[i]);
        printf("%d,%d,%f\n", i+1, testing_set[i], run_time);
    }

    printf("done\n");

    mujs_teardown();
}
