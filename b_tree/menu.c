#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b_tree.h"

void search_student(Node *root, char *arq_dados) {
    int mat;
    printf("Digite a matricula: ");
    scanf("%d", &mat);

    Element *e = search_val(root, mat);
    if (e != NULL) {
        FILE *f = fopen(arq_dados, "r");
        if (f) {
            fseek(f, e->offset, SEEK_SET);
            Register reg;

            fscanf(f, "%d;%[^;];%[^\n]\n", &reg.matricula, reg.nome, reg.telefone);
            printf("\nNome: %s\nTelefone: %s\n", reg.nome, reg.telefone);
            fclose(f);
        }
    } else {
        printf("Matricula nao encontrada.\n");
    }
}

void register_student(Node **root, char *arq_dados) {
    Register reg;
    printf("Matricula: "); scanf("%d", &reg.matricula);
    printf("Nome: "); scanf(" %[^\n]", reg.nome);
    printf("Telefone: "); scanf(" %[^\n]", reg.telefone);

    FILE *f = fopen(arq_dados, "a+");
    if (!f) return;

    fseek(f, 0, SEEK_END);
    long offset = ftell(f);

    fprintf(f, "%d;%s;%s\n", reg.matricula, reg.nome, reg.telefone);
    fclose(f);

    Element elem = {reg.matricula, offset};
    *root = insert_val(*root, elem);
    printf("Cadastrado com sucesso!\n");
}


void save_recursive_node(Node *node, FILE *f) {
    if (node == NULL) return;

    fprintf(f, "Node: %p | Folha: %d | Chaves: ", (void*)node, node->is_leaf);
    for (int i = 0; i < node->keys_amount; i++) {
        fprintf(f, "[Mat: %d, Offset: %ld] ", node->elements[i].matricula, node->elements[i].offset);
    }
    fprintf(f, "\n");

    if (!node->is_leaf) {
        for (int i = 0; i <= node->keys_amount; i++) {
            save_recursive_node(node->children[i], f);
        }
    }
}

void save_tree(Node *root, char *arq_arvore) {
    FILE *f = fopen(arq_arvore, "w");
    if (!f) return;

    fprintf(f, "RAIZ: %p\n", (void*)root);
    save_recursive_node(root, f);
    fclose(f);
    printf("Arvore gravada em %s\n", arq_arvore);
}

void menu(Node **root, char *arq_dados, char *arq_arvore) {
    int op;
    do {
        printf("\n1. Cadastrar\n2. Pesquisar\n3. Gravar\n4. Sair\nOpcao: ");
        scanf("%d", &op);
        switch(op) {
            case 1: register_student(root, arq_dados); break;
            case 2: search_student(*root, arq_dados); break;
            case 3: save_tree(*root, arq_arvore); break;
            case 4: dealloc_tree(*root); break;
        }
    } while(op != 4);
}

Node *load_initial_file(char *arq_dados) {
    Node *root = NULL;
    FILE *f = fopen(arq_dados, "r");

    if (!f) return NULL;

    long offset = ftell(f);
    Register reg;

    while (fscanf(f, "%d;%[^;];%[^\n]\n", &reg.matricula, reg.nome, reg.telefone) == 3) {
        Element elem = {reg.matricula, offset};
        root = insert_val(root, elem);
        offset = ftell(f);
    }

    fclose(f);
    printf("Dados carregados para a arvore B com sucesso!\n");
    return root;
}