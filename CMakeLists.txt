cmake_minimum_required(VERSION 3.0)

project(runtime_function_composer LANGUAGES C)

set(CMAKE_BUILD_TYPE Debug)
set (-DCMAKE_BUILD_TYPE=debug64)

add_executable(runtime_function_composer
        main.c
        rfc/rfc.c rfc/rfc.h rfc/fragment.c rfc/fragment.h rfc/fsio.c rfc/fsio.h rfc/template_parser.c rfc/template_parser.h rfc/fragment_registry.h performance_test/rfc_fibonacci.c performance_test/timing.c performance_test/rfc_fibonacci.h timing.h/performance_eval.h performance_test/timing.h performance_test/rfc_mujs_fibonacci.c performance_test/rfc_mujs_fibonacci.h performance_test/rfc_stub.h performance_test/rfc_stub.c)

target_link_libraries(runtime_function_composer mujs m)