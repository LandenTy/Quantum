#include "parser.h"
#include "lexer.h"

void parse_tokens(const char *source_code) {
    const char *p = source_code;
    Token token;

    do {
        token = next_token(&p);
        print_token(token);
    } while (token.type != TOKEN_EOF);
}
