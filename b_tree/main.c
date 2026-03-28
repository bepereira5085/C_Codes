#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

// for running this program you may have and pass as command argument
// an initial file register in the pattern: student_code;name;phone (let an empty line in the end of this file)
// you may put one student per line, the values may NOT have spaces between;

// IF YOU FOUND THIS ON GITHUB, THE REPO HAS AN INITIAL REGISTER FILE AS AN EXAMPLE

// you need a file for tree registration that will be overwritten every
// tree recording (option 3), so don't let any relevant data there (empty file is a good choice)

// arguments for the .exe on command line: *.exe initial_registers.txt tree_register.txt

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <arquivo_registos.txt> <arquivo_arvore.txt>\n", argv[0]);
        return 1;
    }

    char *arq_dados = argv[1];
    char *arq_arvore = argv[2];

    Node *root = load_initial_file(arq_dados);

    menu(&root, arq_dados, arq_arvore);

    return 0;
}