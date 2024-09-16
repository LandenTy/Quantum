#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

// List of C++ keywords
const char* cpp_keywords[] = {
    // List of C++ keywords...
};

// Number of C++ keywords
const int num_cpp_keywords = sizeof(cpp_keywords) / sizeof(cpp_keywords[0]);

int is_cpp_keyword(const char* str) {
    for (int i = 0; i < num_cpp_keywords; i++) {
        if (strcmp(str, cpp_keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void print_token(Token token) {
    switch (token.type) {
        case TOKEN_IDENTIFIER:
            printf("IDENTIFIER: %s\n", token.value);
            break;
        case TOKEN_KEYWORD:
            printf("KEYWORD: %s\n", token.value);
            break;
        case TOKEN_INTEGER:
            printf("INTEGER: %s\n", token.value);
            break;
        case TOKEN_OPERATOR:
            printf("OPERATOR: %s\n", token.value);
            break;
        case TOKEN_DELIMITER:
            printf("DELIMITER: %s\n", token.value);
            break;
        case TOKEN_UNKNOWN:
            printf("UNKNOWN: %s\n", token.value);
            break;
        case TOKEN_EOF:
            printf("EOF\n");
            break;
    }
}

Token next_token(const char** input) {
    Token token;
    token.value[0] = '\0';
    
    while (**input && isspace(**input)) {
        (*input)++;
    }

    if (**input == '\0') {
        token.type = TOKEN_EOF;
        return token;
    }

    if (isalpha(**input) || **input == '_') {
        int length = 0;
        while (isalnum(**input) || **input == '_') {
            token.value[length++] = **input;
            (*input)++;
        }
        token.value[length] = '\0';
        if (is_cpp_keyword(token.value)) {
            token.type = TOKEN_KEYWORD;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }
        return token;
    }

    if (isdigit(**input)) {
        int length = 0;
        while (isdigit(**input)) {
            token.value[length++] = **input;
            (*input)++;
        }
        token.value[length] = '\0';
        token.type = TOKEN_INTEGER;
        return token;
    }

    // Handle operators and delimiters
    const char* operators_and_delimiters = "+-*/%&|^!~<>=;,.(){}[]";
    if (strchr(operators_and_delimiters, **input)) {
        token.value[0] = **input;
        token.value[1] = '\0';
        if (strchr("+-*/%&|^!~<>=!?:", **input)) {
            token.type = TOKEN_OPERATOR;
        } else {
            token.type = TOKEN_DELIMITER;
        }
        (*input)++;
        return token;
    }

    token.value[0] = **input;
    token.value[1] = '\0';
    token.type = TOKEN_UNKNOWN;
    (*input)++;
    return token;
}
