#include <stdio.h>
#include <time.h>

double get_runtime_ms(struct timespec time_start, struct timespec time_end)
{
    double start_ms = time_start.tv_sec * 1e3 + (double)time_start.tv_nsec / (double)1e6;
    double end_ms = time_end.tv_sec * 1e3 + (double)time_end.tv_nsec / (double)1e6;
    return end_ms - start_ms;
}

