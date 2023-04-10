#pragma once

#include <stdlib.h>

typedef struct AST_STRUCT {
    enum {
        AST_FUNCTION_CALL,
        AST_VARIABLE_DEFINITION,
        AST_VARIABLE,
        AST_STRING,
        AST_COMPOUND,
        AST_NOOP
    } type;

    // AST_VARIABLE_DEFINITION
    char* variable_def_name;
    struct AST_STRUCT* variable_def_value;

    // AST_VARIABLE
    char* variable_name;

    // AST_FUNCTION_CALL
    char* function_call_name;
    struct AST_STRUCT** function_call_args;
    size_t function_call_args_num;

    // AST_STRING
    char* string_value;

    // AST_COMPOUND
    struct AST_STRUCT** compound_value;
    size_t compound_size;
} AST_T;

AST_T* init_ast(int type);
