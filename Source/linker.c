// linker.c
#include <stdio.h>
#include <stdlib.h>
#include "linker.h"

void link_files(const char *assembly_file, const char *output_filename) {
    char command[256];

    // Assemble the assembly file into an object file
    snprintf(command, sizeof(command), "gcc %s -o temp.o", assembly_file);
    if (system(command) != 0) {
        fprintf(stderr, "Error assembling file %s\n", assembly_file);
        return;
    }

    // Link the object file into the final executable
    snprintf(command, sizeof(command), "gcc temp.o -o %s", output_filename);
    if (system(command) != 0) {
        fprintf(stderr, "Error linking file temp.o into %s\n", output_filename);
        return;
    }

    // Clean up temporary object file
    remove("temp.o");
}
