#ifndef LEXER_H
#define LEXER_H

// Use a more specific name for TokenType to avoid conflicts
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_INTEGER,
    TOKEN_OPERATOR,
    TOKEN_DELIMITER,
    TOKEN_UNKNOWN,
    TOKEN_EOF
} MyTokenType;

typedef struct {
    MyTokenType type;
    char value[256];
} Token;

// Function prototypes
int is_cpp_keyword(const char* str);
void print_token(Token token);
Token next_token(const char** input);

#endif // LEXER_H
