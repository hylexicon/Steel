#include "include/parser.h"

#include <stdio.h>
#include <string.h>

parser_T* init_parser(lexer_T* lexer) {
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));

    parser->lexer = lexer;
    parser->currentToken = lexer_get_next_token(lexer);
    parser->prevToken = parser->currentToken;

    return parser;
}

void parser_eat(parser_T* parser, int token_type) {
    if (parser->currentToken->type == token_type) {
        parser->prevToken = parser->currentToken;
        parser->currentToken = lexer_get_next_token(parser->lexer);
    } else {
        printf(
            "Unexpected token '%s' with type %d\n", 
            parser->currentToken->value, 
            parser->currentToken->type
        );

        exit(1);
    } 
}

AST_T* parser_parse(parser_T* parser) {
    return parser_parse_statements(parser);
}

AST_T* parser_parse_statement(parser_T* parser) {
    switch (parser->currentToken->type) {
        case TOKEN_ID:
            return parser_parse_id(parser);
    }

    return init_ast(AST_NOOP);
}

AST_T* parser_parse_statements(parser_T* parser) {
    AST_T* compound = init_ast(AST_COMPOUND);
    AST_T* base_statement = parser_parse_statement(parser);

    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));
    compound->compound_value[0] = base_statement;
    compound->compound_size += 1;

    while (parser->currentToken->type == TOKEN_SEMI || parser->currentToken->type == TOKEN_NEWLINE) {
        if (parser->currentToken->type == TOKEN_SEMI)
            parser_eat(parser, TOKEN_SEMI);

        if (parser->currentToken->type == TOKEN_NEWLINE)
            parser_eat(parser, TOKEN_NEWLINE);

        AST_T* ast_statement = parser_parse_statement(parser);

        if (ast_statement) {
            compound->compound_size += 1;
            compound->compound_value = realloc(
                compound->compound_value,
                compound->compound_size * sizeof(struct AST_STRUCT*)
            );
            compound->compound_value[compound->compound_size - 1] = ast_statement;
        }
    }

    return compound;
}

AST_T* parser_parse_expression(parser_T* parser) {
    switch (parser->currentToken->type) {
        case TOKEN_STRING:
            return parser_parse_string(parser);

        case TOKEN_ID:
            return parser_parse_id(parser);
    }
}

AST_T* parser_parse_factor(parser_T* parser) {

}

AST_T* parser_parse_term(parser_T* parser) {

}

AST_T* parser_parse_function_call(parser_T* parser) {
    AST_T* function_call = init_ast(AST_FUNCTION_CALL);

    parser_eat(parser, TOKEN_LPAREN);

    function_call->function_call_name = parser->prevToken->value;
    function_call->function_call_args = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* base_expression = parser_parse_expression(parser);

    function_call->function_call_args[0] = base_expression;
    function_call->function_call_args_num += 1;

    while (parser->currentToken->type == TOKEN_COMMA) {
        parser_eat(parser, TOKEN_COMMA);

        AST_T* ast_expression = parser_parse_statement(parser);

        function_call->function_call_args_num += 1;
        function_call->function_call_args = realloc(
            function_call->function_call_args,
            function_call->function_call_args_num * sizeof(struct AST_STRUCT*)
        );
        function_call->function_call_args[function_call->function_call_args_num - 1] = ast_expression;
    }

    parser_eat(parser, TOKEN_RPAREN);

    return function_call;
}

AST_T* parser_parse_variable_definition(parser_T* parser) {
    parser_eat(parser, TOKEN_ID);

    parser_eat(parser, TOKEN_ID);
    char* var_name = parser->currentToken->value;

    parser_eat(parser, TOKEN_EQUALS);

    AST_T* var_value = parser_parse_expression(parser);
    AST_T* var_def = init_ast(AST_VARIABLE_DEFINITION);

    var_def->variable_def_name = var_name;
    var_def->variable_def_value = var_value;

    return var_def;
}

AST_T* parser_parse_variable(parser_T* parser) {
    char* tokenValue = parser->currentToken->value;

    parser_eat(parser, TOKEN_ID);

    if (parser->currentToken->type == TOKEN_LPAREN)
        return parser_parse_function_call(parser);

    AST_T* ast_variable = init_ast(AST_VARIABLE);
    
    ast_variable->variable_name = tokenValue;

    return ast_variable;
}

AST_T* parser_parse_string(parser_T* parser) {
    AST_T* ast_string = init_ast(AST_STRING);

    ast_string->string_value = parser->currentToken->value;

    parser_eat(parser, TOKEN_STRING);

    return ast_string;
}

AST_T* parser_parse_id(parser_T* parser) {
    if (!strcmp(parser->currentToken->value, "var"))
        return parser_parse_variable_definition(parser);
    
    else
        return parser_parse_variable(parser);
}