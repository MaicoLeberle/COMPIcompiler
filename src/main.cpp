#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "node.h"
#include "semantic_analysis.h"

extern program_pointer ast;
extern int yyparse();
extern FILE *yyin;

int main(int argc, const char* argv[]) {
    // Check if the file name was given
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " file" << std::endl;
        exit(EXIT_FAILURE);
    }

    // open a file handle to a particular file:
    FILE *file = fopen(argv[1], "r");

    // make sure it is valid:
    if (!file) {
        std::cout << "Invalid file!" << std::endl;
        return -1;
    }

    // set flex to read from it instead of defaulting to STDIN:
    yyin = file;

    // parse through the input until there is no more:
    do {
        yyparse();
    } while (!feof(yyin));

    fclose(file);

    semantic_analysis v1;

    ast->accept(v1);

    return 0;
}
