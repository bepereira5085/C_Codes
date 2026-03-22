#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

#define ARRAY_SIZE 50

int main() {
    Node *root = NULL;

    int i = 0;
    int numbers[ARRAY_SIZE];

    // uncomment this line if yoy want to change the tree numbers randomly
    // srand(time(NULL));

    while (i < ARRAY_SIZE) {
    numbers[i] = rand() % 1000;
        i++;
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        root = insert_val(root, numbers[i]);
    }

    print_tree(root);
    dealloc_tree(root);

    return 0;
}