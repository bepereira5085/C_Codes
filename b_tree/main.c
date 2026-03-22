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

    int search_number = 827;
    Node *found_node = search_val(root, search_number);

    if (found_node == NULL) {
        printf("\no valor nao esta na arvore\n");
    } else {
        printf("--- No ---\n");
        printf("folha? %s\n", found_node->is_leaf ? "sim" : "nao");
        printf("valores quantidade: %d\n", found_node->keys_amount);

        printf("chaves: [");
        for (int i = 0; i < found_node->keys_amount; i++) {
            printf("%d", found_node->keys[i]);
            if (i < found_node->keys_amount - 1) {
                printf(", ");
            }
        }
        printf("]\n");

        printf("ponteiros: [");
        int last_index = 0;
        for (int i = 0; i < found_node->keys_amount; i++) {
            printf("%p", (void *)found_node->children[i]);
            if (i <= found_node->keys_amount - 1) {
                printf(", ");
            }
            last_index++;
        }
        printf("%p]\n\n", (void *)found_node->children[last_index]);

        printf("infos valor encontrado:\n");
        int val_index;
        for(int i = 0; i < found_node->keys_amount; i++) {
            if (found_node->keys[i] == search_number) {
                val_index = i;
                break;
            }
        }
        printf("%p <-- %d --> %p", (void *)found_node->children[val_index], search_number, (void *)found_node->children[val_index+1]);
    }

    dealloc_tree(root);

    return 0;
}