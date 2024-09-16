#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"
#include "linker.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source-file> <output-exe>\n", argv[0]);
        return 1;
    }

    const char *source_filename = argv[1];
    const char *output_filename = argv[2];

    FILE *source_file = fopen(source_filename, "r");
    if (!source_file) {
        perror("Error opening source file");
        return 1;
    }

    fseek(source_file, 0, SEEK_END);
    long file_size = ftell(source_file);
    fseek(source_file, 0, SEEK_SET);

    char *source_code = (char *)malloc(file_size + 1);
    if (!source_code) {
        perror("Memory allocation failed");
        fclose(source_file);
        return 1;
    }

    fread(source_code, 1, file_size, source_file);
    source_code[file_size] = '\0';
    fclose(source_file);

    parse_tokens(source_code);
    generate_code(source_code, "temp.asm"); // Generate assembly file
    link_files("temp.asm", output_filename); // Assemble and link

    free(source_code);
    return 0;
}
