#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

#define ARRAY_SIZE 20
#define TREE_PADDING 5

int main() {
    Node *root = NULL;

    int i = 0;
    int numbers[ARRAY_SIZE];

    // uncomment if yoy want to change the tree numbers randomly
    // srand(time(NULL));

    while (i < ARRAY_SIZE) {
        numbers[i] = rand() % 100;
        i++;
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        root = insert_node(numbers[i], root);
    }

    printf("---------------- Arvore Inicial ----------------\n");
    print_tree(root, TREE_PADDING);

    delete_val(root, 58);

    printf("---------------- Arvore Final ----------------\n");
    print_tree(root, TREE_PADDING);

    dealloc_tree(root);
}
