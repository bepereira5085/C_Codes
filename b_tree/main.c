#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

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