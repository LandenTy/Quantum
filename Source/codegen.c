#include <stdio.h>
#include <stdlib.h>
#include "codegen.h"

void generate_code(const char *source_code, const char *output_filename) {
    FILE *file = fopen(output_filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    // Simple example of assembly code for x86_64 architecture
    fprintf(file, "section .data\n");
    fprintf(file, "msg db 'Hello, World!', 0\n");
    fprintf(file, "section .text\n");
    fprintf(file, "global _start\n");
    fprintf(file, "_start:\n");
    fprintf(file, "mov rax, 1       ; sys_write\n");
    fprintf(file, "mov rdi, 1       ; file descriptor (stdout)\n");
    fprintf(file, "mov rsi, msg     ; pointer to message\n");
    fprintf(file, "mov rdx, 13      ; message length\n");
    fprintf(file, "syscall\n");
    fprintf(file, "mov rax, 60      ; sys_exit\n");
    fprintf(file, "xor rdi, rdi     ; exit code 0\n");
    fprintf(file, "syscall\n");

    fclose(file);
}
