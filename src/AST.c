#include "include/AST.h"

AST_T* init_ast(int type) {
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));

    ast->type = type;

    // AST_VARIABLE_DEFINITION
    ast->variable_def_name = NULL;
    ast->variable_def_value = NULL;

    // AST_VARIABLE
    ast->variable_name = NULL;

    // AST_FUNCTION_CALL
    ast->function_call_name = NULL;
    ast->function_call_args = NULL;
    ast->function_call_args_num = 0;

    // AST_STRING
    ast->string_value = NULL;

    // AST_COMPOUND
    ast->compound_value = NULL;
    ast->compound_size = 0;

    return ast;
}